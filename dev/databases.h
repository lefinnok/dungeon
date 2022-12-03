#ifndef _DATABASES_H_
#define _DATABASES_H_
#include <map>
#include <string>
#include <list>
namespace dg{
	class sprite;
	class screen;
	class dynamicvalue;
	class mob;
	extern bool DEBUG;
	extern int EXIT;
	extern int SCREENX;
	extern int SCREENY;
	extern mob* PLAYER;
	//where loaded of sprite is stored, it can be referenced and displayed in spread instances, but don't have to store the copies in memory
	extern std::map<std::string,sprite*> SPRITEDB;
	//a map of initiated screen objects to store constructed screens, and be referenced by the screen stack
	extern std::map<std::string,screen*> ACTIVESCREENS;
	//a stack of screens to be displayed and printed,the first in the list will be printed first(at the very bottom), and the last will be at the top, and the controls from getch (unless it is global control such as resize and such) will always go to the top most screen in the screen stack
	extern std::list<std::string> SCREENSTACK;
	//global integers
	extern std::map<std::string,dynamicvalue*> VALDB;
	
}
#endif
