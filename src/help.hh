#ifndef TASQUE_HELP_HH
#define TASQUE_HELP_HH

#include <ncurses.h>
#include <map>
#include <string>

class Help
{
    public:
        // Constructor (takes window to draw help window within)
        Help(WINDOW *w);

        // Enables the help window
        inline void enable() { m_enabled = true; }
        // Disables the help window
        inline void disable() { m_enabled = false; }

        // Returns true if the help window is enabled
        inline bool enabled() { return m_enabled; }

        // Draws the help window if enabled
        void render();
    private:
        bool m_enabled;
        std::map<std::string, std::string> m_keybinds;

        WINDOW *m_helpwin;
};

#endif /* TASQUE_HELP_HH */
