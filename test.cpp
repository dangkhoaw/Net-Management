#include "date.h"
#include "mtime.h"

int main(int argc, char const *argv[])
{
    Date date;
    date = date.getCurrentDate();
    Time time;
    time = time.getCurrentTime();
    cout << date << " " << time << endl;
    return 0;
}
