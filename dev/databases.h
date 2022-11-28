#ifndef _DATABASES_H_
#define _DATABASES_H_
#include <map>
#include <string>
#include <list>
namespace dg{
	class sprite;
	class screen;
	extern bool DEBUG;
	extern int EXIT;
	extern std::map<std::string,sprite*> SPRITEDB;
	//a map of initiated screen objects to store constructed screens, and be referenced by the screen stack
	extern std::map<std::string,screen*> ACTIVESCREENS;
	//a stack of screens to be displayed and printed,the first in the list will be printed first(at the very bottom), and the last will be at the top, and the controls from getch (unless it is global control such as resize and such) will always go to the top most screen in the screen stack
	extern std::list<std::string> SCREENSTACK;

}
#endif
