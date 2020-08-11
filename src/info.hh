#ifndef TASQUE_INFO_HH
#define TASQUE_INFO_HH

#include <ncurses.h>

#include "tile.hh"

class Info
{
    public:
        // Constructor (takes window to draw info box within)
        Info(WINDOW *w);

        // Sets the tile to display in the info box
        void setTile(Tile *t);

        // Enables the info box
        inline void enable() { m_enabled = true; }
        // Disables the info box
        inline void disable() { m_enabled = false; }

        // Returns true if the info box is enabled
        inline bool enabled() { return m_enabled; }

        // Draws the info box if enabled
        void render();
    private:
        bool m_enabled;
        Tile *m_tile;

        WINDOW *m_infowin;
};

#endif /* TASQUE_INFO_HH */
