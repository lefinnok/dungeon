#include <iostream>
#include "mob.h"
//#include "items.h"
#include <map>
#include <string>
#include <vector>
#include "databases.h"
#include "uielements.h"
#include "screens.h"
#include <ncurses.h>
#include <algorithm>
#include <random>
using namespace std;
using namespace dg;
namespace dg{
	
	/*all comments will have the same format of: 
	use of this function
	input of this function
	output of this function*/
	

	/* modifier for converting abilities to the chance of success rate.
	input is the number u want to convert e.g modifier_covert[3]
	output is the value like for 3 it is -3*/
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
	

	/*converting agility to its modifier, it uses moidier_convert to convert, return the modifier at the end
	agility is the input
	value of agility after converted by the modifier_convert is the output*/
	int attributes::getAgilityMod() {
		return modifier_convert[agility];
	
	}
	
	/*converting presence to its modifier, it uses moidier_convert to convert, return the modifier at the end
	presence is the input
	value of presence after converted by the modifier_convert is the output*/
	int attributes::getStrengthMod() {
	    return modifier_convert[strength];
	                         
	}  
	
	/*converting strength to its modifier, it uses moidier_convert to convert, return the modifier at the end
	strength is the input
	value of strength after converted by the modifier_convert is the output*/
	int attributes::getToughnessMod() {
	    return modifier_convert[toughness];
	                         
	}  
	/*converting toughness to its modifier, it uses moidier_convert to convert, return the modifier at the end
	toughness is the input
	value of toughness after converted by the modifier_convert is the output output*/
	int attributes::getPresenceMod() {
	    return modifier_convert[presence];
    	                     
	}
	
	/*setting the base value of a mob and its name
	the name, base health, base armor, base agility, base presence, base strength, base toughness of the mob is input
	the protected member of the class mob is output*/
    /*mob::mob(string hd, int ag, int pr, int st, int tn){
        mob(hd,ag,pr,st,tn,false);
    }*/
	mob::mob(string hd, int ag, int pr, int st, int tn){
		if(MOBDB.count(hd)){
			int handle_mod_id = 0;
			while(MOBDB.count(hd+string("_")+to_string(handle_mod_id))){
				handle_mod_id += 1;
			}
			hd += string("_")+to_string(handle_mod_id);
		}
		handle=hd;
		MOBDB.insert({handle,this});
		attr.agility = ag;
		attr.presence = pr;
		attr.strength = st;
		attr.toughness = tn;
		hitpoint = getmaxhitpoint();
	}
	mob::~mob(){
		if(!istemplate)MOBDB.erase(handle);
        list<status_effect*> sse;
		for(status_effect* se: active_statuses){
			sse.push_back(se);
		}
        for(status_effect* se: sse){delete(se);}
        list<item*> itemstorem;
        for(pair<string,item*> i: inventory){
            itemstorem.push_back(i.second);
        }
        for(item* i: itemstorem){
            delete(i);
        }
	}
    void mob::settemplate(){istemplate=true;}
	int mob::getcurrenthitpoint(){
        if(hitpoint>getmaxhitpoint())hitpoint=getmaxhitpoint();
		return hitpoint;
	}
	int mob::getmaxhitpoint(){
		return (getmodtoughness())<<2;
		
	}
	list<status_effect*>* mob::getstatuslist(){return &active_statuses;}
	void mob::modifyhitpoint(int amount){
		if((hitpoint+amount)<=0){hitpoint=0;return;}
		int max = getmaxhitpoint();
		if((hitpoint+amount)>max){hitpoint=max;return;}
		hitpoint+=amount;
	} 
	
	int mob::mobagility() {
		return attr.agility;
	}
	int mob::mobstrength() {
		return attr.strength;
	}
	int mob::mobpresence() {
		return attr.presence;
	}
	int mob::mobtoughness() {
		return attr.toughness;
	}
	string mob::gethandle(){return handle;}
	void mob::dead(){
        if(!player){
            ENEMIES.clear();
            mob* newmob = randommobfromtemplate();
            ENEMIES.push_back(newmob);
            //delete(this);
        }
	}

    mob* mob::copy(){
        mob* newmob = new mob(handle,attr.agility,attr.strength,attr.presence,attr.toughness);
        //map<string,item*>* newmobinv = newmob->getinventory();
        for(pair<string,item*> p: inventory){
            newmob->additem(p.first);
        }
        //list<string>* newmobeqps = newmob->getequipments();
        for(string eqp: equipments){
            newmob->equip(eqp);
        }
        return newmob;
    }
    
	mob* randommobfromtemplate(){
        int mob_code = rand()%MOBTEMPLATES.size();
        map<string,mob*>::iterator mit = MOBTEMPLATES.begin();
        advance(mit,mob_code);
        return (mit->second)->copy();
    }

    void mob::additem(string itemname){
        item* itemtemplate = ITEMDB[itemname];
        if(itemtemplate){
            item* itemtoadd = itemtemplate->copy();
            itemtoadd->setowner(this);
            itemtoadd->setinventory(&inventory);

		    if(inventory.count(itemname)){
			    int handle_item_id = 0;
			    while(inventory.count(itemname+string("_")+to_string(handle_item_id))){
				    handle_item_id += 1;
			    }
			    itemname += string("_")+to_string(handle_item_id);
		    }
            inventory.insert({itemname,itemtoadd});
            itemtoadd->setinventoryhandle(itemname);
        }
    }

    map<string,item*>* mob::getinventory(){return &inventory;}
    list<string>* mob::getequipments(){return &equipments;}
    void mob::addstatus(status_effect* s){active_statuses.push_back(s);}
    bool mob::isplayer(){return player;}
    void mob::setplayer(){if(PLAYER)return;player = true;PLAYER=this;}
    int mob::getagilitymod(){
        int a = getmodagility();
        if(a>20)return 4;
        return modifier_convert[a];
    }
    int mob::getpresencemod(){
        int a = getmodpresence();
        if(a>20)return 4;
        return modifier_convert[a];
    }
    int mob::getstrengthmod(){
        int a = getmodstrength();
        if(a>20)return 4;
        return modifier_convert[a];
    }
    int mob::gettoughnessmod(){
        int a = getmodtoughness();
        if(a>20)return 4;
        return modifier_convert[a];
    }
    list<modifier*> mob::gettotalmodifiers(){
        list<modifier*> total_modifiers;
        for(modifier* mod: inherent_modifiers){
            total_modifiers.push_back(mod);
        }
        for(string equipment_handle: equipments){
            item* equipment = inventory[equipment_handle];
            for(modifier* mod: *equipment->getmodifiers()){
                total_modifiers.push_back(mod);
            }
        }
        return total_modifiers;
    }
    int mob::getmodagility(){
        int agil = attr.agility;
        list<modifier*> total_modifiers = gettotalmodifiers();
        for(modifier* mod: total_modifiers){
            if(mod->type=="agility")agil+=stoi(mod->val);
        }
        return agil;
    }

    int mob::getmodpresence(){
        int prec = attr.presence;
        list<modifier*> total_modifiers = gettotalmodifiers();
        for(modifier* mod: total_modifiers){
            if(mod->type=="presence")prec+=stoi(mod->val);
        }
        return prec;
    }
	
    int mob::getmodstrength(){
        int str = attr.strength;
        list<modifier*> total_modifiers = gettotalmodifiers();
        for(modifier* mod: total_modifiers){
            if(mod->type=="strength")str+=stoi(mod->val);
        }
        return str;
    }

    int mob::getmodtoughness(){
        int tgh = attr.toughness;
        list<modifier*> total_modifiers = gettotalmodifiers();
        for(modifier* mod: total_modifiers){
            if(mod->type=="toughness")tgh+=stoi(mod->val);
        }
        return tgh;
    }

    

    void mob::equip(string inventory_handle){
        bool found = (std::find(equipments.begin(), equipments.end(), inventory_handle) != equipments.end());
        item* i = inventory[inventory_handle];
        string appendage = "";
        for(modifier* mod: *i->getmodifiers()){
            if(mod->type=="appendage")appendage=mod->val;
        }
        if(appendage==""){
            outlog(L"equipment missing appendage identifier");
            return;
        }
        //if same appendage
        list<string> ehtounequip;
        for(string equipment_handle: equipments){
            if(inventory[equipment_handle]->getappendage()==appendage){
                ehtounequip.push_back(equipment_handle);
                //unequip(equipment_handle);
            }
        }
        for(string eh: ehtounequip){
            unequip(eh);
        }
        if(inventory.count(inventory_handle)&&!found){
            equipments.push_back(inventory_handle);
        }
    }
    void mob::unequip(string inventory_handle){
        bool found = (std::find(equipments.begin(), equipments.end(), inventory_handle) != equipments.end());
        if(found){
            equipments.remove(inventory_handle);
        }
    }
    void mob::airound(){
        list<status_effect*>* active_statuses = getstatuslist();
        list<status_effect*> ticks;
        for(status_effect* s: *active_statuses){
            ticks.push_back(s);
        }
        for(status_effect* s: ticks){
            s->tick();
        }
        map<string,item*> usables = getusable();
        if(usables.empty())return;
        int action_code = rand()%usables.size();
        map<string,item*>::iterator uit = usables.begin();
        advance(uit,action_code);
        uit->second->use();
    }

    map<string,item*> mob::getusable(){
        map<string, item*> usable_map;
        for(pair<string,item*> p: inventory){
            item* i = p.second;
            list<string>* tgs = i->gettags();
            bool isEquipment = (std::find(tgs->begin(), tgs->end(), "Equipment") != tgs->end());
            if(isEquipment)continue;
            if(i->usable()){
                usable_map.insert(p);
            }
            
        }
        for(string eq: equipments){
            item* i = inventory[eq];
            if(i->usable()){
                usable_map.insert({eq,i});
            }
        }
        return usable_map;
    }
	//===ITEMS===
    
    //STAT
    string status_effect::getname(){return name;}
    int status_effect::getduration(){return duration;}
    int status_effect::getvalue(){return value;}
	status_effect::status_effect(string nm, mob* hst,int dur, int val){
		name = nm;
        host = hst;
		duration = dur;
		value = val;

	}
	status_effect::~status_effect(){
		host->getstatuslist()->remove(this);
	}
	void status_effect::tick(){
		duration--;
		if(duration==0){delete(this);return;}
        if(duration<0){duration=-1;return;}
	}
    
	void heal::tick(){
		host->modifyhitpoint(value);
		status_effect::tick();
	}
	action::action(map<string, string> args){
		for(pair<string, string>p: args){
			arguments.insert(p);
		}
	}
	int action::trigger(mob* actor){return 1;}
    
    string gettargethandle(mob* actor){
        //return PLAYER->gethandle();
        if(actor->isplayer()){
            string ds_handle = "temp_status_apply_target_selection_string_";
            string selector_handle = "temp_status_apply_target_selector_";
    		new dynamicstring(ds_handle,"Cancel");
            int tempexit = 0;
            list<string> mobsinscene;
            for(pair<string,mob*> p: MOBDB){
                mobsinscene.push_back(p.first);
            }
            dynamic_string_selector* triggerselect= new dynamic_string_selector(selector_handle,ds_handle,mobsinscene,0,20,16,10);
            while(!tempexit){
                if(!ACTIVESCREENS.count(selector_handle))break;
                triggerselect->print();
                
    		    int exec_code = 0;
        		while(!exec_code){
        			screen* current_control_screen = triggerselect;
        			int input = 0;	
        			if(current_control_screen->getcontrollable()){
        				input = getch();
        			}
    
        			exec_code = current_control_screen->execute(input);
        		}
            }
            string res = VALDB[ds_handle]->getstring();
            delete(VALDB[ds_handle]);
            return res;
        }else{
            return PLAYER->gethandle();
        }
        return "";
    }

	int apply_status::trigger(mob* actor){
		//all apply statuses should only be used on mobs
        //return 0 ;
        string target_handle = gettargethandle(actor);
        int val = 1;
        if(arguments.count("value")){
            val = stoi(arguments["value"]);
        }
        int dur = -1;
        if(arguments.count("duration")){
            dur = stoi(arguments["duration"]);
        }
        if(arguments.count("status_type")&&MOBDB.count(target_handle)){
            string status_type = arguments["status_type"];
            if(status_type=="heal"){
                heal* h = new heal("Heal",MOBDB[target_handle],dur,val);
                MOBDB[target_handle]->addstatus(h);
                outlog(towstring(actor->gethandle())+wstring(L" healed ")+ towstring(MOBDB[target_handle]->gethandle()) +wstring(L" by ") + to_wstring(val)+wstring(L" points per round for " + to_wstring(dur)+wstring(L" rounds.")));
            }
            return 1;
        }
        return 0;
	}

    int spell_cast::trigger(mob* actor){
        string target_handle = gettargethandle(actor);
        mob* target_mob = MOBDB[target_handle];
        
        int strength_roll = rand()%20+1 + actor->getpresencemod();
        int agility_roll = rand()%20+1 + target_mob->getagilitymod();
        if(agility_roll>strength_roll){
            outlog(towstring(actor->gethandle()) + wstring(L" cast a spell against ") + towstring(target_mob->gethandle())+ wstring(L" but missed PRS") + to_wstring(strength_roll)+wstring(L" vs AGL"+to_wstring(agility_roll)));
            return 0;
        }

        int amount = 1;
        int damage = 1;
        if(arguments.count("damage_roll")){
            string amount_buf;
            string damage_buf;
            bool amtdmg = 1;
            for(char c: arguments["damage_roll"]){
                if(c=='d'){amtdmg=0;continue;}
                if(amtdmg){
                    amount_buf.push_back(c);
                }else{
                    damage_buf.push_back(c);
                }
                
            }
            amount = stoi(amount_buf);
            damage = stoi(damage_buf);
        }

        int rolled_damage = 0;
        for(int i=0;i<amount;i++){
            rolled_damage+=rand()%damage+1;
        }

        //modifiers
        for(modifier* mod: actor->gettotalmodifiers()){
            if(mod->type=="outgoing_damage")rolled_damage+=stoi(mod->val);
        }
        for(modifier* mod: target_mob->gettotalmodifiers()){
            if(mod->type=="incoming_damage")rolled_damage+=stoi(mod->val);
        }
        outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" dealing ") + to_wstring(rolled_damage)+wstring(L" points of damage"));
        if(rolled_damage>0)target_mob->modifyhitpoint(-rolled_damage);
        /*if(arguments.count("value")){
        outlog();
        outlog();
            val = stoi(arguments["value"]);
        }
        int dur = -1;
        if(arguments.count("duration")){
            dur = stoi(arguments["duration"]);
        }
        string target_handle = VALDB[ds_handle]->getstring();
        if(arguments.count("status_type")&&MOBDB.count(target_handle)){
            string status_type = arguments["status_type"];
            if(status_type=="heal"){
                heal* h = new heal("Heal",MOBDB[target_handle],dur,val);
                MOBDB[target_handle]->addstatus(h);
            }
            return 1;
        }*/
        return 0;

    }

	int strength_attack::trigger(mob* actor){
		//all apply statuses should only be used on mobs
        string target_handle = gettargethandle(actor);
        mob* target_mob = MOBDB[target_handle];
        
        int strength_roll = rand()%20+1 + actor->getstrengthmod();
        int agility_roll = rand()%20+1 + target_mob->getagilitymod();
        if(agility_roll>strength_roll){
            outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" but missed STR") + to_wstring(strength_roll)+wstring(L" vs AGL"+to_wstring(agility_roll)));
            return 0;
        }

        int amount = 1;
        int damage = 1;
        if(arguments.count("damage_roll")){
            string amount_buf;
            string damage_buf;
            bool amtdmg = 1;
            for(char c: arguments["damage_roll"]){
                if(c=='d'){amtdmg=0;continue;}
                if(amtdmg){
                    amount_buf.push_back(c);
                }else{
                    damage_buf.push_back(c);
                }
                
            }
            amount = stoi(amount_buf);
            damage = stoi(damage_buf);
        }

        int rolled_damage = 0;
        for(int i=0;i<amount;i++){
            rolled_damage+=rand()%damage+1;
        }

        //modifiers
        for(modifier* mod: actor->gettotalmodifiers()){
            if(mod->type=="outgoing_damage")rolled_damage+=stoi(mod->val);
        }
        for(modifier* mod: target_mob->gettotalmodifiers()){
            if(mod->type=="incoming_damage")rolled_damage+=stoi(mod->val);
        }

        outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" dealing ") + to_wstring(rolled_damage)+wstring(L" points of damage"));
        if(rolled_damage>0)target_mob->modifyhitpoint(-rolled_damage);
        /*if(arguments.count("value")){
        outlog();
        outlog();
            val = stoi(arguments["value"]);
        }
        int dur = -1;
        if(arguments.count("duration")){
            dur = stoi(arguments["duration"]);
        }
        string target_handle = VALDB[ds_handle]->getstring();
        if(arguments.count("status_type")&&MOBDB.count(target_handle)){
            string status_type = arguments["status_type"];
            if(status_type=="heal"){
                heal* h = new heal("Heal",MOBDB[target_handle],dur,val);
                MOBDB[target_handle]->addstatus(h);
            }
            return 1;
        }*/
        return 0;
	}
    int agility_attack::trigger(mob* actor){

		//all apply statuses should only be used on mobs
        
        string target_handle = gettargethandle(actor);
        mob* target_mob = MOBDB[target_handle];
        
        int strength_roll = rand()%20+1 + actor->getagilitymod();
        int agility_roll = rand()%20+1 + target_mob->getagilitymod();
        if(agility_roll>strength_roll){
            outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" but missed AGL") + to_wstring(strength_roll)+wstring(L" vs AGL"+to_wstring(agility_roll)));
            return 0;
        }

        int amount = 1;
        int damage = 1;
        if(arguments.count("damage_roll")){
            string amount_buf;
            string damage_buf;
            bool amtdmg = 1;
            for(char c: arguments["damage_roll"]){
                if(c=='d'){amtdmg=0;continue;}
                if(amtdmg){
                    amount_buf.push_back(c);
                }else{
                    damage_buf.push_back(c);
                }
                
            }
            amount = stoi(amount_buf);
            damage = stoi(damage_buf);
        }

        int rolled_damage = 0;
        for(int i=0;i<amount;i++){
            rolled_damage+=rand()%damage+1;
        }

        //modifiers
        for(modifier* mod: actor->gettotalmodifiers()){
            if(mod->type=="outgoing_damage")rolled_damage+=stoi(mod->val);
        }
        for(modifier* mod: target_mob->gettotalmodifiers()){
            if(mod->type=="incoming_damage")rolled_damage+=stoi(mod->val);
        }
        outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" dealing ") + to_wstring(rolled_damage)+wstring(L" points of damage"));
        if(rolled_damage>0)target_mob->modifyhitpoint(-rolled_damage);
        /*if(arguments.count("value")){
        outlog();
        outlog();
            val = stoi(arguments["value"]);
        }
        int dur = -1;
        if(arguments.count("duration")){
            dur = stoi(arguments["duration"]);
        }
        string target_handle = VALDB[ds_handle]->getstring();
        if(arguments.count("status_type")&&MOBDB.count(target_handle)){
            string status_type = arguments["status_type"];
            if(status_type=="heal"){
                heal* h = new heal("Heal",MOBDB[target_handle],dur,val);
                MOBDB[target_handle]->addstatus(h);
            }
            return 1;
        }*/
        return 0;
    }
    int presence_attack::trigger(mob* actor){

        string target_handle = gettargethandle(actor);
        mob* target_mob = MOBDB[target_handle];
        
        int strength_roll = rand()%20+1 + actor->getpresencemod();
        int agility_roll = rand()%20+1 + target_mob->getagilitymod();
        if(agility_roll>strength_roll){
            outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" but missed PRS") + to_wstring(strength_roll)+wstring(L" vs AGL"+to_wstring(agility_roll)));
            return 0;
        }

        int amount = 1;
        int damage = 1;
        if(arguments.count("damage_roll")){
            string amount_buf;
            string damage_buf;
            bool amtdmg = 1;
            for(char c: arguments["damage_roll"]){
                if(c=='d'){amtdmg=0;continue;}
                if(amtdmg){
                    amount_buf.push_back(c);
                }else{
                    damage_buf.push_back(c);
                }
                
            }
            amount = stoi(amount_buf);
            damage = stoi(damage_buf);
        }

        int rolled_damage = 0;
        for(int i=0;i<amount;i++){
            rolled_damage+=rand()%damage+1;
        }

        //modifiers
        for(modifier* mod: actor->gettotalmodifiers()){
            if(mod->type=="outgoing_damage")rolled_damage+=stoi(mod->val);
        }
        for(modifier* mod: target_mob->gettotalmodifiers()){
            if(mod->type=="incoming_damage")rolled_damage+=stoi(mod->val);
        }
        outlog(towstring(actor->gethandle()) + wstring(L" struck ") + towstring(target_mob->gethandle())+ wstring(L" dealing ") + to_wstring(rolled_damage)+wstring(L" points of damage"));
        if(rolled_damage>0)target_mob->modifyhitpoint(-rolled_damage);
        /*if(arguments.count("value")){
        outlog();
        outlog();
            val = stoi(arguments["value"]);
        }
        int dur = -1;
        if(arguments.count("duration")){
            dur = stoi(arguments["duration"]);
        }
        string target_handle = VALDB[ds_handle]->getstring();
        if(arguments.count("status_type")&&MOBDB.count(target_handle)){
            string status_type = arguments["status_type"];
            if(status_type=="heal"){
                heal* h = new heal("Heal",MOBDB[target_handle],dur,val);
                MOBDB[target_handle]->addstatus(h);
            }
            return 1;
        }*/
        return 0;
    }
    //modifier
    modifier::~modifier(){
        if(parentlist){parentlist->remove(this);}
    }
    modifier::modifier(string tp, string vl){
        type = tp;
        val = vl;
    }
    
    //ITEM
    void item::setinventory(map<string,item*>* pi){parentinventory=pi;}    
    void item::setowner(mob* ownr){owner=ownr;}
    void item::setinventoryhandle(string ih){inventory_handle=ih;}
    void item::setistemplate(bool ist){istemplate=ist;}
    list<modifier*>* item::getmodifiers(){return &modifiers;}
    string item::getname(){return name;}
    string item::getinventoryhandle(){return inventory_handle;}
    list<string>* item::gettags(){return &tags;}
    
    item* item::copy(){
        //if(!act) item(name,modifiers,tags); 
        return new item(name,act,modifiers,tags);
    }
    string item::getappendage(){
        for(modifier* mod: modifiers){
            if(mod->type=="appendage")return mod->val;
        }
        return "";
    }
    int item::use(){
        if(act)return act->trigger(owner);
        return 0;
    }
    bool item::usable(){return act;}
    /*item::item(string nm,list<modifier*> modis, list<string> tagg){
        name = nm;
        //act = acti;
    }*/
    item::item(string nm, action* acti, list<modifier*>modis, list<string> tagg){
        name = nm;
        act = acti;

        for(modifier* m: modis){
            modifiers.push_back(m);
            m->parentlist = &modifiers;
        }
        for(string s: tagg){
            tags.push_back(s);
        }
    }
    item::~item(){
        if(istemplate)delete(act);
        list<modifier*> delmods;
        for(modifier* mod: modifiers){
            delmods.push_back(mod);
        }
        for(modifier* dmod: delmods){
            delete(dmod);
        }
        if(parentinventory){parentinventory->erase(inventory_handle);}
    }
    
    //consumable
    item* consumable::copy(){
        //if(!act)return new consumable(name,modifiers,tags);
        return new consumable(name,act,modifiers,tags);
    }

    int consumable::use(){
        int used = item::use();
        if(used)delete(this);
        return used;
    }

}


