/*
This is the main script
*/
#include "databases.h"
#include <iostream>
#include "io.h"
#include "saveload.h"
using namespace std;
using namespace dg;


int main_init(){
	loadInit();
	return 0;
}


int main_wrap(){
	loadWrap();
	return 0;
}
int main(){
	main_init();
	ioloop();
	main_wrap();
    return 0;
}
