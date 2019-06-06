#include <iostream>

#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"
#include "CTable.h"
#include "CCursor.h"

int main() {

    CNumber n1("4");
    CString s1("Hello World!");
    CFunction f1("=Sin(3)");
    CFunction f2("=cin(3)");
    COperation o1("=3+4");
    COperation o2("=3-4");
    COperation o3("=3/4");
    COperation o4("=3*4");

    std::cout << "----------------------------" << std::endl;
    std::cout << n1 << std::endl;
    std::cout << s1 << std::endl;
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;
    std::cout << o1 << std::endl;
    std::cout << o2 << std::endl;
    std::cout << o3 << std::endl;
    std::cout << o4 << std::endl;

    initscr();
    cbreak();
    noecho();
    CTable t1;
    auto * c = new CCursor(' ', stdscr);
    int key = 0, x, y, i;
    char arr[50];
    while (key != 27) {
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
            arr[i] = '\0';

            move(0, 7);
            hline(' ', getmaxx(stdscr));
            move(1, 8);
            hline(' ', getmaxx(stdscr));
            mvprintw(1, 8, arr);

            c->Display();
            t1.SaveCell(stdscr, std::string(arr));
        }

        c->Display();
        t1.DisplayContent();

        getyx(stdscr, y, x);
        move(2, 0);
        hline(' ', getmaxx(stdscr));
        printw("Y: %d, X: %d", y, x);

        c->Display();
        std::pair<int, int> fakeCoo = t1.GetCoordinates(stdscr);
        move(3, 0);
        hline(' ', getmaxx(stdscr));
        printw("Y: %d, X: %d", fakeCoo.first, fakeCoo.second);

        c->Display();
        refresh();
    }


    //todo linkovani
    //todo cykly
    //todo agregacni fce
    //todo ukladani do souboru

    //todo kazda bunka teda set rodicu


    //todo kdyz se zmackne enter tak do inputu se napise to co bylo uz v bunce
    //todo v outputu se vzdycky bude zobrazovat co je raw v bunce?

    //todo pouzivat pair?
    //todo rozdelit na vice oken?

    delete c;
    endwin();
    t1.PrintArr();

    return 0;
}