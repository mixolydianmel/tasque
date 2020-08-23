# Tasque
> Tasque \\'task\\\
> n. A Todo-List and Task Manager for the Terminal

## About
This project is essentially a replication of the popular organization service [Trello](https://trello.com/) for the UNIX terminal. The aim is generally to keep the code clean and concise, however that may not be the case during development. The project is written in `C++` with the `ncurses` library.

## Usage

### Building
To build, the following are required:
+ ncurses
+ gcc / g++
+ make

If these requirements are fulfilled, the program may be built by running `make clean install`. This will likely require root user permissions, as the executable is installed in `/usr/local/bin`.

### Running
After building, the user can run the command "`tasque`" in a terminal emulator.

### Directories
| Directory         | Purpose                   |
|-------------------|---------------------------|
| `/usr/local/bin`  | Executable                |
| `~/.cache/tasque` | Stores data in `data.tsq` |

### Keybindings
See [the wiki page](https://github.com/cadenhenrich/tasque/wiki/Keybindings)

## Plans
As this project is currently incomplete, here are some of the planned features:
+ Color
+ Scrolling over lists if they extend past the board edge
+ Resizing
+ Tags/Labels

As the project's development continues, more features will be added to this list. Eventually the project should be quite extensive. Any suggestions are welcome!

## Contact
If you have any issues or questions, you can contact me at:

`cadenhenrich at gmail period com`

## License
This project is released and maintained under the GNU GPLv3 license.
