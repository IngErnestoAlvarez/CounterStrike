#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

enum TeamID : char {
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
};

#define BodyTypeSize 8
enum BodyType : uint8_t {
    OFFICE_TYPE = 0,
    WALL_TYPE = 1,
    CT2_TYPE = 2,
    AK47_TYPE = 3,
    AK47_D_TYPE = 4,
    CT1_TYPE = 5,
    PLAYER_TYPE = 6,
    NO_BODY_TYPE = 7,
};

#endif
