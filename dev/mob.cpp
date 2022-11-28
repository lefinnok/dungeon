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
}

//get the modifier from agility
//agility is the input and the modifier is the output
int getAgilityMod(int& agility) {
	agility = dg::modifier_convert[agility];
	return agility;

}

//get the modifier from presence
//presence is the input and the modifier is the output
int getPresenceMod(int& presence) {
	presence = dg::modifier_convert[presence];
	return presence;

}
// get the modifier from strength
//strength is the input and the output is modifier
int getStrengthMod(int& strength) {
	strength = dg::modifier_convert[strength];
	return strength;

}

// get the modifier from toughness
// toughness is the input and the output is the modifier
int getToughnessMod(int& toughness) {
	toughness = dg::modifier_convert[toughness];
	return toughness;

}

int mob() {

	// mobs detail like name, description
	class mob {
		string mob_name;
		string mob_description;
	};
	return 0;
};

//add attributes to the mobs and convert the to modifiers
int main() {
	dg::attributes mobs;
	int agility;
	mobs.agility = agility;
	int presence;
	mobs.presence = presence;
	int strength;
	mobs.strength = strength;
	int toughness;
	mobs.toughness = toughness;

	int agmod = getAgilityMod(agility);
	mobs.agmod = agmod;
	int prmod = getPresenceMod(presence);
	mobs.prmod = prmod;
	int strmod = getStrengthMod(strength);
	mobs.strmod = strmod;
	int toumod = getToughnessMod(toughness);
	mobs.toumod = toumod;
	cout << mobs.agility << mobs.presence << mobs.toughness << mobs.strength << mobs.agmod << mobs.prmod << mobs.strmod << mobs.toumod;
	
	
	return 0;
}
