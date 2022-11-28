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
	
	mob::mob(string nm, int hp, int ac, int ag, int pr, int st, int tn){
		name = nm;
		base_hp = hp;
		base_ac = ac;
		attr.agility = ag;
		attr.presence = pr;
		attr.strength = st;
		attr.toughness = tn;
	}
	void mob::cout_stats(){
		cout<<"==="<<name<<"==="<<endl;
		cout<<"HP: "<<base_hp<<" AC: "<<base_ac<<endl;
		cout<<"Agility: "<<attr.agility<<" ("<<attr.getAgilityMod()<<")"<<endl;
		cout<<"Strength: "<<attr.strength<<" ("<<attr.getStrengthMod()<<")"<<endl;
		cout<<"Presence: "<<attr.presence<<" ("<<attr.getPresenceMod()<<")"<<endl;
		cout<<"Toughness: "<<attr.toughness<<" ("<<attr.getToughnessMod()<<")"<<endl;
	}
}
int main(void){
	mob goblin("Goblin 1",10,8,16,3,10,9);
	goblin.cout_stats();		
	return 0;
}

