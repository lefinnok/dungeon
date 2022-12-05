#ifndef _MOB_H_
#define _MOB_H_
#include <map>
#include <vector>
#include <string>
#include <list>
using namespace std;
//#include "items.h"
//using namespace dg;
namespace dg{
	//class equipment;
	//class modifier;
	//class status_effect;
	//references and inspiration from mork borg
	// map for converting attribute to modifer
	extern std::map<int,int> modifier_convert;



	// mobs name and description
	//class thing{};
	class mob;
	class attributes{
		public:
			//constructor
			//attributes();
			int agility;
			int presence;
			int strength;
			int toughness;
			//get modifer from attribute
			int getAgilityMod();
			int getPresenceMod();
			int getStrengthMod();
			int getToughnessMod();	
	};

	
	/*class equipment;
	class appendage{
		public:
			//constructor
			appendage();
			equipment eq;
					
	};*/
	

	class status_effect;
	class equipment;
	class modifier;
	class item;
	class mob{
		public:
			//constructor
            mob(std::string,int,int,int,int,bool);
			mob(std::string, int, int, int, int);
			~mob();

			int getcurrenthitpoint();
			//std::vector<equipment> eqlist;
			//deconstructor
			//~mob();
			
			// printout the stat of mob
			//input is the protected members of mob
			//output is the stats with the format
			void cout_stats();

			// get the mob's protected member without declaring derived classes or child classes
			//intput is the corresponding protected member from mob
			//output is the member but not protected
			int mobbase_hp();
			int mobbase_ac();
			int mobagility();
			int mobstrength();
			int mobpresence();
			int mobtoughness();
			
			//get the modified stats of mob
			//input is the corresponding stats in the list of equipment
			//output is the corresponding equipment's base stats + mob stats
			int getmaxhitpoint();
			int getmodac();
			int getmodagility();
			int getmodstrength();
			int getmodpresence();
			int getmodtoughness();
		    
            int getagilitymod();
            int getstrengthmod();
            int getpresencemod();
            int gettoughnessmod();

			//set current stats' default is the mob maxstats
			//Note: These should be set in constructor, this will not be called
			/*
			int result_health = getmaxhealth();
			int result_ac = getmaxac();
			int ult_agilty = getmaxagility();
			int result_strength = getmaxstrength();
			int result_presence = getmaxpresence();
			int result_toughness = getmaxtoughness();
			*/
			list<status_effect*>* getstatuslist();
			void modifyhitpoint(int);
			string gethandle();
			void dead();
            void additem(string itemname);
            void addstatus(status_effect*);
            map<string,item*>* getinventory();
            void equip(string inventory_handle);
            void unequip(string inventory_handle);
            void addimodifier(modifier* imodif);
            list<modifier*> gettotalmodifiers();
            void airound();
            list<string>* getequipments();
            map<string,item*> getusable();
            bool isplayer();
            void setplayer();
            mob* copy();
            void settemplate();
		protected:
			std::string handle;
			int hitpoint;
			//int ac;
			attributes attr;
			std::string armor;
			std::string weapon;
			//std::list<equipment> eqlist;
            list<string> equipments;
			std::map<string,item*> inventory;
			std::list<status_effect*> active_statuses;
			list<modifier*> inherent_modifiers;
            bool player = false;
            bool istemplate = false;

	};
    mob* randommobfromtemplate();
	class status_effect{
		public:
			status_effect(string name, mob* host,int duration, int val);
			~status_effect();
			virtual void tick();
            string getname();
            int getduration();
            int getvalue();
		protected:
            string name;
			mob* host;
			int duration;
			int value;
	};

	class heal:public status_effect{
		public:
            using status_effect::status_effect;
			void tick();
	};

	class action{
		public:
			action(map<string, string> arguments);
			virtual int trigger(mob* actor);
            //virtual action* copy;
		protected:
			map<string,string> arguments;

	};
	class apply_status: public action{
		public:
            using action::action;
			int trigger(mob* actor);
		
	};
    class strength_attack: public action{
        public:
            using action::action;
            int trigger(mob* actor);
    };
    
    class agility_attack: public action{
        public:
            using action::action;
            int trigger(mob* actor);
    };

    class presence_attack: public action{
        public:
            using action::action;
            int trigger(mob* actor);
    };

    class spell_cast: public action{
        public:
            using action::action;
            int trigger(mob* actor);
    };


	class item{
		public:
            ~item();
            //item(string name, list<modifier*> modifiers,list<string> tags);
			item(string name, action* act, list<modifier*> modifiers, list<string> tags);
            void setinventory(map<string,item*>* pi);
            void setowner(mob* owner);
            void setinventoryhandle(string handle);
            virtual item* copy();
            virtual int use();
            bool usable();
            string getname();
            string getinventoryhandle();
            void setistemplate(bool);
            list<modifier*>* getmodifiers();
            list<string>* gettags();
            string getappendage();
		protected:
            list<string> tags;
			string name;
			action* act=NULL;
            list<modifier*> modifiers;
            mob* owner = NULL;
            map<string,item*>* parentinventory = NULL;
            string inventory_handle;
            bool istemplate = false;
	};

	class modifier {
		public:
            ~modifier();
			modifier(string type, string val);
			string type;
			string val;
            list<modifier*>* parentlist = NULL;

	};

	class consumable:public item{
        public:
            using item::item;
            virtual item* copy();
            int use();
		
	};

	/*class equipment:public item{
		public:
			equipment(string name, list<modifier> modifiers);
			void use();
		protected:
			string name;
			list<modifier*> modifiers;
	};*/

	/*class potion:public consumable{
		//public:
			
	};*/
	
}
#endif
