#ifndef TASQUE_BOARD_HH
#define TASQUE_BOARD_HH

#include <vector>
#include <string>
#include <ncurses.h>

#include "list.hh"

class Board
{
    public:
        // Create a board with the designated title.
        Board(const std::string &title);

        // Returns the vector containing the lists within the board.
        inline std::vector<List*> &getLists() { return m_lists; }
        // Returns the title of the board.
        inline std::string getTitle() { return m_title; }
        // Returns the number of lists in the board, counting from 1.
        inline unsigned int getLength() { return m_length; }

        // Sets the title of the board.
        void setTitle(const std::string &title);

        // Returns the list at the specified index.
        inline List *getList(unsigned int index) { return m_lists.at(index); }
        // Adds a list to the board.
        void addList(List *l);
        // Removes a list from the bord at the designated index.
        void delList(unsigned int index);
        // Removes lists from the index at start to the index before end (end is not inclusive).
        void delLists(unsigned int start, unsigned int end);

        // Draws the board.
        void render(WINDOW *w, int x);
    private:
        std::vector<List*> m_lists;
        std::string m_title;
        unsigned int m_length;
};

#endif /* TASQUE_BOARD_HH */
