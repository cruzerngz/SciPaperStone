#ifndef SCIPAPERSTONE_H
#define SCIPAPERSTONE_H

#include <stdint.h>
#include <stdbool.h>

// 3 valid moves: sci, paper, stone
#define NUM_MOVE_TYPES 3

/**
 * @brief Enumeration of game moves
 *
 */
typedef enum _move {
    sci, paper, stone
} Move;

/**
 * @brief Enumeration of game outcomes
 *
 */
typedef enum _outcome {
    win, loss, tie, undefined
} Outcome;

/**
 * @brief Struct containing game parameters
 *
 */
typedef struct _game {
    uint32_t num_rounds;
    uint32_t rounds_played;
    uint32_t user_wins;
    uint32_t com_wins;
} Game;

// int validateinput(int input);
// char *throwinsult();
void game_init(Game* new_game, uint32_t total_rounds);
void game_round_next(Game *game);
void game_round_add_user_win(Game *game);
void game_round_add_com_win(Game *game);
void game_show_round_statistics(Game *game);
void game_show_inferred_statistics(Game *game);
void game_end_show_statistics(Game *game);
void game_update(Outcome round_result, Game *game);

void delay(uint32_t milliseconds);

Move get_user_move_loop(void);
Move generate_random_move(void);
Outcome game_outcome_round(Move user, Move computer);
Outcome game_outcome(Game *game);
bool require_next_round(Game *game);

#endif // SCIPAPERSTONE_H
