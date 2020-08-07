#include <ncurses.h>
#include "board.hh"
#include "list.hh"
#include "tile.hh"

int main() {
    initscr();
    cbreak();
    noecho();

    // get the dimensions of the standard screen
    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);

    // window to draw the board in
    WINDOW *boardwin = newwin(ymax - 1, xmax, 0, 0);
    box(boardwin, 0, 0);
    refresh();
    wrefresh(boardwin);

    // window to draw commands and modal stuff in
    WINDOW *cmdwin = newwin(1, xmax, ymax - 1, 0);
    keypad(cmdwin, true);

    unsigned int curList = 1;
    unsigned int curTile = 2;

    std::vector<Board*> boards;
    Board *b = new Board("Test");
    boards.push_back(b);

    b->addList(new List("List"));
    b->getList(0)->addTile(new Tile("Tile"));

    b->addList(new List("Other List With A Longer Title"));
    b->getList(1)->addTile(new Tile("Other Tile"));
    b->getList(1)->addTile(new Tile("Other Tile With A Longer Title"));
    b->getList(1)->addTile(new Tile("OwO", "Description here yada"));

    for (int i = 0; i < b->getLength(); i++)
    {
        b->getList(i)->render(boardwin, 3, 1 + (i * 20), ymax - 2, 20 + (i * 20));
        for (int j = 0; j < b->getList(i)->getLength(); j++)
        {
            if (i == curList && j == curTile)
                wattron(boardwin, A_REVERSE);
            b->getList(i)->getTile(j)->render(boardwin, 5 + j, 1 + (i * 20), 20 + (i * 20));
            wattroff(boardwin, A_REVERSE);
        }
    }

    b->render(boardwin, xmax);

    getch();
    endwin(); // stop curses context

    return 0;
}
