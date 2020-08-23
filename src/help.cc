#include "help.hh"
#include <curses.h>

Help::Help(WINDOW *w) :
    m_enabled(false)
{
    m_keybinds["h     "] = "Select the list to the left";
    m_keybinds["j     "] = "Select the next tile down in the current list";
    m_keybinds["k     "] = "Select the next tile up in the current list";
    m_keybinds["l     "] = "Select the list to the right";
    m_keybinds["H     "] = "Select the previous board";
    m_keybinds["L     "] = "Select the next board";
    m_keybinds["at    "] = "Add a tile to the current list";
    m_keybinds["al    "] = "Add a list to the current board";
    m_keybinds["ab    "] = "Add another board";
    m_keybinds["dt    "] = "Delete the current tile";
    m_keybinds["dl    "] = "Delete the current list";
    m_keybinds["db    "] = "Delete the current board";
    m_keybinds["et    "] = "Modify the current tile";
    m_keybinds["el    "] = "Modify the current list";
    m_keybinds["eb    "] = "Modify the current board";
    m_keybinds["s     "] = "Saves all boards";
    m_keybinds["?     "] = "Display help menu";
    m_keybinds["Return"] = "Display info for the currently selected tile";
    m_keybinds["q     "] = "Saves and quits the program";

    m_helpwin = newwin(m_keybinds.size() + 6, w->_maxx - 90, w->_begy + 5, w->_begx + 45);
}

void Help::render()
{
    if (m_enabled)
    {
        wclear(m_helpwin);

        wattron(m_helpwin, A_BOLD);
        mvwprintw(m_helpwin, 1, 1, "Help");
        wattroff(m_helpwin, A_BOLD);

        for (auto itr = m_keybinds.begin(); itr != m_keybinds.end(); itr++)
        {
            mvwprintw(m_helpwin, 3 + std::distance(m_keybinds.begin(), itr), 1, (itr->first + " : " + itr->second).c_str());
        }

        mvwprintw(m_helpwin, m_helpwin->_maxy - 1, 1, "Press `?` to continue...");

        box(m_helpwin, 0, 0);
        mvwhline(m_helpwin, 2, 1, ACS_HLINE, m_helpwin->_maxx - 2);
        mvwhline(m_helpwin, m_helpwin->_maxy - 2, 1, ACS_HLINE, m_helpwin->_maxx - 2);

        wrefresh(m_helpwin);
    }
}
