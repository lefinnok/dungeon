#include <iostream>
#include <stdio.h>

#ifdef WINDOWS
#include <conio.h>
#else
#include <curses.h>
//#include "libs/llvm-15.0.2.src/BinaryFormat/ELF.h"
#endif
using namespace std;

namespace dg{
    //initialize ncurses library
    int curses_init(){
        initscr();
        timeout(-1);
        
        return 0;
    }
    int curses_wrapup(){
        endwin();
        return 0;
    }
    int ioloop(){
        curses_init();
        for(int i = 0; i < 10; i++){
            printw("%d",getch());
            
        }
        curses_wrapup();
        return 0;
    }
    
}