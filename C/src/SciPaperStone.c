#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "SciPaperStone.h"

int main() {

    Game game;
    uint32_t user_set_rounds;
    Move user_move, com_move;
    Outcome round_result;

    //Game intro
    printf("Welcome to SciPaperStone!\n");
    delay(500);
    printf("Choose the number of games to play [1-10]: ");
    scanf("%d", &user_set_rounds);

    game_init(&game, user_set_rounds);

    // gameplay loop
    while(require_next_round(&game)) {
        delay(250);
        game_show_round_statistics(&game);

        user_move = get_user_move_loop();
        com_move = generate_random_move();

        round_result = game_outcome_round(user_move, com_move);

        delay(500);
        switch(round_result) {
            case win:
                printf("Win!\n");
                break;
            case loss:
                printf("Loss!\n");
                break;
            case tie:
                printf("Tie!\n");
                break;
            default:
                break;
        }
        game_update(round_result, &game);
    }

    delay(500);
    game_end_show_statistics(&game);
    return 0;
}

/**
 * @brief Initialize the game tracker struct
 *
 * @param new_game Pointer to Game struct
 * @param total_rounds Total number of rounds to play
 */
void game_init(Game *new_game, uint32_t total_rounds) {
    assert(
        ("Number of rounds chosen should not be zero",
        total_rounds != 0)
    );
    assert(
        ("Pointer to game struct should not be null",
        new_game != NULL)
    );

    new_game->num_rounds = total_rounds;
    new_game->rounds_played = 0;
    new_game->user_wins = 0;
    new_game->com_wins = 0;
}

/**
 * @brief Increments the current round counter
 *
 * @param game
 */
void game_round_next(Game *game) {
    game->rounds_played++;
    assert(
        ("Round counter should never be greater than number of rounds",
        game->rounds_played <= game->num_rounds)
    );
}

/**
 * @brief Increments the user win counter
 *
 * @param game
 */
void game_round_add_user_win(Game *game) {
    game->user_wins++;
    assert(
        ("Total wins should never exceed total number of rounds",
        game->user_wins+game->com_wins <= game->num_rounds)
    );
}

/**
 * @brief Increments the com win counter
 *
 * @param game
 */
void game_round_add_com_win(Game *game) {
    game->com_wins++;
    assert(
        ("Total wins should never exceed total number of rounds",
        game->user_wins+game->com_wins <= game->num_rounds)
    );
}

/**
 * @brief Displays relavant game statistics for user
 *
 * @param game Pointer to game struct
 */
void game_show_round_statistics(Game *game) {
    printf("\nRound %d/%d\n", game->rounds_played + 1, game->num_rounds);
    printf("Wins: %d\n", game->user_wins);
    printf("Losses: %d\n", game->com_wins);
    printf("Ties: %d\n", game->rounds_played - game->user_wins - game->com_wins);
}

/**
 * @brief Shows relavant game statistics at the end of game
 *
 * @param game
 */
void game_end_show_statistics(Game *game) {
    Outcome outcome = game_outcome(game);

    printf("\n");
    switch(outcome) {
        case win:
            printf("Game won!\n");
            break;
        case loss:
            printf("Game lost!\n");
            break;
        case tie:
            printf("It's a tie!\n");
            break;
        default:
            break;
    }
    printf("Wins: %d\n", game->user_wins);
    printf("Losses: %d\n", game->com_wins);

}

/**
 * @brief Update game struct using round results
 *
 * @param round_result Outcome of a round
 * @param game Pointer to game struct
 */
void game_update(Outcome round_result, Game *game) {
    switch(round_result) {
        case win:
            game_round_add_user_win(game);
            break;
        case loss:
            game_round_add_com_win(game);
            break;
        default:
            break;
    }
    game_round_next(game);
}

/**
 * @brief Sleeps for specified amount of time
 *
 * @param milliseconds
 */
void delay(uint32_t milliseconds) {
    usleep(milliseconds << 10);
}

/**
 * @brief Performs input validation
 *
 * @return Move
 */
Move get_user_move_loop(void) {
    uint32_t user_input;
    do {
        printf("Make a move [0=Sci,1=Paper,2=Stone]: ");
        scanf("%d", &user_input);

    } while(user_input >= NUM_MOVE_TYPES);

    return (Move)user_input;
}

/**
 * @brief Returns a random move for computer
 *
 * @return Move
 */
Move generate_random_move(void) {
    srand(time(NULL));
    return (Move)(rand() % NUM_MOVE_TYPES);
}

/**
 * @brief Returns the result of one round, from player's perspective
 *
 * @param user Move by user
 * @param computer Move by computer
 * @return Game outcome
 */
Outcome game_outcome_round(Move user, Move computer) {
    if(user == sci) {
        if(computer == sci) return tie;
        if(computer == paper) return win;
        if(computer == stone) return loss;
    } else if(user == paper) {
        if(computer == sci) return loss;
        if(computer == paper) return tie;
        if(computer == stone) return win;
    } else if(user == stone) {
        if(computer == sci) return win;
        if(computer == paper) return loss;
        if(computer == stone) return tie;
    }
    return undefined;
}

/**
 * @brief Deterine the current outcome of a game
 *
 * @param game Pointer to game struct
 * @return Outcome
 */
Outcome game_outcome(Game *game) {
    if(game->user_wins > game->com_wins) return win;
    if(game->user_wins < game->com_wins) return loss;
    if(game->user_wins == game->com_wins) return tie;

    return undefined;
}

/**
 * @brief Determine if another game round is required
 *
 * @param game Pointer to game struct
 * @return bool
 */
bool require_next_round(Game *game) {

    // win delta between user and com greater than num games left
    if(game->user_wins > game->com_wins) {
        if(
            (game->user_wins - game->com_wins) >
            (game->num_rounds - game->rounds_played)
        ) return false;
        else return true;

    // same, but reversed for computer
    } else if(game->com_wins > game->user_wins) {
        if(
            (game->com_wins - game->user_wins) >
            (game->num_rounds - game->rounds_played)
        ) return false;
        else return true;

    // if user and com wins are equal
    } else {
        if(game->num_rounds - game->rounds_played > 0) return true;
        else return false;
    }

    return false;
}
