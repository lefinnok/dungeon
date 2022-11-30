/*
This is the main script
*/
#include "databases.h"
#include <iostream>
#include "io.h"
#include "saveload.h"
#include "screens.h"
#include "uielements.h"
using namespace std;
using namespace dg;

//MAIN GAME INITIALIZATION
int main_init(){
	EXIT = 0;
	loadInit();
	curses_init();
	new titlescreen("title_screen");
	SCREENSTACK.push_back("title_screen");
	printat("what is the problem?",8,16);
	return 0;
}

//MAIN GAME WRAPUP (deconstruction, saving, and stuff)
int main_wrap(){
	curses_wrapup();
	loadWrap();
	dynoval_wrap();
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
