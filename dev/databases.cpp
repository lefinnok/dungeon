#include <map>
#include <string>
#include <list>
#include "databases.h"
using namespace std;

namespace dg{
	class sprite;
	class screen;
	class dynamicvalue;
	int EXIT;
	bool DEBUG = true;
	int SCREENX;
	int SCREENY;
	map<string,sprite*> SPRITEDB;
	map<string,screen*> ACTIVESCREENS;
	map<string,dynamicvalue*> VALDB;
	list<string> SCREENSTACK;
}
