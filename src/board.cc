#include "board.hh"

Board::Board(const std::string &title) :
    m_title(title)
{
    m_lists = {};
    m_length = 0;
}

void Board::setTitle(const std::string &title)
{
    m_title = title;
}

void Board::addList(List *l)
{
    m_lists.push_back(l);
    m_length++;
}

void Board::delList(unsigned int index)
{
    m_lists.erase(m_lists.begin() + index);
    m_length--;
}

void Board::delLists(unsigned int start, unsigned int end)
{
    m_lists.erase(m_lists.begin()+start, m_lists.begin()+end);
    m_length -= end - start;
}

void Board::render(WINDOW *w, int x)
{
    wattron(w, A_BOLD);
    mvwprintw(w, 1, 1, m_title.c_str());
    wattroff(w, A_BOLD);

    box(w, 0, 0);
    mvwhline(w, 2, 1, ACS_HLINE, x - 2);

    wrefresh(w);
}
