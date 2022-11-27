#include <iostream>
#include "mob.h"
#include <map>
#include <string>

using namespace std;

namespace dg{
	// modifier for converting abilities to the chance of success rate.
	// If the ability is 1-4, then the success rate of that ability decrease by 3
	// If the ability is 5-6, then the success rate of that ability decrease by 3
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
		{13,-3},
		{14,-3},
		{15,-3},
		{16,-3},
		{17,-3},
		{18,-3},
		{19,-3},
		{20,-3},
		{20,3}
	};
	mob::mob(){
	//for example, write the construction for class mob here
	}
}
//get modifier
