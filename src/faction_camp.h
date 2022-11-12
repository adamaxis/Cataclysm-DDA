#pragma once
#ifndef CATA_SRC_FACTION_CAMP_H
#define CATA_SRC_FACTION_CAMP_H

#include <iosfwd>
#include <utility>
#include <vector>

//#include "calendar.h"
#include "coordinates.h"

template <typename E> struct enum_traits;

namespace catacurses
{
class window;
} // namespace catacurses
class npc;
class Character;
class item_location;
class time_duration;
struct mission_entry;
struct point;
namespace base_camps
{
enum tab_mode : int;
} // namespace base_camps

enum class farm_ops : int {
    plow = 1,
    plant = 2,
    harvest = 4
};

template<>
struct enum_traits<farm_ops> {
    static constexpr bool is_flag_enum = true;
};

namespace talk_function
{
void basecamp_mission( npc & );

///Changes an NPC follower to a camp manager
void become_overseer( npc & );
///Changes an NPC follower to a camp manager, displays camp warnings, and sets the current OM tile to a camp survey
void start_camp( npc & );
///Changes an NPC follower to a camp manager of an existing camp.
void recover_camp( npc & );
///Changes an NPC camp manager to a follower
void remove_overseer( npc & );

void draw_camp_tabs( const catacurses::window &win, base_camps::tab_mode cur_tab,
                     const std::vector<std::vector<mission_entry>> &entries );
std::string name_mission_tabs( const tripoint_abs_omt &omt_pos, const std::string &role_id,
                               const std::string &cur_title, base_camps::tab_mode cur_tab );

/// Returns the OM tiles surrounding the camp, @ref purge removes all tiles that aren't expansions
std::vector<std::pair<std::string, tripoint_abs_omt>> om_building_region(
            const tripoint_abs_omt &omt_pos, int range, bool purge = false );
/// Returns the x and y coordinates of ( omt_tar - omt_pos ), clamped to [-1, 1]
point om_simple_dir( const tripoint_abs_omt &omt_pos, const tripoint_abs_omt &omt_tar );
} // namespace talk_function

//namespace camp_helpers { // NEW
    /// Changes the faction food supply by @ref change, 0 returns total food supply, a negative
    /// total food supply hurts morale
    int camp_food_supply(time_duration work);
    /// Same as above but takes a time_duration and consumes from faction food supply for that
    /// duration of work
    int camp_food_supply(int change = 0, bool return_days = false);
    /// Returns the total charges of food time_duration @ref work costs
    int time_to_food(time_duration work);
    /// Returns the complete calorie cost of crafting
    int get_craft_cost(const item_location& loc, const Character& c);
//} // namespace camp_helpers

#endif // CATA_SRC_FACTION_CAMP_H
