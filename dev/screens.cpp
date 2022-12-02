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
		add_ie(new uitext(L"[C]ontinue Character","continue_text",16,22));
		add_ie(new uitext(L"[N]ew Character","new_text",16,24));
		add_ie(new uitext(L"[Q]uit","quit_text",16,26));
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
		add_ie(new uitext(L"[Q]uit","quit_text",8, 33));
		add_ie(new uisprite("char_port", SPRITEDB["character_port_1"],6,7));
		add_ie(new uisprite("char_name_title", SPRITEDB["cc_name"],30,7));
		add_ie(new uitext(L"[N]: ","name_lable",29,13));
		new dynamicstring("cc_name_edit",string(""));
		add_ie(new dynamictext("cc_name_edit","cc_name_edit",33,13));
		add_ie(new uisprite("char_class_title", SPRITEDB["cc_class"],32,14));
		add_ie(new uitext(L"[C]:","class_lable",29,19));
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
			case('c'):{
				list<string> options({"KNIGHT","RANGER","WIZARD"});
				dynamic_string_selector* dss = new dynamic_string_selector("cc_edit_class_prompt","cc_class_edit",options,32,18,20,3);
				SCREENSTACK.push_back(dss->gethandle());
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
		new dynamicstring("temp_stringmod_string"+handle,existing_string);
		localdshandle = "temp_stringmod_string"+handle;
		add_ie(new uibox(size_x,size_y,"temp_stringmod_boxbg"+handle,0,0));
		add_ie(new dynamictext("temp_stringmod_string"+handle,"stringmod_lable",1,1));
			
		
	}
	dynamic_string_mod::~dynamic_string_mod(){
		SCREENSTACK.remove(handle);
		//delete(VALDB[localdshandle]);
		//dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
		//delete(localds);
	}
	int dynamic_string_mod::execute(int key){
		//tried to use range expression swtich case, but extension, not sure if it will compile everywhere so, :3 if else it is
		if(key>='A'&&key<='Z'||key>='a'&&key<='z'||key==' '||key=='_'){
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
		//enter
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
	dynamic_string_selector::~dynamic_string_selector(){
		SCREENSTACK.remove(handle);
		//delete(VALDB[localdshandle]);
		//dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
		//delete(localds);
	}
	void dynamic_string_selector::optionsup(){
		for(string option_ie_handle: option_ie_handles){
			iemap[option_ie_handle]->move(0,-1);
		}
	}
	void dynamic_string_selector::optionsdown(){
		for(string option_ie_handle: option_ie_handles){
			iemap[option_ie_handle]->move(0,1);
		}
	}
	void dynamic_string_selector::updatecursorloc(){
		interface_element* current_option = iemap[option_ie_handles.at(option_code)];
		interface_element* cursor = iemap[cursor_ie_handle];
		cursor->setloc(current_option->getx()-1,current_option->gety());
		int cursor_masked = cursor->ismasked(x,y);
		while(cursor_masked){
			if(cursor_masked==MASKED_UP){
				optionsdown();
			}
			else{
				optionsup();	
			}
			cursor->setloc(current_option->getx()-1,current_option->gety());
			cursor_masked = cursor->ismasked(x,y);
		}
	}
	dynamic_string_selector::dynamic_string_selector(string handle, string dynamicstringhandle, list<string> options, int xl, int yl, int size_x, int size_y):screen(handle){
		//center = true;
		setloc(xl,yl);
		maxoption = options.size();
		modifdshandle = dynamicstringhandle;
		string existing_string = ((dynamicstring*)(VALDB[dynamicstringhandle]))->getstring();
		sx = size_x+2;
		sy = size_y;
		add_ie(new uibox(sx,sy,string("temp_stringselector_boxbg")+handle,0,0));
		int original_y = 1;
		//int overmax_ie = 0;
		if(options.size() == 0){
			add_ie(new uitext(L"EMPTY", "empty_label"+handle,1,1));
			return;
		}

		for(string option: options){
			string option_ie_handle = string("temp_string_selector") + to_string(original_y)+handle;
			add_ie(new uitext(towstring(option),option_ie_handle,3,original_y));
			option_ie_handles.push_back(option_ie_handle);
			/*if(original_y<sy-1){
				iestack.push_back(option_ie_handle);
			}else{
				overmax_ie++;
			}*/
			original_y ++;
			iemap[option_ie_handle]->setmask(x+2,y+1,x+sx-1,y+sy);
			iemap[option_ie_handle]->setcustommask(true);	
			if(option == existing_string){
				option_code = original_y-2;
				iemap[option_ie_handle]->addattr(A_BOLD);
			}
		}
		//if there is any thing over the maximum, show arrow
		cursor_ie_handle = "SPEcursor"+handle;
		up_ie_handle = "SPEup_tri"+handle;
		down_ie_handle = "SPEdown_tri"+handle;
		add_ie(new uitext(L"▴",up_ie_handle,1,1));
		add_ie(new uitext(L"▾",down_ie_handle,1,sy-1));
		add_ie(new uitext(L"▶",cursor_ie_handle,0,0));
		iemap[cursor_ie_handle]->setmask(x+2,y+1,x+sx-1,y+sy);
		iemap[cursor_ie_handle]->setcustommask(true);	
		updatecursorloc();

		/*if(overmax_ie){
			iestack.push_back(down_ie_handle);
		}*/

		
	}

	/*void dynamic_string_selector::print(){

	}*/

	int dynamic_string_selector::execute(int key){
		switch(key){
			case(KEY_UP):{
				if(option_code-1<0)return 0;
				option_code--;
				updatecursorloc();
				return 1;
			}
			case(KEY_DOWN):{
				if(option_code+1>=maxoption)return 0;
				option_code++;
				updatecursorloc();
				return 1;
			}
			//enter
			case(10):{
				//save current edit str to target str
				//dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
				dynamicstring* modifds = (dynamicstring*)VALDB[modifdshandle];
				modifds->set(tostring(((uitext*)iemap[option_ie_handles[option_code]])->getstring()));
				delete(this);
				return 1;
			}	

			//escape
			case(27):{
				delete(this);
				return 1;
			}
			default:{
				return 0;
			}
		}
		return 1;
	}


}

