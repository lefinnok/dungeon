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
			attributes();
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
			equipment();
			//called when the equipment is used against a target
			virtual void use(mob* target);
	};
	class melee_weapon:equipment{
		public:
			//constructor
			melee_weapon();
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
			mob();
			//deconstructor
			~mob();
		private:
			int base_hp;
			int base_ac;
			attributes attr;
			std::string armor;
			std::string weapon;
	};
}
#endif
