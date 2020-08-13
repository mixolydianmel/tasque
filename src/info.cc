#include "info.hh"

Info::Info(WINDOW *w) :
    m_enabled(false),
    m_tile(new Tile(""))
{
    m_infowin = newwin(w->_maxy - 10, w->_maxx - 90, w->_begy + 5, w->_begx + 45);
}

void Info::setTile(Tile *t)
{
    m_tile = t;
}

void Info::render()
{
    if (m_enabled)
    {
        wclear(m_infowin);

        wattron(m_infowin, A_BOLD);
        mvwprintw(m_infowin, 1, 1, m_tile->getTitle().c_str());
        wattroff(m_infowin, A_BOLD);

        std::string desc = m_tile->getDesc();
        for (size_t i = m_infowin->_maxx - 2; i < desc.length(); i += m_infowin->_maxx - 2)
        {
            desc.insert(i, 1, '\n');
        }

        wattron(m_infowin, A_ITALIC);
        mvwprintw(m_infowin, 3, 1, desc.c_str());
        wattroff(m_infowin, A_ITALIC);

        mvwprintw(m_infowin, m_infowin->_maxy - 1, 1, "Press `Return` to continue...");

        box(m_infowin, 0, 0);
        mvwhline(m_infowin, 2, 1, ACS_HLINE, m_infowin->_maxx - 1);
        mvwhline(m_infowin, m_infowin->_maxy - 2, 1, ACS_HLINE, m_infowin->_maxx - 1);

        wrefresh(m_infowin);
    }
}
