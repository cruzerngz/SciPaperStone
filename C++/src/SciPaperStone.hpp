#ifndef SCIPAPERSTONE_HPP
#define SCIPAPERSTONE_HPP

#include <stdint.h>
#include <string>

#define NUM_MOVE_TYPES 3

typedef enum _move {
    sci, paper, stone
} Move;

typedef enum _outcome {
    win, loss, tie, undefined
} Outcome;

class Game {
    uint32_t num_rounds;
    uint32_t rounds_played;
    uint32_t user_wins;
    uint32_t com_wins;


    void _game_init(void);
    Move _generate_random_move(void);
    Outcome _move_outcome(Move user, Move com);

    public:
        Game(uint32_t rounds_to_play);
        ~Game();
        Outcome play_round(Move user_move);
        Outcome current_outcome(void);
        bool require_next_round(void);
        std::string round_stats(void);
        std::string end_stats(void);

};

void delay(uint32_t delay_ms);
Move get_user_move_loop(void);

#endif //SCIPAPERSTONE_HPP
