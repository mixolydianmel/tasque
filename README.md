# Tasque
> A Todo-List and Task Manager for the Terminal

## About
This project is essentially a replication of the popular organization service [Trello](https://trello.com/) for the UNIX terminal. The aim is generally to keep the code clean and concise, however that may not be the case during development. The project is written in `C++` with the `ncurses` library.

## Usage
### Building
To build, the following are required:
+ ncurses
+ gcc
If these requirements are fulfilled, the program may be built by running the `build` executable provided in this repository. Make sure the file is marked as executable on your machine, as this may not be the case immediately after cloning the repository.
### Running
As the project is currently in development, the `tasque` executable is generated in the same directory as the build executable. Running the generated executable will launch tasque in the terminal window it was run in.
### Keybindings
> Note: For the most part, `tasque` uses vim-like keybinds.

| Key | Action                                                                 |
|-----|------------------------------------------------------------------------|
| `h` | Select the list to the left                                            |
| `j` | Select the next tile down in the current list                          |
| `k` | Select the next tile up in the current list                            |
| `l` | Select the list to the right                                           |
| `a` | Add another tile to the current list                                   |
| `A` | Add another list to the current board                                  |
| `d` | Delete the currently selected tile                                     |
| `D` | Delete the currently selected list (deletes all tiles within the list) |
| `e` | Modify the current tile                                                |
| `q` | Quits the program                                                      |

Any other key pressed will result in that key's character value being printed to the command window, as well as its actual representation.

## Plans
As this project is currently incomplete, here are some of the planned features:
+ Multiple boards
+ Viewing a tile's title and description in a separate window
+ Help panel
+ vim-like commands and command syntax
+ Color
+ Persistence of boards, lists, and tiles through a file-storage solution
As the project's development continues, more features will be added to this list. Eventually the project should be quite extensive. Any suggestions are welcome!

## Contact
If you have any issues or questions, you can contact me at:
`cadenhenrich at gmail period com`

## License
This project is released and maintained under the GNU GPLv3 license.
