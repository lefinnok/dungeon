/*
This is the main script
*/
#include "databases.h"
#include <iostream>
#include "io.h"
#include "saveload.h"
using namespace std;
using namespace dg;

//MAIN GAME INITIALIZATION
int main_init(){
	EXIT = 0;
	loadInit();
	curses_init();
	return 0;
}

//MAIN GAME WRAPUP (deconstruction, saving, and stuff)
int main_wrap(){
	curses_wrapup();
	loadWrap();
	return 0;
}

//MAIN GAME LOOP
void main_loop(){
	while(!EXIT){
		ioloop();
	}
}

int main(){
	main_init();
	main_loop();
	main_wrap();
    return 0;
}
