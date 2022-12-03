#include <iostream>
#include "mob.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace dg;
namespace dg{
	
	/*all comments will have the same format of: 
	use of this function
	input of this function
	output of this function*/


	/* modifier for converting abilities to the chance of success rate.
	input is the number u want to convert e.g modifier_covert[3]
	output is the value like for 3 it is -3*/
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
	

	/*converting agility to its modifier, it uses moidier_convert to convert, return the modifier at the end
	agility is the input
	value of agility after converted by the modifier_convert is the output*/
	int attributes::getAgilityMod() {
		return modifier_convert[agility];
	
	}
	
	/*converting presence to its modifier, it uses moidier_convert to convert, return the modifier at the end
	presence is the input
	value of presence after converted by the modifier_convert is the output*/
	int attributes::getStrengthMod() {
	    return modifier_convert[strength];
	                         
	}  
	
	/*converting strength to its modifier, it uses moidier_convert to convert, return the modifier at the end
	strength is the input
	value of strength after converted by the modifier_convert is the output*/
	int attributes::getToughnessMod() {
	    return modifier_convert[toughness];
	                         
	}  
	/*converting toughness to its modifier, it uses moidier_convert to convert, return the modifier at the end
	toughness is the input
	value of toughness after converted by the modifier_convert is the output output*/
	int attributes::getPresenceMod() {
	    return modifier_convert[presence];
    	                     
	}
	
	/*setting the base value of a mob and its name
	the name, base health, base armor, base agility, base presence, base strength, base toughness of the mob is input
	the protected member of the class mob is output*/
	mob::mob(string nm, int hp, int ac, int ag, int pr, int st, int tn){
		name = nm;
		base_hp = hp;
		base_ac = ac;
		attr.agility = ag;
		attr.presence = pr;
		attr.strength = st;
		attr.toughness = tn;
	}

	/*print out the stats of the mob
	input is the mob's basic value and name
	output is the mob's basic value and name in the format of:
	===mob's name===
	HP: mob's base health AC: mob's base armor
	Agility: mob's agility (modifier for agility)
	Strength: mob's strength (modifier for strength)
	Presence: mob's presence (modifier for presence)
	Toughness: mob's toughness (modifier for toughness)*/
	void mob::cout_stats(){
		cout<<"==="<<name<<"==="<<endl;
		cout<<"HP: "<<base_hp<<" AC: "<<base_ac<<endl;
		cout<<"Agility: "<<attr.agility<<" ("<<attr.getAgilityMod()<<")"<<endl;
		cout<<"Strength: "<<attr.strength<<" ("<<attr.getStrengthMod()<<")"<<endl;
		cout<<"Presence: "<<attr.presence<<" ("<<attr.getPresenceMod()<<")"<<endl;
		cout<<"Toughness: "<<attr.toughness<<" ("<<attr.getToughnessMod()<<")"<<endl;
	}
	
	/*get the mob's protected member without declaring derived classes or child classes
	intput is the corresponding protected member from mob
	output is the member but not protected*/
	int mob::mobbase_hp(){
		return base_hp;
	}
	int mob::mobbase_ac() {
		return base_ac;
	}
	int mob::mobagility() {
		return attr.agility;
	}
	int mob::mobstrength() {
		return attr.strength;
	}
	int mob::mobpresence() {
		return attr.presence;
	}
	int mob::mobtoughness() {
		return attr.toughness;
	}

	/*get the max health of the mob
	input is the base health of mob, health and toughness of elements in equipment list eq
	output is  the max health calculated*/
	int mob::getmaxhealth() {
		int maxhealth = base_hp;
		for (int i = 0; i < eqlist.size(); i++) {
			maxhealth += eqlist[i].equipbase_hp() + (modifier_convert[eqlist[i].equiptoughness()]) * 10;
		}
		return maxhealth;
	}

	/*get the max ac of the mob
	input is the base ac of mob, health and agility of elements in equipment list eq
	output is  the max ac calculated*/
	int mob::getmaxac() {
		int maxac = base_ac;
		for (int i = 0; i < eqlist.size(); i++) {
			maxac += eqlist[i].equipbase_ac() + (modifier_convert[eqlist[i].equipagility()]) * 10;
		}
		return maxac;
	}

	/*get the max agility of the mob
	input is the base agility of mob and elements in equipment list eq
	output is  the max agility calculated*/
	int mob::getmaxagility() {
		int maxagility = attr.agility;
		for (int i = 0; i < eqlist.size(); i++) {
			maxagility += eqlist[i].equipagility();
		}
		return maxagility;
	}

	/*get the max strength of the mob
	input is the base strength of mob and elements in equipment list eq
	output is  the max strength calculated*/
	int mob::getmaxstrength() {
		int maxstrength = attr.strength;
		for (int i = 0; i < eqlist.size(); i++) {
			maxstrength += eqlist[i].equipstrength();
		}
		return maxstrength;
	}

	/*get the max presence of the mob
	input is the base strength of mob and elements in equipment list eq
	output is  the max strength calculated*/
	int mob::getmaxpresence() {
		int maxpresence = attr.presence;
		for (int i = 0; i < eqlist.size(); i++) {
			maxpresence += eqlist[i].equippresence();
		}
		return maxpresence;
	}

	/*get the max toughness of the mob
	input is the base toughness of mob and elements in equipment list eq
	output is  the max toughness calculated*/
	int mob::getmaxtoughness() {
		int maxtoughness = attr.toughness;
		for (int i = 0; i < eqlist.size(); i++) {
			maxtoughness += eqlist[i].equiptoughness();
		}
		return maxtoughness;
	}

	/*setting the base value of an equipment and its name
	the name, base health, base armor, base agility, base presence, base strength, base toughness of the equipment is input
	the protected content of the equipment is output */
	equipment::equipment(string nm, int hp, int ac, int ag, int pr, int st, int tn) {
		eqname = nm;
		eqbase_hp = hp;
		eqbase_ac = ac;
		eqattr.agility = ag;
		eqattr.presence = pr;
		eqattr.strength = st;
		eqattr.toughness = tn;
	}

	/*print out the stats of the equipment
	input is the equipment's basic value and name
	output is the equipment's basic value and name in the format of:
	===equipment's name===
	HP: equipment's base health AC: equipment's base armor
	Agility: equipment's agility (modifier for agility)
	Strength: equipment's strength (modifier for strength)
	Presence: equipment's presence (modifier for presence)
	Toughness: equipment's toughness (modifier for toughness)*/
	void equipment::cout_eqstats() {
		cout << "===" << eqname << "===" << endl;
		cout << "Added HP: " << eqbase_hp << "Added AC: " << eqbase_ac << endl;
		cout << "Added Agility: " << eqattr.agility << " (" << eqattr.getAgilityMod() << ")" << endl;
		cout << "Added Strength: " << eqattr.strength << " (" << eqattr.getStrengthMod() << ")" << endl;
		cout << "Added Presence: " << eqattr.presence << " (" << eqattr.getPresenceMod() << ")" << endl;
		cout << "Added Toughness: " << eqattr.toughness << " (" << eqattr.getToughnessMod() << ")" << endl;
	}

	/*get the equipment's protected member without declaring derived classes or child classes
	intput is the corresponding protected member from equipment
	output is the member but not protected*/
	string equipment::equipname() {
		return eqname;
	}
	int equipment::equipbase_hp() {
		return eqbase_hp;
	}
	int equipment::equipbase_ac() {
		return eqbase_ac;
	}
	int equipment::equipagility() {
		return eqattr.agility;
	}
	int equipment::equipstrength() {
		return eqattr.strength;
	}
	int equipment::equippresence() {
		return eqattr.presence;
	}
	int equipment::equiptoughness() {
		return eqattr.toughness;
	}


	//add the equipment stats with mobs stats
	void equipment::use(mob* target) {
		/*
		old use function, u can just use target->mobbase_hp() to get target.base_hp value
		cout << target->mobbase_hp() + eqbase_hp;
		cout << target->mobbase_ac() + eqbase_ac;
		cout << target->mobagility() + eqattr.agility;
		cout << target->mobpresence() + eqattr.presence;
		cout << target->mobstrength() + eqattr.strength;
		cout << target->mobtoughness() + eqattr.toughness;
		*/
	}

}

/*
for testing only


int main(void){
	mob goblin1("Goblin 1",10,8,16,3,10,9);
	goblin1.cout_stats();
	cout << goblin1.mobagility();


	mob goblin2("Goblin 2" ,20,16,16,6,20,9);
	goblin2.cout_stats();

	equipment leather1("Leather armor", 100, 10, 2, 2, 2, 2);
	leather1.cout_eqstats();

	equipment leather2("Leather armor", 200, 10, 2, 3, 2, 2);

	equipment leather3("Leather armor", 300, 10, 2, 3, 2, 2);

	goblin1.eqlist.push_back(leather1);
	goblin1.eqlist.push_back(leather2);
	cout << goblin1.getmaxhealth();
	cout << goblin1.result_ac;



	return 0;
}
*/
