#include "gamedata.hpp"
#include "entity/scp_939.hpp"
#include "entity/player.hpp"
#include "constants.hpp"
#include <cmath>

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

void set_path_to_player(ent::SCP_939 *scp, Gamedata *gamedata) {}

void set_random_path(ent::SCP_939 *scp, Gamedata *gamedata) {}

void set_pos(ent::SCP_939 *scp, std::vector<std::pair<double, double>> &next_path) {}

void ent::SCP_939::step(Gamedata *gamedata)
{
    if (!next_path_.empty())
    {
        set_pos(this, next_path_);
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