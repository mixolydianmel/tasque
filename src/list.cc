#include "list.hh"

List::List(const std::string &title) :
    m_title(title)
{
    m_tiles = {};
    m_length = 0;
}

void List::addTile(Tile *t)
{
    m_tiles.push_back(t);
    m_length++;
}

void List::delTile(unsigned int index)
{
    m_tiles.erase(m_tiles.begin() + index);
    m_length--;
}

void List::delTiles(unsigned int start, unsigned int end)
{
    m_tiles.erase(m_tiles.begin() + start, m_tiles.begin() + end);
    m_length -= end - start;
}

void List::setTitle(const std::string& title)
{
    m_title = title;
}

void List::render(WINDOW *w, int starty, int startx, int endy, int endx, bool selected)
{
    std::string print = m_title;
    if ((int)print.length() > endx - startx)
    {
        print = print.substr(0, endx - startx - 3);
        print.append("...");
    }

    if (selected)
    {
        wattron(w, A_ITALIC);
        wattron(w, COLOR_PAIR(T_COLOR_SELECTED));
    }
    mvwprintw(w, starty, startx, print.c_str());
    wattroff(w, A_ITALIC);
    wattroff(w, COLOR_PAIR(T_COLOR_SELECTED));

    mvwvline(w, starty, endx, ACS_VLINE, endy - starty);
    if (selected)
        wattron(w, COLOR_PAIR(T_COLOR_SELECTED));
    mvwhline(w, starty + 1, startx, ACS_HLINE, endx - startx);
    wattroff(w, COLOR_PAIR(T_COLOR_SELECTED));

    wrefresh(w);
}
