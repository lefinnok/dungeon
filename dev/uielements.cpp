#include "io.h"
#include "uielements.h"
#include "databases.h"
//#include <ncurses.h>
using namespace dg; 
        
namespace dg{ 
    uitext::uitext(string itext, string handle, int xl, int yl):interface_element(handle,xl,yl){
		text = 	itext;
    }
	void uitext::print(int xrel, int yrel){
		printat(text.c_str(),xrel+x,yrel+y);	
	}	
} 
