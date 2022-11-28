#include <iostream>
#include "mob.h"
#include <map>
#include <string>

using namespace std;
using namespace dg;
namespace dg{
	// modifier for converting abilities to the chance of success rate.
	// If the ability is 1-4, then the success rate of that ability decrease by 3
	// If the ability is 5-6, then the success rate of that ability decrease by 2
	// If the ability is 7-8, then the success rate of that ability decrease by 1
	// If the ability is 9-12, then the success rate of that ability remains no change
	// If the ability is 13-14, then the success rate of that ability increase by 1
	// If the ability is 15-16, then the success rate of that ability increase by 2
	// If the ability is 17-20, then the success rate of that ability increase by 3
	map<int,int> modifier_convert={
		{1,-3},
		{2,-3},
		{3,-3},
		{4,-3},
		{5,-2},
		{6,-2},
		{7,-1},
		{8,-1},
		{9,0},
		{10,0},
		{11,0},
		{12,0},
		{13,1},
		{14,1},
		{15,2},
		{16,2},
		{17,3},
		{18,3},
		{19,3},
		{20,3}
	};
	

	//This is a constructor to make an instance of the class(and object) from the class, it's generally not written as such
	/*
	//function to set the class mob
	mob::mob(){
		
		// mobs detail like name, description
		class mob{
			string mob_name;
			string mob_description;
		
		
		};
	}*/
	

	//converting agility to its modifier, it uses moidier_convert to convert, return the modifier at the end
	//agility is the input
	//agility_mod is the output
	int attributes::getAgilityMod() {
		return modifier_convert[agility];
	
	}
	
	//converting presence to its modifier, it uses moidier_convert to convert, return the modifier at the end
	//presence is the input
	//presence_mod is the output
	int attributes::getStrengthMod() {
	    return modifier_convert[strength];
	                         
	}  
	
	//converting strength to its modifier, it uses moidier_convert to convert, return the modifier at the end
	//strength is the input
	//strengthe_mod is the output
	int attributes::getToughnessMod() {
	    return modifier_convert[toughness];
	                         
	}  
	//converting toughness to its modifier, it uses moidier_convert to convert, return the modifier at the end
	//toughness is the input
	//toughness_mod is the output
	int attributes::getPresenceMod() {
	    return modifier_convert[presence];
    	                     
	}
	
	//setting the base value of a mob and its name
	//the name, base health, base armor, base agility, base presence, base strength, base toughness of the mob is input
	//the protected content of the mob is output
	mob::mob(string nm, int hp, int ac, int ag, int pr, int st, int tn){
		name = nm;
		base_hp = hp;
		base_ac = ac;
		attr.agility = ag;
		attr.presence = pr;
		attr.strength = st;
		attr.toughness = tn;
	}

	//print out the stats of the mob
	//input is the mob's basic value and name
	//output is the mob's basic value and name in the format of:
	//===mob's name===
	//HP: mob's base health AC: mob's base armor
	//Agility: mob's agility (modifier for agility)
	//Strength: mob's strength (modifier for strength)
	//Presence: mob's presence (modifier for presence)
	//Toughness: mob's toughness (modifier for toughness)
	void mob::cout_stats(){
		cout<<"==="<<name<<"==="<<endl;
		cout<<"HP: "<<base_hp<<" AC: "<<base_ac<<endl;
		cout<<"Agility: "<<attr.agility<<" ("<<attr.getAgilityMod()<<")"<<endl;
		cout<<"Strength: "<<attr.strength<<" ("<<attr.getStrengthMod()<<")"<<endl;
		cout<<"Presence: "<<attr.presence<<" ("<<attr.getPresenceMod()<<")"<<endl;
		cout<<"Toughness: "<<attr.toughness<<" ("<<attr.getToughnessMod()<<")"<<endl;
	}

	//setting the base value of an equipment and its name
	//the name, base health, base armor, base agility, base presence, base strength, base toughness of the equipment is input
	//the protected content of the equipment is output
	equipment::equipment(string nm, int hp, int ac, int ag, int pr, int st, int tn) {
		eqname = nm;
		eqbase_hp = hp;
		eqbase_ac = ac;
		eqattr.agility = ag;
		eqattr.presence = pr;
		eqattr.strength = st;
		eqattr.toughness = tn;
	}

	//print out the stats of the equipment
	//input is the equipment's basic value and name
	//output is the equipment's basic value and name in the format of:
	//===equipment's name===
	//HP: equipment's base health AC: equipment's base armor
	//Agility: equipment's agility (modifier for agility)
	//Strength: equipment's strength (modifier for strength)
	//Presence: equipment's presence (modifier for presence)
	//Toughness: equipment's toughness (modifier for toughness)
	void equipment::cout_eqstats() {
		cout << "===" << eqname << "===" << endl;
		cout << "Added HP: " << eqbase_hp << "Added AC: " << eqbase_ac << endl;
		cout << "Added Agility: " << eqattr.agility << " (" << eqattr.getAgilityMod() << ")" << endl;
		cout << "Added Strength: " << eqattr.strength << " (" << eqattr.getStrengthMod() << ")" << endl;
		cout << "Added Presence: " << eqattr.presence << " (" << eqattr.getPresenceMod() << ")" << endl;
		cout << "Added Toughness: " << eqattr.toughness << " (" << eqattr.getToughnessMod() << ")" << endl;
	}

	//boost on mobs with equipments
	void equipment::use(mob* target) {
		
	}

}
int main(void){
	mob goblin1("Goblin 1",10,8,16,3,10,9);
	goblin1.cout_stats();

	mob goblin2("Goblin 2" ,20,16,16,6,20,9);
	goblin2.cout_stats();

	equipment leather1("Leather armor", 100, 10, 2, 2, 2, 2);
	leather1.cout_eqstats();

	return 0;
}

