#include "gamedata.hpp"
#include "entity/scp_939.hpp"
#include "constants.hpp"

bool player_is_near(ent::SCP_939 *scp, Gamedata *gamedata)
{

    return true;
}
bool able_to_set_path(ent::SCP_939 *scp)
{
    std::pair<double, double> pos = scp->get_pos();
    return fabs(pos.first - floor(pos.first) - 0.5) < DOUBLE_EPS && fabs(pos.second - floor(pos.second) - 0.5) < DOUBLE_EPS;
}
std::vector<std::pair<double, double>> find_path_centers(std::pair<double, double> a, std::pair<double, double> b);

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