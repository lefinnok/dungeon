#include "io.h"
#include "screens.h"
#include "databases.h"
#include "uielements.h"
using namespace dg;

namespace dg{
	titlescreen::titlescreen(string handle):screen(handle){
		setloc(0,0);
		setcontrollable(true);
		add_ie(new uisprite("celt_deco_1",SPRITEDB["celt_knot_1"],0,10));
		add_ie(new uisprite("title_bar", SPRITEDB["dungeon_core_title"],6,10));
		add_ie(new uitext("[C]ontinue Character","continue_text",16,22));
		add_ie(new uitext("[N]ew Character","new_text",16,24));
		add_ie(new uitext("[Q]uit","quit_text",16,26));
	}
	int titlescreen::execute(int key){
		switch(key){
			case('q'):{
                EXIT = 1;
                return 1;
			}
			default:{
				return 0;		
			}
		}
	}
}

