
# ROCKS

This program is used to play a certain interesting game:

> ## The Game of Rocks: Rules
> 
> Begin with a grid of "rocks" with side length n.
> Two players take turns removing groups of rocks in the following manner:
> 
> * at least one rock is on the perimeter of the grid is removed
> * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner
> * all the rocks removed are in a straight line
> * no two rocks removed have a space between them
> 
> If, on your turn, you cannot remove rocks in this manner, you lose.

This program allows you to play this game.

## Documentation

This project is centered around the `playgame` function in `fns.cpp`.
It uses `usermove` and `compmove` to allow players to interact with the the playing board, an element of the `Board` class.
You move a cursor and the w, a, s, d, q, e, and f keys to select rocks and remove them from play.

### `Board` Class

The board class has various methods, but the key methods are `validate` and `print`.

The `validate` function checks to see if the rules are being followed.
Then, a message is outputted via `rules_message`, which also performs a logic operation to see if the move is valid.

The `print` function prints the board onto the console, allowing players to see it, which is *crucial* to gameplay.

There are also some straightforward `toggle_r`, `clear_r`, `is_over` and `get_size` methods.
These select/deselect rocks, clear selected rocks, check if the game is over, and return the grid size, respectively.

### `fns`

The core function in `fns` is `playgame`, which alternates from player 1 to player 2, checking for a won game or resignation in between.
Some other important but simple functions are `ask`, `mygetch`, and `printrules`, which ask a yes or no question, receive a key press, and print the game rules.

The more advanced functions are `compmove`, `usermove`, and `usermove_core`.

`compmove` perfoms a computer move, randomly.

`usermove` calls `usermove_core`, along with some setup, printing some stuff, and teardown, clearing selected rocks.

`usermove_core` is a recursive function which calls itself each valid keypress.
By using the `Board::validate` function, and a simple `switch` statement, a player may easily select and clear rocks.