#include <iostream>

#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"
#include "CTable.h"
#include "CCursor.h"

int main() {

    CNumber n1(4);
    CString s1("Hello World!");
    CFunction f1("=Sin(3)");
    CFunction f2("=cin(3)");
    COperation o1("=3+4");

    std::cout << "----------------------------" << std::endl;
    std::cout << n1 << std::endl;
    std::cout << s1 << std::endl;
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;
    std::cout << o1 << std::endl;

    initscr();
    cbreak();
    noecho();
    CTable t1;
    auto * c = new CCursor(' ', stdscr);
    int key = 0, x, y, i;
    char arr[50];
    while (key != 'x') {
        key = c->Move();
        if(key == 10) { //ENTER
            for (char & j : arr)
                j = ' ';
            i = 0, y = 0, x = 7;
            move(y, x++);
            while(true) {
                key = wgetch(stdscr);
                if(key == 10)
                    break;
                else if (key == KEY_BACKSPACE) {
                    i--;
                    if(i <= 0)
                        i = 0;
                    arr[i] = '\0';
                    x--;
                    if(x < 7)
                        x = 7;
                    mvprintw(y, x, " ");
                } else if (32 <= key && key <= 126){
                    arr[i++] = (char) key;
                    mvprintw(y, x++, "%c", key);
                }
            }
            move(0, 7);
            hline(' ', getmaxx(stdscr));
            move(1, 8);
            hline(' ', getmaxx(stdscr));
            arr[i] = '\0';
            mvprintw(1, 8, arr);
        }

        c->Display();
        refresh();
    }

    //todo ukladat si to 2D pole?
    //todo kazda bunka teda set rodicu

    endwin();
    return 0;
}