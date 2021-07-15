#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

enum TeamID : uint8_t {
    NONE = 0,
    TEAM_A = 1,
    TEAM_B = 2,
};

enum Role : char {
    NO_ROLE = 0,
    COUNTER_TERRORIST = 1,
    TERRORIST = 2,
};

enum Phase : char {
    TEAMS_FORMING_PHASE = 0,
    PREPARATION_PHASE = 1,
    MAIN_PHASE = 2,
    FINAL_PHASE = 3
};

#define BodyTypeSize 17
enum BodyType : uint8_t {
    OFFICE_TYPE = 0,
    WALL_TYPE = 1,
    CT2_TYPE = 2,
    AK47_TYPE = 3,
    AK47_D_TYPE = 4,
    CT1_TYPE = 5,
    PLAYER_TYPE = 6,
    NO_BODY_TYPE = 7,
    GLOCK_TYPE = 8,
    KNIFE_TYPE = 9,
    BOMB_D_TYPE = 10,
    TT1_TYPE = 11,
    AK47_M_TYPE = 12,
    AWP_TYPE = 13,
    AWP_M_TYPE = 14,
    M3_TYPE = 15,
    M3_M_TYPE = 16
};

#endif
