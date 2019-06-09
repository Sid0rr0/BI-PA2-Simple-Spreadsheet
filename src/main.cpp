#include <iostream>

#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"
#include "CTable.h"
#include "CCursor.h"

#define MAX_LEN 50

int main() {

    initscr();
    cbreak();
    noecho();
    CTable t1;
    auto * c = new CCursor(' ', stdscr);
    int key = 0, x = 0, y = 0;

    getmaxyx(stdscr, y, x);
    move(2, 0);
    hline(' ', getmaxx(stdscr));
    printw("X_Max: %d, Y_Max: %d", x, y);
    move(6, 12);
    unsigned i;
    bool file = false;
    char arr[MAX_LEN];
    while (key != 27) {
        key = c->Move();

        if(key == 10 || (32 <= key && key <= 126)) { //ENTER

            for (char & j : arr)
                j = ' ';
            i = 0, y = 0, x = 7;
            //move(y, x++);

            std::pair<int, int> fakeCoo = t1.GetFakeCoordinates(stdscr);
            std::string content = t1.GetInput(fakeCoo.second, fakeCoo.first);
            mvprintw(0, 7, content.c_str());
            for (; i < content.length(); ++i) {
                arr[i] = content.at(i);
                x++;
            }

            while(true) {
                key = wgetch(stdscr);
                if(key == KEY_F(1)) {
                    arr[i] = '\0';
                    t1.SaveToFile(arr);

                    delete c;
                    endwin();
                    return 0;
                }

                if(key == KEY_F(2)) {
                    arr[i] = '\0';
                    t1.ReadFromFile(arr);
                    file = true;
                    break;
                }

                if(key == 10)
                    break;
                else if (key == KEY_BACKSPACE) {
                    if(i <= 0)
                        i = 0;
                    else
                        i--;
                    arr[i] = ' ';
                    if(x <= 7)
                        x = 7;
                    else
                        x--;
                    mvprintw(y, x, " ");
                } else if (32 <= key && key <= 126){
                    arr[i++] = (char) key;
                    mvprintw(y, x++, "%c", key);
                }
            }
            if(file)
                break;
            arr[i] = '\0';

            move(0, 7);
            hline(' ', getmaxx(stdscr));
            move(1, 8);
            hline(' ', getmaxx(stdscr));
            mvprintw(1, 8, arr);

            c->Display();
            t1.SaveCell(stdscr, std::string(arr));
        }

        t1.DisplayContent();
        c->Display();
        refresh();

        c->Display();
        std::pair<int, int> fakeCoo = t1.GetFakeCoordinates(stdscr);
        move(3, 0);
        hline(' ', getmaxx(stdscr));
        printw("X: %d, Y: %d", fakeCoo.first, fakeCoo.second);

        c->Display();
        refresh();
    }

    delete c;
    endwin();
    t1.PrintArr();

    return 0;
}