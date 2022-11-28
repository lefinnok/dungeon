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
	
}
//converting agility to its modifier, it uses moidier_convert to convert, return the modifier at the end
//agility is the input
//agility_mod is the output
int attributes::getAgilityMod() {
	return modifier_convert[agility];

}

//converting presence to its modifier, it uses moidier_convert to convert, return the modifier at the end
//presence is the input
//presence_mod is the output
int attributes::getPresenceMod(int presence, int presence_mod) {
	presence_mod= dg::modifier_convert[presence];
	return presence_mod;

}


//converting strength to its modifier, it uses moidier_convert to convert, return the modifier at the end
//strength is the input
//strengthe_mod is the output
int attributes::getStrengthMod(int strength, int strength_mod) {
	strength_mod= dg::modifier_convert[strength];
	return strength_mod;

}

//converting toughness to its modifier, it uses moidier_convert to convert, return the modifier at the end
//toughness is the input
//toughness_mod is the output
int attributes::getToughnessMod(int toughness, int toughness_mod) {
	toughness_mod= dg::modifier_convert[toughness];
	return toughness_mod;

}
