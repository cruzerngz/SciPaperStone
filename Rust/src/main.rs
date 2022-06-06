mod game;
use crate::game::types::{Outcome, Move};


fn main() {
    use Outcome::*;
    use Move::*;

    println!("Welcome to SciPaperStone");
    game::delay(500);

    let num_rounds = game::get_user_games_loop();

    // objects tend to be modified during their lifetime, and should be declared as mut
    let mut new_game: game::Session = game::new_session(num_rounds);

    while new_game.require_next_round() {
        game::delay(250);
        println!("{}", new_game.round_stats());

        let user_move: Move = game::get_user_move_loop();
        let round_outcome: &Outcome = new_game.play_round(user_move);

        game::delay(500);
        let reaction: String = match round_outcome {
            Win => "Win!".to_string(),
            Loss => "Loss!".to_string(),
            Tie => "Tie!".to_string(),
            _ => "".to_string()
        };
        println!("{}", reaction);
    }
    game::delay(500);
    println!("{}", new_game.end_stats());

}


