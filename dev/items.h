#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <string>
#include <list>
#include <map>
//#include "mob.h"
using namespace std;
//using namespace dg;
namespace dg{
	//class
	class mob;
	class status_effect;
	mob::list<status_effect*>* getstatuslist();
	
	//class thing{};
	class status_effect{
		public:
			status_effect(mob* host,int duration, int val);
			~status_effect();
			virtual void tick();
		protected:
			mob* host;
			int duration;
			int value;
	};
	class heal:public status_effect{
		public:
			void tick();
	};

	class action{
		public:
			action(map<string, string> arguments);
			virtual void trigger(mob* actor);
		protected:
			map<string,string> arguments;

	};
	class apply_status: public action{
		public:
			void trigger(mob* actor);
		
	};
	class item{
		public:
			item(string name);
			item(string name, action* act);
		protected:
			string name;
			action* act=NULL;
	};
	class modifier {
		public:
			modifier(string type, int val);
			string type;
			int val;

	};
	class consumable:public item{
		
	};
	class equipment:public item{
		public:
			equipment(string name, list<modifier> modifiers);
			void use();
		protected:
			string name;
			list<modifier> modifiers;
	};

	class potion:public consumable{
		//public:
			
	};
}

#endif
