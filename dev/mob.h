#ifndef _MOB_H_
#define _MOB_H_
#include <map>
#include <vector>
#include <string>
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
			int equipbbase_ac();
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
			//deconstructor
			//~mob();
			void cout_stats();
			int mobbase_hp();
			int mobbase_ac();
			int mobagility();
			int mobstrength();
			int mobpresence();
			int mobtoughness();
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
