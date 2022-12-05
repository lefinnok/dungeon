#include "items.h"
//#include "mob.h"
#include <string>
#include <list>
#include <map>
using namespace dg;
using namespace std;
namespace dg{
	class mob;
	status_effect::status_effect(mob* hst,int dur, int val){
		host = hst;
		duration = dur;
		value = val;

	}
	status_effect::~status_effect(){
		host->getstatuslist()->remove(this);
	}
	void status_effect::tick(){
		duration--;
		if(duration<=0){delete(this);return;}
	}
	void heal::tick(){
		host->modifyhitpoint(value);
		status_effect::tick();
	}
	action::action(map<string, string> args){
		for(pair<string, string>p: args){
			arguments.insert(p);
		}
	}
	void action::trigger(mob* actor){}
	void apply_status::trigger(mob* actor){
		//all apply statuses should only be used on mobs
		

	}
}
