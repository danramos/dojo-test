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
    game.place(1, 0);

    const std::vector<std::vector<int>> expected = {
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {1, 0, 0, 0, 0 ,0, 0},
    };

    const auto layout = game.getLayout();
    for (auto i = 0; i < 6; i++) {
        ASSERT_EQUAL_VECTORS(layout[i], expected[i]);
    }
}

FIXTURE_TEST_CASE(PlayerTwoPlacesFirstTokenInColumn0, Fixture)
{
    game.place(2, 0);

    const std::vector<std::vector<int>> expected = {
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {2, 0, 0, 0, 0 ,0, 0},
    };

    const auto layout = game.getLayout();
    for (auto i = 0; i < 6; i++) {
        ASSERT_EQUAL_VECTORS(layout[i], expected[i]);
    }
}

FIXTURE_TEST_CASE(PlayerOnePlacesMultipleTokenInOneColumn, Fixture)
{
    game.place(1, 1);
    game.place(1, 1);
    game.place(1, 1);

    const std::vector<std::vector<int>> expected = {
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 0, 0, 0, 0 ,0, 0},
       {0, 1, 0, 0, 0 ,0, 0},
       {0, 1, 0, 0, 0 ,0, 0},
       {0, 1, 0, 0, 0 ,0, 0},
    };

    const auto layout = game.getLayout();
    for (auto i = 0; i < 6; i++) {
        ASSERT_EQUAL_VECTORS(layout[i], expected[i]);
    }
}

FIXTURE_TEST_CASE(PlayerOnePlacesExcessTokenInOneColumnShallNotBeAllowed, Fixture)
{
    for (int i = 0; i < 6; i++) {
        ASSERT_EQUAL(true, game.isAdditionalTokenAllowed(1));
        game.place(1, 1);
    }
    ASSERT_EQUAL(false, game.isAdditionalTokenAllowed(1));
}

FIXTURE_TEST_CASE(NoWinnerInStart, Fixture)
{
    ASSERT_EQUAL(0, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerOneWinsWithVertical, Fixture)
{
   game.place(1,0);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,0);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,0);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,0);
   ASSERT_EQUAL(1, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerTwoWinsWithVerticalInColumnTwo, Fixture)
{
   game.place(2,2);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(2,2);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(2,2);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(2,2);
   ASSERT_EQUAL(2, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerOneWinsWithVerticalInTop, Fixture)
{
    /**
     * 1 0 0 0 0 0 0
     * 1 0 0 0 0 0 0
     * 1 0 0 0 0 0 0
     * 1 0 0 0 0 0 0
     * 2 0 0 0 0 0 0
     * 2 0 0 0 0 0 0
     */
   game.place(2, 0);
   game.place(2, 0);

   game.place(1,0);
   game.place(1,0);
   game.place(1,0);
   ASSERT_EQUAL(0, game.getWinner());
   game.place(1,0);

   ASSERT_EQUAL(1, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerOneWinsWithHorizontalInBottomRow, Fixture)
{
   /**
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  1 1 1 1 0 0 0
    */
   game.place(1,0);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,1);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,2);
   ASSERT_EQUAL(0, game.getWinner());

   game.place(1,3);
   ASSERT_EQUAL(1, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerTwoWinsWithHorizontalInFifthRow, Fixture)
{
   /**
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  2 2 2 2 0 0 0
    *  1 2 1 2 0 0 0
    */
   game.place(1,0);
   game.place(1,2);
   game.place(2,1);
   game.place(2,3);

   game.place(2,0);
   game.place(2,1);
   game.place(2,2);
   ASSERT_EQUAL(0, game.getWinner());
   game.place(2,3);

   ASSERT_EQUAL(2, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerOneWinsWithNegativeDiagonal, Fixture)
{
   /**
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  1 0 0 0 0 0 0
    *  2 1 0 0 0 0 0
    *  2 2 1 0 0 0 0
    *  2 2 2 1 0 0 0
    */
   game.place(2,0);
   game.place(2,0);
   game.place(2,0);

   game.place(2,1);
   game.place(2,1);

   game.place(2,2);

   game.place(1,0);
   game.place(1,1);
   game.place(1,2);
   game.place(1,3);

   ASSERT_EQUAL(1, game.getWinner());
}

FIXTURE_TEST_CASE(PlayerTwoWinsWithPostiveDiagonal, Fixture)
{
   /**
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 0
    *  0 0 0 0 0 0 2
    *  0 0 0 0 0 2 1
    *  0 0 0 0 2 1 1
    *  0 0 0 2 1 1 1
    */
   game.place(1,6);
   game.place(1,6);
   game.place(1,6);

   game.place(1,5);
   game.place(1,5);

   game.place(1,4);

   game.place(2,3);
   game.place(2,4);
   game.place(2,5);
   game.place(2,6);

   ASSERT_EQUAL(2, game.getWinner());
}


int main()
{
    RUN_TESTS();
}
