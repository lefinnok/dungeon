#include "io.h"
#include "screens.h"
#include "databases.h"
#include "uielements.h"
#include <ncurses.h>
#include <iostream>
using namespace dg;

namespace dg{
	titlescreen::titlescreen(string handle):screen(handle){
		setloc(0,0);
		setcontrollable(true);
		add_ie(new uisprite("celt_deco_1",SPRITEDB["celt_knot_1"],0,12));
		add_ie(new uisprite("title_bar", SPRITEDB["dungeon_core_title"],6,13));
		add_ie(new uitext("[C]ontinue Character","continue_text",16,22));
		add_ie(new uitext("[N]ew Character","new_text",16,24));
		add_ie(new uitext("[Q]uit","quit_text",16,26));
		//iemap["continue_text"]->addattr(A_BOLD);
	}
	int titlescreen::execute(int key){
		switch(key){
			case('q'):{
                EXIT = 1;
                return 1;
			}
			case('c'):{
				return 1;
			}
			case('n'):{
				character_creation* cc = new character_creation("character_create");
				SCREENSTACK.push_back(cc->gethandle());
				return 1;
			}

			default:{
				return 0;		
			}
		}
	}

	character_creation::character_creation(string handle):screen(handle){
		setloc(0,0);
		setcontrollable(true);
		//add_ie(new uibackground(20,20,"cc_background",0,0));
		opaque=true;
		add_ie(new uisprite("scroll", SPRITEDB["scroll_bigbg"],0,3));
		add_ie(new uisprite("cc_title",SPRITEDB["character_creation_title"],8,0));
		add_ie(new uitext("[Q]uit","quit_text",8, 33));
		add_ie(new uisprite("char_port", SPRITEDB["character_port_1"],6,7));
		add_ie(new uisprite("char_name_title", SPRITEDB["cc_name"],30,7));
		add_ie(new uitext("[N]: ","name_lable",29,13));
		new dynamicstring("cc_name_edit",string(""));
		add_ie(new dynamictext("cc_name_edit","cc_name_edit",33,13));
		add_ie(new uisprite("char_class_title", SPRITEDB["cc_class"],32,14));
		add_ie(new uitext("[C]:","class_lable",29,19));
		new dynamicstring("cc_class_edit",string("KNIGHT"));
		add_ie(new dynamictext("cc_class_edit","cc_class_edit",33,19));
		iemap["cc_class_edit"]->addattr(A_BOLD);
		//add_ie(new uitext("[C]lass: ","class_lable",6,7));
	}

	int character_creation::execute(int key){
		switch(key){
			case('q'):{
				SCREENSTACK.remove(handle);
				delete(this);
				return 1;
			}
			case('n'):{
				dynamic_string_mod* dsm = new dynamic_string_mod("cc_edit_name_prompt","cc_name_edit",32,12,20,2);
				SCREENSTACK.push_back(dsm->gethandle());
				return 1;
			}
			default:{
				return 0;
			}
		}
	}

	dynamic_string_mod::dynamic_string_mod(string handle, string dynamicstringhandle, int xl, int yl, int size_x, int size_y):screen(handle){
		//center = true;
		setloc(xl,yl);
		modifdshandle = dynamicstringhandle;
		string existing_string = ((dynamicstring*)(VALDB[dynamicstringhandle]))->getstring();
		new dynamicstring("temp_stringmod_string",existing_string);
		localdshandle = "temp_stringmod_string";
		add_ie(new uibox(size_x,size_y,"temp_stringmod_boxbg",0,0));
		add_ie(new dynamictext("temp_stringmod_string","stringmod_lable",1,1));
			
		
	}
	dynamic_string_mod::~dynamic_string_mod(){
		SCREENSTACK.remove(handle);
		//delete(VALDB[localdshandle]);
		//dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
		//delete(localds);
	}
	int dynamic_string_mod::execute(int key){
		//tried to use range expression swtich case, but extension, not sure if it will compile everywhere so, :3 if else it is
		if(key>='A'&&key<='Z'||key>='a'&&key<='z'||key==' '||key=='_'||key==263){
			dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
			string editstr = localds->getstring();
			editstr.push_back(key);
			localds->set(editstr);
			return 1;
		}
		//backspace || TEMP, NOT UNIVERSAL (i don't think)
		if(key == KEY_BACKSPACE || key == KEY_DC || key == 127){
			//std::cout<<"backspace"<<std::endl;
			dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
			string editstr = localds->getstring();
			if(editstr.size()==0)return 0;
			editstr.pop_back();
			localds->set(editstr);
			return 1;
		}
		if(key==10){
			//save current edit str to target str
			dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
			dynamicstring* modifds = (dynamicstring*)VALDB[modifdshandle];
			modifds->set(localds->getstring());
			delete(this);
			return 1;
		}
		//esc
		if(key==27){
			//exit without saving
			delete(this);
			return 1;
		}
		return 0;
	}


}

