#include "io.h"
#include "screens.h"
#include "databases.h"
#include "uielements.h"
#include <ncurses.h>
#include <iostream>
#include "mob.h"
#include <algorithm>
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
		//size_x = 40;
		//center_x = true;
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
	
    play_screen::~play_screen(){
        //delete(iemap["ps_show_status_text"]);
        delete(VALDB[status_string_handle]);
    }
	play_screen::play_screen(string handle):screen(handle){
		add_ie(new uibox(61, 11, "bottom_play_box",0,30));
		add_ie(new uisprite("ps_use",SPRITEDB["ps_use"],1,31));
		add_ie(new uiboxVseperator(11,"ps_use_seperator",16,30));
		add_ie(new uisprite("ps_inventory",SPRITEDB["ps_inventory"],18,31));
		add_ie(new uiboxVseperator(11,"ps_inventory_seperator",31,30));
        add_ie(new uisprite("ps_dungeon",SPRITEDB["dungeon"],0,0));
        add_ie(new playlog(61,6,"ps_play_log",0,42));
		//test player
		mob* testplayer = new mob("test_player",10,10,23,20);
		mob* testplayer1 = new mob("test_player", 20, 20, 20,20);
        enemies.push_back(testplayer1);
        
        add_ie(new statblock(*enemies.begin(),"ps_enemy_statblock_1",0,8));
	    
		player_handle = testplayer->gethandle();

        MOBDB[player_handle]->additem("Health Potion");

        MOBDB[player_handle]->additem("Health Potion");

        testplayer->additem("rusted_chestplate");
        testplayer->equip("rusted_chestplate");
        testplayer1->additem("rusted_chestplate");
        testplayer1->equip("rusted_chestplate");
        testplayer->additem("mundane_longsword");
        testplayer->equip("mundane_longsword");
        testplayer->additem("poison_dagger");
        testplayer->additem("rusted_chestplate");
        //testplayer->additem("rusted_chestplate");
        //testplayer->equip("rusted_chestplate_0");
		//hp
        int curhp = MOBDB[player_handle]->getcurrenthitpoint();
		int maxhp = MOBDB[player_handle]->getmaxhitpoint();
        add_ie(new uitext(L"HEALTH","ps_player_health_label",32,31));
		add_ie(new uitext(to_wstring(curhp),"ps_player_cur_health",39,31));
		add_ie(new uitext(wstring(L"/")+to_wstring(maxhp),"ps_player_max_health",iemap["ps_player_cur_health"]->getsizex()+39,31));
		add_ie(new uiprogressbar(28,curhp,maxhp,"ps_player_hp_bar",32,32));

        //statuses
        int statusy = 33;
        add_ie(new uiboxHseperator(30,"ps_status_seperator_1",31,statusy));
        add_ie(new uiboxHseperator(30,"ps_status_seperator_2",31,statusy+2));
        add_ie(new uitext(L"STATUS","ps_status_label",32,statusy));
        status_string_handle = "ps_show_status_string";
        new dynamicstring(status_string_handle,"");
        add_ie(new dynamictext(status_string_handle,"ps_show_status_text",32,statusy+1));
        
        //Player Stats
        add_ie(new uitext(L"","ps_stats_string",32,statusy+3));
        add_ie(new uitext(L"AGL","ps_agl_label",32,statusy+4));
        add_ie(new uiprogressbar2(20,0,20,"ps_player_agl_bar",39,statusy+4));
        add_ie(new uitext(L"PRS","ps_prs_label",32,statusy+5)); 
        add_ie(new uiprogressbar2(20,0,20,"ps_player_prs_bar",39,statusy+5));
        add_ie(new uitext(L"STR","ps_str_label",32,statusy+6)); 
        add_ie(new uiprogressbar2(20,0,20,"ps_player_str_bar",39,statusy+6));
        add_ie(new uitext(L"TGH","ps_tgh_label",32,statusy+7)); 
        add_ie(new uiprogressbar2(20,0,20,"ps_player_tgh_bar",39,statusy+7));
	}


	void play_screen::updateuielements(){
        mob* player = MOBDB[player_handle];
        if(!player)return;
		int curhp = MOBDB[player_handle]->getcurrenthitpoint();
		int maxhp = MOBDB[player_handle]->getmaxhitpoint();
        int agl = player->getmodagility();
        int prc = player->getmodpresence();
        int str = player->getmodstrength();
        int tgh = player->getmodtoughness();
		((uitext*)iemap["ps_player_cur_health"])->setstring(to_wstring(curhp));
		((uitext*)iemap["ps_player_max_health"])->setstring(wstring(L"/")+to_wstring(maxhp));
		iemap["ps_player_max_health"]->setloc(iemap["ps_player_cur_health"]->getsizex()+39,31);
        ((uiprogressbar*)iemap["ps_player_hp_bar"])->updatemax(maxhp);
        ((uiprogressbar*)iemap["ps_player_hp_bar"])->updateval(curhp);
        ((uiprogressbar*)iemap["ps_player_agl_bar"])->updateval(agl);
        ((uiprogressbar*)iemap["ps_player_prs_bar"])->updateval(prc);
        ((uiprogressbar*)iemap["ps_player_str_bar"])->updateval(str);
        ((uiprogressbar*)iemap["ps_player_tgh_bar"])->updateval(tgh);
        string status_text = "";
        
        for(status_effect* s: *(player->getstatuslist())){
           status_text += s->getname() + string("|") + to_string(s->getvalue()) + string("|") + to_string(s->getduration()) + string(" "); 
        }
        VALDB[status_string_handle]->set(status_text);
        wstring statstring = wstring(L"|AGL|")+to_wstring(player->getmodagility())+wstring(L"|PRS|")+to_wstring(player->getmodpresence())+wstring(L"|STR|")+to_wstring(player->getmodstrength())+wstring(L"|TGH|")+to_wstring(player->getmodtoughness());
        ((uitext*)iemap["ps_stats_string"])->setstring(statstring);
		//add_ie(new uitext(to_wstring(MOBDB[player_handle]->getcurrenthitpoint()),"ps_player_cur_health"),32,31);
		//add_ue(new uitext(wstring(L"/")+to_wstring(MOBDB[player_handle]->getmaxhitpoint()),"ps_player_max_health",iemap["ps_player_cur_health"]->getsizex()+32+1,31));

	}
    void play_screen::advanceround(){
        //apply status effects
        mob* player = MOBDB[player_handle];
        if(!player)return;
        list<status_effect*>* active_statuses = player->getstatuslist();
        list<status_effect*> ticks;
        for(status_effect* s: *active_statuses){
            ticks.push_back(s);
        }
        for(status_effect* s: ticks){
            s->tick();
        }
        //enemy round 
        for(mob* enemy: enemies){
            enemy->airound();
        }
    }
	int play_screen::execute(int key){
		//updateuielements();
		switch(key){
            case('u'):{
                /*vector<item*> usable_items;
                for(item* i: *MOBDB[player_handle]->getinventory()){
                    if(i->usable())usable_items.push_back(i);
                }*/
                use_menu* um = new use_menu("ps_use_menu",player_handle);
                SCREENSTACK.push_back(um->gethandle());
                advanceround();
                return 1;
            }
            case('i'):{
                inventory_menu* im = new inventory_menu("ps_iv_menu",player_handle);
                SCREENSTACK.push_back(im->gethandle());
            }
            case('r'):{
                advanceround();
                //advance round
                return 1;
            }
			case('h'):{
				MOBDB[player_handle]->modifyhitpoint(-1);
                (*enemies.begin())->modifyhitpoint(-1);
				return 1;
			}
			//escape
			case(27):{
				screen* ps = new pause_menu("pause_menu");
				SCREENSTACK.push_back(ps->gethandle());
				return 1;
			}
			default:{
				return 0;
			}
		}
		return 0;
	}
	void play_screen::print(){
		updateuielements();
		screen::print();
	}
    use_menu::~use_menu(){
        delete(VALDB["use_menu_placeholder"]);
        delete(ACTIVESCREENS[selector_handle]);
    }
    use_menu::use_menu(string handle, string player_h):screen(handle){
        setloc(0,30);
        player_handle = player_h;
        selector_handle = "use_menu_selector";
        add_ie(new uitext(L"USE","use_menu_title",1,0));
        new dynamicstring("use_menu_placeholder","");
        list<string> usable_items;
        //map<int,string> optioncodetoinventoryhandle;
        int idx = 0;
        for(pair<string,item*> p: MOBDB[player_handle]->getusable()){
            item* i = p.second;
            usable_items.push_back(i->getname());
            optioncodetoinventoryhandle.insert({idx,p.first});
            idx++;
        }
        //usable_items.push_back("G");
        dynamic_string_selector* selector = new dynamic_string_selector(selector_handle,"use_menu_placeholder",usable_items,x,y,16,11);
        SCREENSTACK.insert(----SCREENSTACK.end(),selector_handle);

        
    }
    

    int use_menu::execute(int key){
        
        dynamic_string_selector* selector = (dynamic_string_selector*)ACTIVESCREENS[selector_handle];
        switch(key){
			case(KEY_UP):{
				if(selector->option_code-1<0)return 0;
				selector->option_code--;
				selector->updatecursorloc();
				return 1;
			}
			case(KEY_DOWN):{
				if(selector->option_code+1>=selector->maxoption)return 0;
				selector->option_code++;
				selector->updatecursorloc();
				return 1;
			}
            //Enter
            case(10):{
                if(!(selector->empty)){
                    string itemuse_handle = optioncodetoinventoryhandle[selector->option_code];
                    mob* player = MOBDB[player_handle];
                    map<string,item*>* inventory = player->getinventory();
                    item* target_item = inventory->find(itemuse_handle)->second;
                    target_item->use();
                    //(*(MOBDB[player_handle]->getinventory()))[itemuse_handle]->use();
                }
                delete(this);
                return 1;
            }
            case(27):{
                delete(this);
                return 1;
            }
            default:{
                return 0;
            }
        }
    }
    
    inventory_menu::~inventory_menu(){
        delete(VALDB[equip_ds_handle]);
        delete(VALDB[unequip_ds_handle]);
        delete(ACTIVESCREENS[inventory_selector_handle]);
        delete(ACTIVESCREENS[equipment_selector_handle]);
    }

    inventory_menu::inventory_menu(string handle, string player_h):screen(handle){
        setloc(0,0);
        player_handle = player_h;
        player_inventory = MOBDB[player_handle]->getinventory();
        inventory_selector_handle = "inventory_menu_inventory_selector";
        equipment_selector_handle = "inventory_menu_equipment_selector";
        equip_ds_handle = "inventory_menu_equip_ds";
        unequip_ds_handle = "inventory_menu_unequip_ds";
        add_ie(new uitext(L"INVENTORY","inventory_menu_title",1,0));
        add_ie(new uitext(L"EQUIPMENT","equipment_menu_title",39,0));
        add_ie(new uitext(L"[ENTER] to equip","inventory_menu_instruction",3,29));
        add_ie(new uitext(L"and unequip", "inventory_menu_instruction_2",39,29));
        new dynamicstring(equip_ds_handle,"");
        new dynamicstring(unequip_ds_handle,"");
        list<string> inventory_items;
        //map<int,string> optioncodetoinventoryhandle;
        //int idx = 0;
        for(pair<string,item*> p: *player_inventory){
            //item* i = p.second;
            inventory_items.push_back(p.first);
        }

        list<string> equipment_items;
        for(string eq: *MOBDB[player_handle]->getequipments()){
            equipment_items.push_back(eq);
        }
        //usable_items.push_back("G");
        dynamic_string_selector* selector = new dynamic_string_selector(inventory_selector_handle,equip_ds_handle,inventory_items,x,y,36,29);
        SCREENSTACK.insert(----SCREENSTACK.end(),inventory_selector_handle);

        dynamic_string_selector* selectorii = new dynamic_string_selector(equipment_selector_handle,unequip_ds_handle,equipment_items,x+38,y,21,29);
        SCREENSTACK.insert(--SCREENSTACK.end(),equipment_selector_handle);

    }
    void inventory_menu::updateuielements(){
        
        list<string> inventory_items;
        //map<int,string> optioncodetoinventoryhandle;
        //int idx = 0;
        for(pair<string,item*> p: *player_inventory){
            //item* i = p.second;
            inventory_items.push_back(p.first);
        }

        list<string> equipment_items;
        for(string eq: *MOBDB[player_handle]->getequipments()){
            equipment_items.push_back(eq);
        }
        ((dynamic_string_selector*)ACTIVESCREENS[equipment_selector_handle])->setoptions(equipment_items);
        ((dynamic_string_selector*)ACTIVESCREENS[inventory_selector_handle])->setoptions(inventory_items);
    }
    void inventory_menu::print(){
        //screen::print();
        //updateuielements();
        screen::print();
    }
    int inventory_menu::execute(int key){
        map<int, string> convert = {{0,inventory_selector_handle},{1,equipment_selector_handle}};
        dynamic_string_selector* selector = (dynamic_string_selector*)ACTIVESCREENS[convert[selector_code]];
        switch(key){
			case(KEY_UP):{
				if(selector->option_code-1<0)return 0;
				selector->option_code--;
				selector->updatecursorloc();
				return 1;
			}
			case(KEY_DOWN):{
				if(selector->option_code+1>=selector->maxoption)return 0;
				selector->option_code++;
				selector->updatecursorloc();
				return 1;
			}
            case(KEY_LEFT):{
                selector_code = 0;
                return 1;
            }
            case(KEY_RIGHT):{
                selector_code = 1;
                return 1;
            }
            //Enter
            
            case(10):{
                if(!(selector->empty)){    
                    mob* player = MOBDB[player_handle];
                    //dynamicstring* ds = (dynamicstring*)VALDB[selector->getmodifdshandle()];
                    string target_equipment_handle = selector->getcurrentoptionstring();
                    if(selector_code){
                        //in equip
                        player->unequip(target_equipment_handle);
                    }else{
                        //in inv
                        player->equip(target_equipment_handle);

                    }
                    //delete(this);
                    //if(){}
                }
                updateuielements();
                //delete(this);
                return 1;
            }
            case(27):{
                delete(this);
                return 1;
            }
            default:{
                return 0;
            }
        }
    }

	/*pause_menu::~pause_menu(){
		SCREENSTACK.remove(handle);
		//delete(VALDB[localdshandle]);
		//dynamicstring* localds = (dynamicstring*)VALDB[localdshandle];
		//delete(localds);
	}*/
	
	pause_menu::pause_menu(string handle):screen(handle){
		setloc(20,10);
		add_ie(new uibox(22, 6, "pause_menu_box",0,0));
		add_ie(new uitext(L"PAUSE","pause_menu_title",1,0));
		add_ie(new uitext(L"[S]ave Game", "pause_menu_save_label",1,1));
		add_ie(new uitext(L"[Q]uit to Main Menu", "pause_menu_quit_label",1,2));

	}


	int pause_menu::execute(int key){
		switch(key){
			case('s'):{
				return 1;
			}
			case('q'):{
				new titlescreen("title_screen");
				SCREENSTACK.push_back("title_screen");
				delete(ACTIVESCREENS["play_screen"]);
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
		return 0;
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
    void dynamic_string_selector::setoptions(list<string> options){
        maxoption = options.size();
        if(options.size()==0){
            
			add_ie(new uitext(wstring(L"EMPTY")/*+wstring(max(0,size_y-5) L' ')*/, "empty_label"+handle,1,1));
			empty = true;
            return;
        }
        //if(option_code>maxoption)option_code = maxoption;
        //if(option_code<0)option_code = 0;
        list<string> options_to_erase;
        for(string option_ie_handle: option_ie_handles){
            options_to_erase.push_back(option_ie_handle);
            //delete(iemap[option_ie_handle]);
            //iemap.erase(option_ie_handle);
        }
        for(string option_ie_handle: options_to_erase){
            delete(iemap[option_ie_handle]);
            iemap.erase(option_ie_handle);
            iestack.remove(option_ie_handle);
        }
        option_ie_handles.clear();
		//string existing_string = ((dynamicstring*)(VALDB[modifdshandle]))->getstring();
        int original_y = 1;
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
			/*if(option == existing_string){
				option_code = original_y-2;
				iemap[option_ie_handle]->addattr(A_BOLD);
			}*/
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
			add_ie(new uitext(wstring(L"EMPTY")/*=wstring(max(0,size_x-5),L' ')*/, "empty_label"+handle,1,1));
			empty = true;
            return;
		}
        option_code = 0;
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
    string dynamic_string_selector::getmodifdshandle(){return modifdshandle;}
    string dynamic_string_selector::getcurrentoptionstring(){
        interface_element* current_option = iemap[option_ie_handles.at(option_code)];
        return tostring(((uitext*)current_option)->getstring());
    }
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

