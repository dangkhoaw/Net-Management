#ifndef CONSTANTS
#define CONSTANTS 1

#include <atomic>
#include <mutex>

namespace Constants
{
    namespace Menu
    {
        constexpr int MENUSTAFF = 8;
        constexpr int MENUCUSTOMERMANAGER = 5;
        constexpr int MENUCOMPUTERMANAGER = 4;
        constexpr int MENUCUSTOMER = 4;
        constexpr int MENUDISH = 4;
        constexpr int MENUFOOD = 7;
        constexpr int MENUDRINK = 7;
        constexpr int MENUQUANTITY = 4;
        constexpr int MENUREVENUE = 4;
        constexpr int MENUSELECTTYPEOFCOMPUTER = 4;
    }

    namespace Keys
    {
        constexpr int KEY_UP = 72;
        constexpr int KEY_DOWN = 80;
        constexpr int KEY_LEFT = 75;
        constexpr int KEY_RIGHT = 77;
        constexpr int KEY_ENTER = 0x0D;
        constexpr int KEY_BACKSPACE = 0x08;
        constexpr int KEY_ESC = 0x1B;
        constexpr int KEY_TAB = 0x09;
    }

    namespace ANSI
    {
        namespace Foreground
        {
            constexpr const char *RED = "\x1b[38;2;255;51;51m";
            constexpr const char *GREEN = "\x1b[38;2;51;255;51m";
            constexpr const char *YELLOW = "\x1b[38;2;255;255;51m";
            constexpr const char *WHITE = "\x1b[38;2;255;255;255m";
            constexpr const char *BLACK = "\x1b[38;2;0;0;0m";
        }
        namespace Background
        {
            constexpr const char *RED = "\x1b[48;2;255;51;51m";
            constexpr const char *GREEN = "\x1b[48;2;51;255;51m";
            constexpr const char *YELLOW = "\x1b[48;2;255;255;51m";
            constexpr const char *WHITE = "\x1b[48;2;255;255;255m";
            constexpr const char *BLACK = "\x1b[48;2;0;0;0m";
        }
        namespace Style
        {
            constexpr const char *BOLD = "\x1b[1m";
        }

        constexpr const char *RESET = "\x1b[0m";
    }

    namespace Globals
    {
        inline std::atomic<bool> showRemainingTime = true;
        inline std::atomic<bool> showUsageTime = true;
        inline std::atomic<bool> isChangingPassword = false;
        inline std::atomic<bool> isViewingInfo = false;
        inline std::atomic<bool> isOrdering = false;

        inline bool isChangedOrder = true;
        inline bool firstOrder = true;

        inline std::mutex mtxTime;
        inline std::mutex mtxCustomer;
        inline std::mutex mtxComputer;
    }
}

#endif
