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
    int ioloop(){
        for(int i = 0; i < 10; i++){
            printf("%c", getch());
        }
        return 0;
    }
}