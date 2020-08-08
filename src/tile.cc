#include "tile.hh"

Tile::Tile(const std::string &title, const std::string &desc) :
    m_title(title),
    m_desc(desc)
{}

void Tile::setTitle(const std::string &title)
{
    m_title = title;
}

void Tile::setDesc(const std::string &desc)
{
    m_desc = desc;
}

void Tile::render(WINDOW *w, int starty, int startx, int endx)
{
    std::string print = m_title;
    if ((int)print.length() > endx - startx)
    {
        print = print.substr(0, endx - startx - 3);
        print.append("...");
    }

    if (m_desc.length() != 0)
        wattron(w, A_UNDERLINE);
    mvwprintw(w, starty, startx, print.c_str());
    wattroff(w, A_UNDERLINE);
}
