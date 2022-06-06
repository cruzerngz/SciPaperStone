#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "ScipaperStone.hpp"

int main() {
    std::cout << "Welcome to SciPaperStone\n";
    delay(500);
    uint32_t num_games = 0;

    do {
        std::cout << "Choose the number of games to play [1-10]: ";
        std::cin >> num_games;
    } while(num_games==0);

    Game *game = new Game(num_games);
    Move user_move;
    Outcome round_outcome;
    std::string reaction;

    // gameplay loop
    while(game->require_next_round()) {
        delay(250);
        std::cout << game->round_stats();

        user_move = get_user_move_loop();
        round_outcome = game->play_round(user_move);

        delay(500);
        switch(round_outcome) {
            case win:
                reaction = "Win!";
                break;
            case loss:
                reaction = "Loss!";
                break;
            case tie:
                reaction = "Tie!";
                break;
            default:
                break;
        }
        std::cout << reaction << "\n";
    }

    delay(500);
    std::cout << game->end_stats();

    return 0;
}

Game::Game(uint32_t rounds_to_play) {
    num_rounds = rounds_to_play;
    _game_init();
}

Game::~Game() {

}

void Game::_game_init(void) {
    srand(time(NULL));
    rounds_played = 0;
    user_wins = 0;
    com_wins = 0;
}

Move Game::_generate_random_move(void) {
    return (Move)(rand() % NUM_MOVE_TYPES);
}

Outcome Game::_move_outcome(Move user, Move com) {
    if(user==sci) {
        if(com==sci) return tie;
        if(com==paper) return win;
        if(com==stone) return loss;
    }
    if(user==paper) {
        if(com==sci) return loss;
        if(com==paper) return tie;
        if(com==stone) return win;
    }
    if(user==stone) {
        if(com==sci) return win;
        if(com==paper) return loss;
        if(com==stone) return tie;
    }
    return undefined;
}

Outcome Game::play_round(Move user_move) {
    Outcome result = _move_outcome(
        user_move,
        _generate_random_move()
    );

    switch(result) {
        case win:
            user_wins++;
            break;
        case loss:
            com_wins++;
            break;
        default:
            break;
    }

    rounds_played++;
    return result;
}

Outcome Game::current_outcome(void) {
    if(user_wins > com_wins) return win;
    if(user_wins < com_wins) return loss;
    if(user_wins == com_wins) return tie;
    return undefined;
}

bool Game::require_next_round(void) {
    // win delta between either player larger than number of games remaining
    if(user_wins > com_wins) {
        if(
            (user_wins - com_wins) >
            (num_rounds - rounds_played)
        ) return false;
        else return true;
    // case for computer, same as above
    } else if(com_wins > user_wins) {
        if(
            (com_wins - user_wins) >
            (num_rounds - rounds_played)
        ) return false;
        else return true;
    // if user and com wins are equal
    } else {
        if(num_rounds - rounds_played > 0) return true;
        else return false;
    }
    return false;
}

std::string Game::round_stats(void) {
    std::ostringstream outstream;
    outstream
        << "\nRound " << rounds_played + 1
        << "/" << num_rounds << "\n"
        << "Wins: " << user_wins << "\n"
        << "Losses: " << com_wins << "\n"
        << "Ties: " << rounds_played - user_wins - com_wins << "\n";

    return outstream.str();
}

std::string Game::end_stats(void) {
    std::ostringstream outstream;
    std::string result;
    uint32_t skipped_rouds = num_rounds - rounds_played;

    switch(Game::current_outcome()) {
        case win:
            result = "Game won!";
            break;
        case loss:
            result = "Game lost!";
            break;
        case tie:
            result = "It's a tie!";
            break;
        default:
            break;
    }

    outstream
        << "\n" << result << "\n"
        << "Wins: " << user_wins << "\n"
        << "Losses: " << com_wins << "\n";

    if(skipped_rouds != 0) {
        outstream << "Skipped " << skipped_rouds << " round(s)\n";
    }

    return outstream.str();
}

void delay(uint32_t delay_ms) {
    usleep(delay_ms << 10);
}

Move get_user_move_loop(void) {
    uint32_t user_move = 0;
    do {
        std::cout << "Make a move [0=Sci,1=Paper,2=Stone]: ";
        std::cin >> user_move;
        // std::cout << "user move: " << user_move << "\n";
    } while(user_move >= NUM_MOVE_TYPES);

    return (Move)user_move;
}
