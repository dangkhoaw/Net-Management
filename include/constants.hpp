#ifndef CONSTANTS
#define CONSTANTS 1

#include <atomic>
#include <mutex>

namespace Menu
{
    constexpr int MENUSTAFF = 7;
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

namespace Globals
{
    inline std::atomic<bool> showRemainingTime = true;
    inline std::atomic<bool> showUsageTime = true;
    inline std::atomic<bool> isChangingPassword = false;
    inline std::atomic<bool> isViewingInfo = false;
    inline std::atomic<bool> isOrdering = false;

    inline bool isChangedOrder = true;
    inline bool firstOrder = true;

    static std::mutex mtx;
}

#endif
