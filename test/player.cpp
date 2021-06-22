#include "game_logic/player.h"

#include "game_logic/game.h"
#include "gtest/gtest.h"

TEST(PlayerTests, playerMoves) {
    Game game("../config/config.yaml", "../assets/maps/test_map.yaml");
    // test_map:
    // 0 1 1 1
    // 0 0 0 1
    // 1 1 0 1
    // 0 0 0 0
    Player player(game, 0, 0);
    EXPECT_EQ(player.getX(), 0);
    EXPECT_EQ(player.getY(), 0);

    player.moveDown();
    // Se pudo mover, la posicion debe cambiar.
    EXPECT_EQ(player.getX(), 0);
    EXPECT_EQ(player.getY(), 1);

    player.moveDown();
    // Colision con una pared, la posicion no debe cambiar.
    EXPECT_EQ(player.getX(), 0);
    EXPECT_EQ(player.getY(), 1);
}
