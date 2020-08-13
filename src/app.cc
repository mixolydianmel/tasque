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

#include "info.hh"
#include "help.hh"

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

    // window to display info in
    Info info(boardwin);

    // window to display help menu in
    Help help(boardwin);

    unsigned int curBoard = 0;
    unsigned int curList = 0;
    unsigned int curTile = 0;

    std::vector<Board*> boards;
    load(boards);

    draw_tasque(boards, boardwin, curBoard, curList, curTile, ymax, xmax);

    // Main loop
    curs_set(0);
    bool run = true;
    while (run)
    {
        Board *b = boards.at(curBoard);
        int cmd = mvwgetch(cmdwin, 0, 0);
        switch (cmd)
        {
            case 'h':
                if (curList != 0)
                    curList--;
                if (curTile > b->getList(curList)->getLength() - 1)
                    curTile = b->getList(curList)->getLength() - 1;
                break;
            case 'j':
                if (curTile != b->getList(curList)->getLength() - 1)
                    curTile++;
                break;
            case 'k':
                if (curTile != 0)
                    curTile--;
                break;
            case 'l':
                if (curList != b->getLength() - 1)
                    curList++;
                if (curTile > b->getList(curList)->getLength() - 1)
                    curTile = b->getList(curList)->getLength() - 1;
                break;
            case 'H':
                if (curBoard != 0)
                    curBoard--;
                if (curList > boards.at(curBoard)->getLength() - 1)
                    curList = boards.at(curBoard)->getLength() - 1;
                if (curTile > boards.at(curBoard)->getList(curList)->getLength() - 1)
                    curTile = boards.at(curBoard)->getList(curList)->getLength() - 1;
                break;
            case 'L':
                if (curBoard != boards.size() - 1)
                    curBoard++;
                if (curList > boards.at(curBoard)->getLength() - 1)
                    curList = boards.at(curBoard)->getLength() - 1;
                if (boards.at(curBoard)->getLength() != 0 && curTile > boards.at(curBoard)->getList(curList)->getLength() - 1)
                    curTile = boards.at(curBoard)->getList(curList)->getLength() - 1;
                break;
            case 'e':
                {
                    wclear(cmdwin);
                    wprintw(cmdwin, "Edit: [T] Tile [L] List [B] Board");
                    char choice = wgetch(cmdwin);
                    switch (choice)
                    {
                        case 't':
                            {
                                if (b->getLength() != 0 && b->getList(curList)->getLength() != 0)
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
                        case 'l':
                            {
                                if (b->getLength() != 0)
                                {
                                    echo();
                                    curs_set(1);
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Enter title: ");

                                    char title[512];
                                    wgetnstr(cmdwin, title, 512);

                                    b->getList(curList)->setTitle(std::string(title));

                                    wclear(cmdwin);
                                    wprintw(cmdwin, "List modified.");
                                    curs_set(0);
                                    noecho();
                                }
                                break;
                            }
                        case 'b':
                            {
                                if (boards.size() != 0)
                                {
                                    echo();
                                    curs_set(1);
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Enter title: ");

                                    char title[512];
                                    wgetnstr(cmdwin, title, 512);

                                    b->setTitle(std::string(title));

                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Board modified.");
                                    curs_set(0);
                                    noecho();
                                }
                                break;
                            }
                    }
                    break;
                }
            case 'a':
                {
                    wclear(cmdwin);
                    wprintw(cmdwin, "Add: [T] Tile [L] List [B] Board");
                    char choice = wgetch(cmdwin);
                    switch (choice)
                    {
                        case 't':
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
                        case 'l':
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
                        case 'b':
                            {
                                echo();
                                curs_set(1);
                                wclear(cmdwin);
                                wprintw(cmdwin, "Enter board title: ");

                                char title[512];
                                wgetnstr(cmdwin, title, 512);

                                boards.push_back(new Board(std::string(title)));

                                wclear(cmdwin);
                                wprintw(cmdwin, "Board added.");
                                curs_set(0);
                                noecho();
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                }
            case 'd':
                {
                    wclear(cmdwin);
                    wprintw(cmdwin, "Delete: [T] Tile [L] List [B] Board");
                    char choice = wgetch(cmdwin);
                    switch (choice)
                    {
                        case 't':
                            {
                                if (b->getList(curList)->getLength() != 0)
                                {
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Are you sure you want to delete this tile? [y/N]");
                                    char affirm = wgetch(cmdwin);
                                    if (affirm == 'y')
                                    {
                                        b->getList(curList)->delTile(curTile);

                                        if (curTile > b->getList(curList)->getLength() - 1)
                                            curTile = b->getList(curList)->getLength() - 1;

                                        wclear(cmdwin);
                                        wprintw(cmdwin, "Tile deleted.");
                                    }
                                    else
                                        wclear(cmdwin);
                                }
                                break;
                            }
                        case 'l':
                            {
                                if (b->getLength() != 0)
                                {
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Are you sure you want to delete this list? [y/N]");
                                    char affirm = wgetch(cmdwin);
                                    if (affirm == 'y')
                                    {
                                        b->delList(curList);
                                        if (curList > b->getLength() - 1)
                                            curList = b->getLength() - 1;

                                        wclear(cmdwin);
                                        wprintw(cmdwin, "List deleted.");
                                    }
                                    else
                                        wclear(cmdwin);
                                }
                                break;
                            }
                        case 'b':
                            {
                                if (boards.size() > 1)
                                {
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Are you sure you want to delete this board? [y/N]");
                                    char affirm = wgetch(cmdwin);
                                    if (affirm == 'y')
                                    {
                                        boards.erase(boards.begin() + curBoard);
                                        if (curBoard > boards.size() - 1)
                                            curBoard = boards.size() - 1;

                                        wclear(cmdwin);
                                        wprintw(cmdwin, "Board deleted.");
                                    }
                                    else
                                        wclear(cmdwin);
                                }
                                else
                                {
                                    wclear(cmdwin);
                                    wprintw(cmdwin, "Error: Cannot delete last remaining board.");
                                }
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                }
            case '?':
                {
                    if (help.enabled())
                        help.disable();
                    else
                        help.enable();
                    break;
                }
            case 10:
                {
                    if (!info.enabled() && b->getLength() != 0 && b->getList(curList)->getLength() != 0)
                    {
                        info.setTile(b->getList(curList)->getTile(curTile));
                        info.enable();
                    }
                    else
                    {
                        info.disable();
                    }
                    break;
                }
            case 'q':
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
        info.render();
        help.render();

        wrefresh(cmdwin);
        wrefresh(boardwin);
        refresh();
    }

    save_all(boards);
    endwin(); // stop curses context

    return 0;
}
