#include <map>
#include <string>
#include <list>
#include "databases.h"
using namespace std;

namespace dg{
	class sprite;
	class screen;
	int EXIT;
	bool DEBUG = true;
	map<string,sprite*> SPRITEDB;
	map<string,screen*> ACTIVESCREENS;
	list<string> SCREENSTACK;
}
