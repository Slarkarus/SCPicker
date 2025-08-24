#include "gamedata.hpp"
#include "entity/scp_939.hpp"
#include "entity/player.hpp"
#include "constants.hpp"

#include <cmath>
#include <cstdlib>
#include <algorithm>

// TODO: replace std::vector<std::pair<double, double>> with c++ using like
// using Point = std::pair<double, double>;
// using VectorPoints = std::vector<Point>;

bool player_is_near(ent::SCP_939 *scp, Gamedata *gamedata)
{
    struct std::pair<double, double> scp_pos = scp->get_pos();
    struct std::pair<double, double> player_pos = gamedata->get_player()->get_pos();

    return fsqrt((scp_pos.first - player_pos.first) * (scp_pos.first - player_pos.first) +
                 (scp_pos.second - player_pos.second) * (scp_pos.second - player_pos.second)) < SCP_939_HEARING_DISTANCE;
}

bool able_to_set_path(ent::SCP_939 *scp)
{
    std::pair<double, double> pos = scp->get_pos();
    return fabs(pos.first - floor(pos.first) - 0.5) < DOUBLE_EPS && fabs(pos.second - floor(pos.second) - 0.5) < DOUBLE_EPS;
}
std::vector<std::pair<double, double>> find_path_centers(std::pair<double, double> a, std::pair<double, double> b,
                                                         Gamedata *gamedata)
{
    std::pair<int, int> start = {floor(a.first), floor(a.second)};
    std::pair<int, int> finish = {floor(b.first), floor(b.second)};
    std::pair<int, int> closest_unused;
    std::pair<int, int> neighbour;
    int closest_len;

    std::vector<std::vector<Tile>> field = gamedata->get_map();
    int field_width = field[0].size();
    int field_height = field.size();

    std::vector<std::vector<int>> dp(field_height, std::vector<int>(field_width, 1e9));
    std::vector<std::vector<bool>> used(field_height, std::vector<bool>(field_width, false));
    std::vector<std::vector<std::pair<int, int>>> parent(
        field_height, std::vector<std::pair<int, int>>(field_width, {-1, -1}));

    dp[start.second][start.first] = 0;

    for (int i = 0; i < field_width * field_height; ++i) {
        closest_unused = {-1, -1};
        for (int try_pos_x = 0; try_pos_x < field_width; ++try_pos_x)
        {
            for (int try_pos_y = 0; try_pos_y < field_height; ++try_pos_y)
            {
                if (!used[try_pos_y][try_pos_x] &&
                    field[try_pos_y][try_pos_x] != Tile::Wall &&
                    (closest_unused.first == -1 
                    || dp[try_pos_y][try_pos_x] < dp[closest_unused.second][closest_unused.first])) {
                        closest_unused = {try_pos_x, try_pos_y};    
                    }
            }
        }
        
        closest_len = dp[closest_unused.second][closest_unused.first];

        if (closest_len >= 1e9 || closest_unused == finish) {
            break;
        }

        used[closest_unused.second][closest_unused.first] = true;

        for (int y_shift = -1; y_shift <= 1; ++y_shift) {
            for (int x_shift = -1; x_shift <= 1; ++x_shift) {
                if (abs(x_shift) + abs(y_shift) == 1) {
                    if (neighbour.first < 0 || neighbour.first >= field_width
                        || neighbour.second < 0 || neighbour.second >= field_height) {
                        continue;
                    }

                    neighbour = {closest_unused.first + x_shift, closest_unused.second + y_shift};
                    if (closest_len + 1 < dp[neighbour.second][neighbour.first]) {
                        dp[neighbour.second][neighbour.first] = closest_len + 1;
                        parent[neighbour.second][neighbour.first] = closest_unused;
                    }
                }
            }
        }            
    }

    std::vector<std::pair<int,int>> path;
    std::pair<int,int> current_tile = finish;
    
    if(parent[current_tile.second][current_tile.first] == std::pair<int, int>{-1,-1} && current_tile != start){
        return {};
    }

    while (current_tile != std::pair<int, int>{-1,-1}) {
        path.push_back(current_tile);
        current_tile = parent[current_tile.second][current_tile.first];
    }
    std::reverse(path.begin(), path.end());

    std::vector<std::pair<double,double>> path_centers;
    for(auto tile : path){
        path_centers.push_back({tile.first + 0.5, tile.second + 0.5});
    }
    return path_centers;
}

std::vector<std::pair<double, double>> get_scp_939_path(std::pair<double, double> a, std::pair<double, double> b, Gamedata *gamedata)
{
    std::vector<std::pair<double, double>> center_path = find_path_centers(a, b, gamedata);
    std::vector<std::pair<double, double>> true_path;

    // Поочерёдно, для каждой пары точек, добавляем все точки, которые пройдёт scp_939 кроме конечной точки, чтобы избежать дублирования точек
    for (int i = 0; i + 1 < center_path.size(); ++i)
    {
        std::pair<double, double> first_point = center_path[i];
        std::pair<double, double> second_point = center_path[i + 1];

        int num_iterations = (1.0 / SCP_939_SPEED) - 1;
        if (first_point.first != second_point.first)
        {
            double dx = second_point.first - first_point.first;
            for (int i = 0; i < num_iterations; ++i)
            {
                true_path.push_back({first_point.first + dx * SCP_939_SPEED * i, first_point.second});
            }
        }
        else
        {
            double dy = second_point.second - first_point.second;
            for (int i = 0; i < num_iterations; ++i)
            {
                true_path.push_back({first_point.first, first_point.second + dy * SCP_939_SPEED * i});
            }
        }
    }
    true_path.push_back(center_path.back());
    std::reverse(true_path.begin(), true_path.end());
    return true_path;
}

void set_path_to_player(ent::SCP_939 *scp, Gamedata *gamedata)
{
    scp->next_path_ = get_scp_939_path(scp->get_pos(), gamedata->get_player()->get_pos(), gamedata);
}

void set_random_path(ent::SCP_939 *scp, Gamedata *gamedata)
{
    std::vector<std::vector<Tile>> map = gamedata->get_map();
    int width = map[0].size();
    int height = map.size();
    int x = -1, y = -1;
    while (x == -1 || y == -1 || (map[y][x] != Tile::Empty || map[y][x] != Tile::Exit))
    {
        x = std::rand() % width;
        y = std::rand() % height;
    }

    scp->next_path_ = get_scp_939_path(scp->get_pos(), {(double)x + 0.5, (double)y + 0.5}, gamedata);
}

void set_next_pos(ent::SCP_939 *scp, std::vector<std::pair<double, double>> next_path)
{
    scp->set_pos(next_path.back());
    next_path.pop_back();
}

void ent::SCP_939::step(Gamedata *gamedata)
{
    if (!next_path_.empty())
    {
        set_next_pos(this, next_path_);
    }
    if (able_to_set_path(this)) // можно поворачивать только в центрах клеток
    {
        if (player_is_near(this, gamedata))
        {
            set_path_to_player(this, gamedata);
        }
        else if (next_path_.empty())
        {
            set_random_path(this, gamedata);
        }
    }
}