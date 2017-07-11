#include <dojo-test-tools.hpp>
#include <Game.hpp>
#include <type_traits>

struct Fixture
{
    Game game;

    void checkBoundaries()
    {
        const auto layout = game.getLayout();
        ASSERT_EQUAL(layout.size(), 6u);
        for (const auto& row : layout) {
            ASSERT_EQUAL(row.size(), 7u);
        }
    }

    const std::vector<int> emptyRow = {0,0,0,0,0,0,0};

};

/**
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 */
FIXTURE_TEST_CASE(GetLayoutOfEmptyBoard, Fixture)
{
    checkBoundaries();

    const auto layout = game.getLayout();

    for (const auto& row : layout) {
        ASSERT_EQUAL_VECTORS(row, emptyRow);
    }
}

/**
 *  0 0 0 0 0 0 0 //row0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0
 *  0 0 0 0 0 0 0 //row5
 */
FIXTURE_TEST_CASE(PlayerOnePlacesFirstTokenInColumn0, Fixture)
{
    Game game;
    game.place(1, 0);

    const auto layout = game.getLayout();
    const std::vector<std::vector<int>> expected = {
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {1, 0, 0, 0, 0 ,0, 0},
    };

    for (auto i = 0; i < 6; i++) {
        ASSERT_EQUAL_VECTORS(layout[i], expected[i]);
    }
}

int main()
{
    RUN_TESTS();
}
