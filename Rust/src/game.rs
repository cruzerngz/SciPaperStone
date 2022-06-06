// Module containing game-related code

use std::io;
use std::io::Write;

use crate::game::types::Outcome::*;
use crate::game::types::Move::*;

/// Module containing types used in the game
pub mod types {

    /// Contains the 3 valid move types
    pub enum Move {

        Sci, Paper, Stone
    }

    /// Contains various game outcomes
    pub enum Outcome {

        Win, Loss, Tie, Undefined
    }
}

impl types::Move {
    /// Converts a u32 to a valid move
    fn from_u32(mut value: u32) -> types::Move {

        value %= 3;

        return match value {
            0 => Sci,
            1 => Paper,
            2 => Stone,
            _ => Stone
        }
    }
}

/// Contains game init parameters and statistics
pub struct Session {

    num_rounds: u32,
    rounds_played: u32,
    user_wins: u32,
    com_wins: u32
}

impl Session {
    /// Compares a user move to a randomly generated computer move.
    /// Returns a Outcome enum
    pub fn play_round(&mut self, user_move: types::Move) -> &types::Outcome {

        let com_move = generate_random_move();

        self.rounds_played += 1;

        match move_outcome(user_move, com_move) {
            Win => {
                self.user_wins += 1;
                &Win
            },
            Loss => {
                self.com_wins += 1;
                &Loss
            },
            Tie => {
                &Tie
            },
            Undefined => {
                &Undefined
            }
        }

    }

    pub fn current_outcome(&self) -> types::Outcome {
        if self.user_wins > self.com_wins {return types::Outcome::Win}
        if self.com_wins > self.user_wins {return types::Outcome::Loss}
        if self.user_wins == self.com_wins {return types::Outcome::Tie}
        return types::Outcome::Undefined;
    }

    pub fn require_next_round(&self) -> bool {
        if self.user_wins > self.com_wins {
            if  (self.user_wins - self.com_wins) >
                (self.num_rounds - self.rounds_played) {
                    return false;
            } else {return true;}
        } else if self.com_wins > self.user_wins {
            if  (self.com_wins - self.user_wins) >
                (self.num_rounds - self.rounds_played) {
                return false;
            } else {return true;}
        } else {
            if self.num_rounds - self.rounds_played > 0 {return true;}
            else {return false;}
        }

    }

    pub fn round_stats(&self) -> String {
        let return_str: String = format!(
            "\nRound {}/{}\n\
            Wins: {}\n\
            Losses: {}\n\
            Ties: {}\n",
            self.rounds_played,
            self.num_rounds,
            self.user_wins,
            self.com_wins,
            self.rounds_played - self.user_wins - self.com_wins
        );

        return return_str;
    }

    pub fn end_stats(&self) -> String {

        let result: String = match self.current_outcome() {
                Win => "Game won!".to_string(),
                Loss => "Game lost!".to_string(),
                Tie => "It's a tie!".to_string(),
                Undefined => "".to_string()
        };
        let skipped: String = match self.num_rounds - self.rounds_played {
            0 => "".to_string(),
            _ => format!("Skipped {} round(s)", self.num_rounds - self.rounds_played)
        };

        let return_str: String = format!(
            "\n{}\n\
            Wins: {}\n\
            Losses: {}\n\
            {}",
            result,
            self.user_wins,
            self.com_wins,
            skipped
        );

        return return_str;
    }
}

pub fn new_session(num_rounds:u32) -> Session {
    Session {
        num_rounds: num_rounds,
        rounds_played: 0,
        user_wins: 0,
        com_wins: 0
    }
}

pub fn get_user_games_loop() -> u32 {
    let mut num_games: u32 = 0;

    while num_games == 0 {
        let mut buffer: String = String::new();

        print!("Choose the number of games to play [1-10]: ");
        match io::stdout().flush() {
            Ok(_) => {},
            Err(_) => {continue}
        }

        io::stdin().read_line(&mut buffer).unwrap();

        match buffer.trim().parse::<u32>() {
            Ok(number) => num_games = number,
            Err(_) => {
                num_games = 69;
                continue;
            }
        }
    }
    num_games
}

pub fn get_user_move_loop() -> types::Move {

    let mut user_move: u32 = u32::MAX;

    while user_move >= 3 {
        let mut buffer: String = String::new();

        print!("Make a move [0=Sci,1=Paper,2=Stone]: ");
        match io::stdout().flush() {
            Ok(_) => {},
            Err(_) => {continue}
        }

        io::stdin().read_line(&mut buffer).unwrap();
        match buffer.trim().parse::<u32>() {
            Ok(number) => user_move = number,
            Err(_) => { // an underscore denotes a generic type (i think)
                user_move = u32::MAX;
                continue;
            }
        }
    }

    types::Move::from_u32(user_move)
}

fn generate_random_move() -> types::Move {
    use rand::prelude::*;
    let mut rng = rand::thread_rng();
    let num: u32 = rng.gen();

    types::Move::from_u32(num)
}

fn move_outcome(user_move: types::Move, com_move: types::Move) -> types::Outcome {

    match user_move {
        Sci => match com_move {
            Sci => return Tie,
            Paper => return Win,
            Stone => return Loss
        }
        Paper => match com_move {
            Sci => return Loss,
            Paper => return Tie,
            Stone => return Win
        }
        Stone => match com_move {
            Sci => return Win,
            Paper => return Loss,
            Stone => return Tie
        }
    }
}

pub fn delay(delay_ms: u64) {
    let duration: std::time::Duration = std::time::Duration::from_millis(delay_ms);
    std::thread::sleep(duration);
}
