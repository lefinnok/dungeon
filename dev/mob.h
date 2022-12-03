#ifndef _MOB_H_
#define _MOB_H_
#include <map>
#include <vector>
#include <string>
#include <list>
namespace dg{
	//references and inspiration from mork borg
	// map for converting attribute to modifer
	extern std::map<int,int> modifier_convert;
	// mobs name and description
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

	class modifier {
		public:
			int type;
			int val;

	};

	//can implement later if have time
	class effect{
		
	};
	class equipment{
		public:
			//constructor
			equipment(std::string, int, int, int, int, int, int);
			void cout_eqstats();
			std::string equipname();
			int equipbase_hp();
			int equipbase_ac();
			int equipagility();
			int equipstrength();
			int equippresence();
			int equiptoughness();

			//called when the equipment is used against a target
			virtual void use(mob* target);
		protected:
			std::string eqname;
			int eqbase_hp;
			int eqbase_ac;
			attributes eqattr;
	};
	class melee_weapon:equipment{
		public:
			//constructor
			melee_weapon(std::string, int, int, int, int, int);
			void use(mob* target, attributes* user_attributes);
	};
	//implement later
	class appendage{
		public:
			//constructor
			appendage();
			equipment eq;
					
	};

	class mob{
		public:
			//constructor
			mob(std::string, int, int, int, int, int, int);
			std::vector<equipment> eqlist;
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
			
			//get the maxstats of mob
			//input is the corresponding stats in the list of equipment
			//output is the corresponding equipment's base stats + mob stats
			int getmaxhealth();
			int getmaxac();
			int getmaxagility();
			int getmaxstrength();
			int getmaxpresence();
			int getmaxtoughness();
			

			//set current stats' default is the mob maxstats
			int result_health = getmaxhealth();
			int result_ac = getmaxac();
			int result_agilty = getmaxagility();
			int result_strength = getmaxstrength();
			int result_presence = getmaxpresence();
			int result_toughness = getmaxtoughness();
			
		protected:
			std::string name;
			int base_hp;
			int base_ac;
			attributes attr;
			std::string armor;
			std::string weapon;
	};
}
#endif
