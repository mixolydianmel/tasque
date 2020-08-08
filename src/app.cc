/*
WARNING:
This code is in development.
It is messy.
It is poorly formatted.
It is an absolute travesty.
This will all be cleaned up later. Promise ;)
*/
#include <ncurses.h>

#include "database.hh"

#include "board.hh"
#include "list.hh"
#include "tile.hh"

void draw_tasque(std::vector<Board*> boards, WINDOW *boardwin, unsigned int curBoard, unsigned int curList, unsigned int curTile, int ymax, int xmax)
{
    Board *b = boards.at(curBoard);
    for (unsigned int i = 0; i < b->getLength(); i++)
    {
        if (i == curList)
            wattron(boardwin, A_ITALIC);
        b->getList(i)->render(boardwin, 3, 1 + (i * 20), ymax - 2, 20 + (i * 20));
        wattroff(boardwin, A_ITALIC);
        for (unsigned int j = 0; j < b->getList(i)->getLength(); j++)
        {
            if (i == curList && j == curTile)
                wattron(boardwin, A_REVERSE);
            b->getList(i)->getTile(j)->render(boardwin, 5 + j, 1 + (i * 20), 20 + (i * 20));
            wattroff(boardwin, A_REVERSE);
        }
    }

    b->render(boardwin, xmax);
}

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

    unsigned int curBoard = 0;
    unsigned int curList = 0;
    unsigned int curTile = 0;

    std::vector<Board*> boards;
    load(boards);

    draw_tasque(boards, boardwin, curBoard, curList, curTile, ymax, xmax);

    // Main loop
    curs_set(0);
    bool run = true;
    Board *b = boards.at(curBoard);
    while (run)
    {
        int cmd = mvwgetch(cmdwin, 0, 0);
        switch (cmd)
        {
            case 104:
                if (curList != 0)
                    curList--;
                if (curTile > b->getList(curList)->getLength() - 1)
                    curTile = b->getList(curList)->getLength() - 1;
                break;
            case 106:
                if (curTile != b->getList(curList)->getLength() - 1)
                    curTile++;
                break;
            case 107:
                if (curTile != 0)
                    curTile--;
                break;
            case 108:
                if (curList != b->getLength() - 1)
                    curList++;
                if (curTile > b->getList(curList)->getLength() - 1)
                    curTile = b->getList(curList)->getLength() - 1;
                break;
            case 101:
                {
                    if (b->getLength() != 0)
                    {
                        echo();
                        curs_set(1);
                        wclear(cmdwin);
                        wprintw(cmdwin, "Enter title: ");

                        char title[512];
                        wgetnstr(cmdwin, title, 512);

                        b->getList(curList)->getTile(curTile)->setTitle(std::string(title));

                        wclear(cmdwin);
                        wprintw(cmdwin, "Enter description: ");

                        char desc[512];
                        wgetnstr(cmdwin, desc, 512);

                        b->getList(curList)->getTile(curTile)->setDesc(std::string(desc));

                        wclear(cmdwin);
                        wprintw(cmdwin, "Tile modified.");
                        curs_set(0);
                        noecho();
                    }
                    break;
                }
            case 97:
                {
                    if (b->getLength() != 0)
                    {
                        echo();
                        curs_set(1);
                        wclear(cmdwin);
                        wprintw(cmdwin, "Enter title: ");

                        char title[512];
                        wgetnstr(cmdwin, title, 512);

                        wclear(cmdwin);
                        wprintw(cmdwin, "Enter description: ");

                        char desc[512];
                        wgetnstr(cmdwin, desc, 512);

                        b->getList(curList)->addTile(new Tile(std::string(title), std::string(desc)));
                        if (curTile > b->getList(curList)->getLength() - 1)
                            curTile = b->getList(curList)->getLength() - 1;

                        wclear(cmdwin);
                        wprintw(cmdwin, "Tile added.");
                        curs_set(0);
                        noecho();
                    }
                    break;
                }
            case 100:
                {
                    if (b->getList(curList)->getLength() != 0)
                    {
                        wclear(cmdwin);
                        wprintw(cmdwin, "Are you sure you want to delete this tile? [y/N]");
                        char choice = wgetch(cmdwin);
                        if (choice == 'y')
                        {
                            b->getList(curList)->delTile(curTile);

                            if (curTile > b->getList(curList)->getLength() - 1 && b->getList(curList)->getLength() != 0)
                                curTile = b->getList(curList)->getLength() - 1;

                            wclear(cmdwin);
                            wprintw(cmdwin, "Tile deleted.");
                        }
                        else
                            wclear(cmdwin);
                    }
                    break;
                }
            case 65:
                {
                    echo();
                    curs_set(1);
                    wclear(cmdwin);
                    wprintw(cmdwin, "Enter list title: ");

                    char title[512];
                    wgetnstr(cmdwin, title, 512);

                    b->addList(new List(std::string(title)));

                    wclear(cmdwin);
                    wprintw(cmdwin, "List added.");
                    curs_set(0);
                    noecho();
                    break;
                }
            case 68:
                {
                    if (b->getLength() != 0)
                    {
                        wclear(cmdwin);
                        wprintw(cmdwin, "Are you sure you want to delete this list? [y/N]");
                        char choice = wgetch(cmdwin);
                        if (choice == 'y')
                        {
                            b->delList(curList);

                            if (curList > b->getLength() - 1 && b->getLength() != 0)
                                curList = b->getLength() - 1;

                            wclear(cmdwin);
                            wprintw(cmdwin, "List deleted.");
                        }
                        else
                            wclear(cmdwin);
                    }
                    break;
                }
            case 113:
                {
                    wclear(cmdwin);
                    wprintw(cmdwin, "Do you really want to quit (your work will be saved)? [y/N]");
                    char choice = wgetch(cmdwin);
                    if (choice == 'y')
                        run = false;
                    else
                        wclear(cmdwin);
                    break;
                }
            default:
                wclear(cmdwin);
                wprintw(cmdwin, "Key code: %3d printed as \'%c\'", cmd, cmd);
                break;
        }
        wclear(boardwin);

        draw_tasque(boards, boardwin, curBoard, curList, curTile, ymax, xmax);

        wrefresh(cmdwin);
        wrefresh(boardwin);
        refresh();
    }

    save_all(boards);
    endwin(); // stop curses context

    return 0;
}
