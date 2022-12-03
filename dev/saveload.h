#ifndef _SAVELOAD_H_
#define _SAVELOAD_H_
#include "io.h"
#include <map>
#include <string>
namespace dg{
	//class sprite;
	//std::map<std::string,sprite> SPRITEDB;
	void process_mem_usage(double& vm_usage, double& resident_set);
    	int loadInit();
	//int spriteloopthrough();
	int loadWrap();
}
#endif
