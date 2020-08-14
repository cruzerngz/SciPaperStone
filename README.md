# SciPaperStone
My first python program!

### How to play:
This game requires you to install the python shell on your computer.
The program follows the rules of the classic game, and allows any number of rounds to be played.

#### Entering your move
Moves can be entered in full, such as `scissors`, or `sci`, or even `ors`. Alternatively, entering the index corresponding to the position of the move in the list will also register. *Note that the index starts from 1*.

In the event that you have entered an invalid move, such as `scsiors`, the game will print an random insult from a predefined list. You have a total of 5 tries per round to spell the move correctly, after which the game will exit.

#### Ending the game early
You can end the game any time by entering `finish` or `stop`. After which the current winner will be named.

#### Best of game
As this is a best of game, when the current score gap cannot be closed by the losing player with the remaining number of rounds, the game will end early.
For example, if you have a 2-0 lead over the computer in a 3 round game, the game will end without proceeding to the final round.

Thanks for playing!
