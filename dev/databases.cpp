#include <map>
#include <string>
#include <list>
#include "databases.h"
using namespace std;

namespace dg{
	class sprite;
	class screen;
	class dynamicvalue;
	class mob;
    class item;
	int EXIT;
	bool DEBUG = true;
	int SCREENX;
	int SCREENY;
	map<string,mob*> MOBDB;
    map<string,item*> ITEMDB;
	map<string,sprite*> SPRITEDB;
	map<string,screen*> ACTIVESCREENS;
	map<string,dynamicvalue*> VALDB;
	//map<string,equipment*>EQUIPMENT_TEMPLATES;
	list<string> SCREENSTACK;
}
