#ifndef TASQUE_LIST_HH
#define TASQUE_LIST_HH

#include <vector>
#include <string>
#include <ncurses.h>

#include "tile.hh"

class List
{
    public:
        // Creates a list with the designated title.
        List(const std::string &title);

        // Returns the title of the list.
        inline std::string getTitle() { return m_title; }
        // Returns the number of tiles in the list, counting from 1.
        inline unsigned int getLength() { return m_length; }

        // Returns the tile at the specified index.
        inline Tile *getTile(unsigned int index) { return m_tiles.at(index); }
        // Adds a tile to the list.
        void addTile(Tile *t);
        // Removes a tile from the list at the designated index.
        void delTile(unsigned int index);
        // Removes tiles from the index at start to the index before end (end is not inclusive).
        void delTiles(unsigned int start, unsigned int end);

        // Sets the title of the list.
        void setTitle(const std::string& title);

        // Draws the list.
        void render(WINDOW *w, int starty, int startx, int endy, int endx);
    private:
        std::vector<Tile*> m_tiles;
        std::string m_title;
        unsigned int m_length;
};

#endif /* TASQUE_LIST_HH */
