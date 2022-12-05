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
    mob* PLAYER = NULL;
	bool DEBUG = false;
	int SCREENX;
	int SCREENY;
    map<string,mob*> MOBTEMPLATES;
	map<string,mob*> MOBDB;
    map<string,item*> ITEMDB;
	map<string,sprite*> SPRITEDB;
	map<string,screen*> ACTIVESCREENS;
	map<string,dynamicvalue*> VALDB;
	//map<string,equipment*>EQUIPMENT_TEMPLATES;
	list<string> SCREENSTACK;
    list<wstring> SYSTEMLOG;
    void outlog(wstring outstring){SYSTEMLOG.push_back(outstring);}
    list<mob*>ENEMIES;
    map<string,int>LOOTTABLE;
}
