#include <iostream>
#include "mob.h"
#include <map>
#include <string>

using namespace std;

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
	mob::mob(){
	//for example, write the construction for class mob here
	}
}
//get modifier
