#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
//#include "libs/llvm-15.0.2.src/BinaryFormat/ELF.h"
#endif

#include "databases.h"
#include <iostream>
#include <algorithm>
#include "libs/pugixml-1.13/src/pugixml.hpp"
#include "event.h"
#include <filesystem>
#include "io.h"
#include "mob.h"
#include <map>
#include <fstream>
#include <unistd.h>
#include "saveload.h"
using namespace pugi;
using namespace std;
using namespace dg;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

//references:
//https://linuxhint.com/parse_xml_in_cpp/
//https://www.tutorialspoint.com/find-out-the-current-working-directory-in-c-cplusplus
//https://blog.csdn.net/wteruiycbqqvwt/article/details/112664432
//https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
//Dynamic Function Load [Name]: #ended up not implementing
//https://stackoverflow.com/questions/25270275/get-functions-names-in-a-shared-library-programmatically

// get the currrent working directory to current program
//output is the whole path such as D:\...\...
int get_current_dir(char pBuf[FILENAME_MAX]) {
    int len;
    #ifdef WINDOWS
    
    //gets the directory without the file name
    len = GetModuleFileName(NULL, pBuf, FILENAME_MAX);
    #else
    len = readlink("/proc/self/exe", pBuf, FILENAME_MAX);
    #endif
	
    // find the absolute path
    if(len>0&&len<FILENAME_MAX){
        //cout<<pBuf<<endl;
        return len;
    }
    return 0;
}


namespace dg{
    char curDir[FILENAME_MAX];
    int filelen;
	//map<string, sprite*> SPRITEDB;
	
	//from: https://gist.github.com/thirdwing/da4621eb163a886a03c5
	//gets memeroy usage || for debbugging use only (not really useful, use valgrind instead)
	void process_mem_usage(double& vm_usage, double& resident_set)
	{
	    vm_usage     = 0.0;
	    resident_set = 0.0;
	
	    // the two fields we want
	    unsigned long vsize;
	    long rss;
	    {
	        std::string ignore;
	        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
	        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
	                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
	                >> ignore >> ignore >> vsize >> rss;
	    }
	
	    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
	    vm_usage = vsize / 1024.0;
	    resident_set = rss * page_size_kb;
	}
	
	//loopthrough sprite folders for sprites
	int spriteloopthrough(){
		string path = string(curDir, filelen);
		string imgpath = path.substr(0,path.find_last_of("\\/")) + "/data/sprite_asset";
		for(const filesystem::directory_entry& dirEntry : recursive_directory_iterator(imgpath)){
			
			if(dirEntry.path().filename().extension()!=".sprite"||dirEntry.file_size()==0){
				continue;
			}
			string spath(dirEntry.path().c_str());
            string sname(dirEntry.path().filename().stem().c_str());
			if(DEBUG)cout<<"Loading Sprite:"<<sname<<endl;
			if(SPRITEDB.count(sname) != 0){
				if(DEBUG)cout<<"Sprite duplicate found, replacing with new sprite"<<endl;
				//delete the existing sprite at that address
				delete(SPRITEDB[sname]);
				map<string,sprite*>::iterator it = SPRITEDB.find(sname);
				//if(DEBUG)Replace value instead of inserting new one (it caused a memory leak)
				if(it != SPRITEDB.end()){
					it->second = new sprite(spath,sname);
				}
				if(DEBUG)cout<<"Sprite Replaced"<<endl;
			}else{
				SPRITEDB.insert({sname,new sprite(spath,sname)});
				if(DEBUG)cout<<"Sprite Created"<<endl;
			}
			if(DEBUG)cout<<"===Sprite Loaded==="<<endl;
		}
		return 0;
	}
    
        
    int loadItems(){
        xml_document itemsDB;
        
        string path = string(curDir,filelen);
        string ppath = path.substr(0,path.find_last_of("\\/")) + "/data/item_defs/main_item_def.xml";
        wstring widestr = std::wstring(ppath.begin(), ppath.end());
        const wchar_t* widecstrpath = widestr.c_str();
        //cout<<ppath<<endl;

        if (!itemsDB.load_file(widecstrpath)){
            if(DEBUG)cout<<"ITEM FILE MISSING, itemdefs not found"<<endl;
            return 1;
        }

        xml_node events = itemsDB.child("ItemDef");
        for (xml_node_iterator it = events.begin(); it != events.end(); ++it)
        {
            string itemhandle = it->attribute("Name").value();
            //item* itemtemplate = NULL;
            if(DEBUG)cout << it->name()<< " | " << it->attribute("Name").value();
            string itemtype = it->name();
            xml_node action_node = it->child("action");
            action* act = NULL;
            if(action_node){
                //This could have been a map, but, too much work and crunching rn, so, NO :D
                xml_node specific_action_node = *action_node.begin();
                string actiontype = specific_action_node.name();
                if(DEBUG)cout<<endl<<actiontype;
                if(actiontype=="apply_status"){
                    map<string,string> arguments;
                    xml_node status_node = *(++(specific_action_node.begin()));
                    arguments.insert({"status_type",status_node.name()});
                    xml_attribute duration_attr = status_node.attribute("Duration");
                    if(duration_attr){
                        string duration=duration_attr.value();
                        arguments.insert({"duration",duration});
                    }
                    string val = status_node.text().get();
                    arguments.insert({"value",val});
                    act = new apply_status(arguments);
                    //cout<<endl<<duration;
                }
                if(actiontype=="strength_attack"){
                    map<string,string> arguments;
                    xml_node specific_action_node = *action_node.begin();
                    xml_node damage_node = specific_action_node.child("damage_roll");
                    string damage = damage_node.text().get();
                    arguments.insert({"damage_roll",damage});
                    act = new strength_attack(arguments);
                }   
                if(actiontype=="agility_attack"){
                    map<string,string> arguments;
                    xml_node specific_action_node = *action_node.begin();
                    xml_node damage_node = specific_action_node.child("damage_roll");
                    string damage = damage_node.text().get();
                    arguments.insert({"damage_roll",damage});
                    act = new agility_attack(arguments);
                }
                if(actiontype=="presence_attack"){
                    map<string,string> arguments;
                    xml_node specific_action_node = *action_node.begin();
                    xml_node damage_node = specific_action_node.child("damage_roll");
                    string damage = damage_node.text().get();
                    arguments.insert({"damage_roll",damage});
                    act = new presence_attack(arguments);
                }

                if(actiontype=="spell_cast"){
                    map<string,string> arguments;
                    xml_node specific_action_node = *action_node.begin();
                    xml_node damage_node = specific_action_node.child("damage_roll");
                    string damage = damage_node.text().get();
                    arguments.insert({"damage_roll",damage});
                    act = new spell_cast(arguments);
                }
            }
            list<modifier*> modifiers;
            xml_node modifier_node = it->child("modifiers");
            if(modifier_node){
                for(xml_node_iterator mit = modifier_node.begin();mit!=modifier_node.end();++mit){
                    modifiers.push_back(new modifier(mit->name(),mit->text().get()));
                }
            }
            list<string> tags;
            xml_node tag_node = it->child("tags");
            if(tag_node){
                
            }
            tags.push_back(itemtype);
            //modifiers.push_back(new modifier("placeholder",-1));
            xml_node droprate = it->child("dropchance");
            if(droprate){
                int dropchance = stoi(droprate.text().get());
                LOOTTABLE.insert({itemhandle,dropchance});
            }
            if(itemtype=="Consumable"){
                item* consumabletemplate = new consumable(itemhandle,act,modifiers,tags);
                consumabletemplate->setistemplate(true);
                 
                ITEMDB.insert({itemhandle,consumabletemplate});
            }
            if(itemtype=="Equipment"||itemtype=="Spell"){
                item* generaltemplate = new item(itemhandle,act,modifiers,tags);
                generaltemplate->setistemplate(true);

                ITEMDB.insert({itemhandle,generaltemplate});
            }
            
            
            
            if(DEBUG)cout << endl;
        }

        if(DEBUG)cout << endl;
        return 0;
    
    }

    int loadMobs(){
        xml_document mobtemplateDB;
        
        string path = string(curDir,filelen);
        string ppath = path.substr(0,path.find_last_of("\\/")) + "/data/mobs.xml";
        wstring widestr = std::wstring(ppath.begin(), ppath.end());
        const wchar_t* widecstrpath = widestr.c_str();
        cout<<ppath<<endl;

        if (!mobtemplateDB.load_file(widecstrpath)){
            if(DEBUG)cout<<"MOB FILE MISSING, mobs.xml not found"<<endl;
            return 1;
        }

        xml_node mobs = mobtemplateDB.child("ClassDef");
        
        
        for (xml_node_iterator it = mobs.begin(); it != mobs.end(); ++it)
        {
            xml_node aglN = it->child("agility");
            xml_node preN = it->child("presence");
            xml_node strN = it->child("strength");
            xml_node touN = it->child("toughness");
            string mobtemplatename = it->attribute("Name").value();
            int agl = stoi(aglN.text().get());
            int pre = stoi(preN.text().get());
            int str = stoi(strN.text().get());
            int tou = stoi(touN.text().get());
            mob* mobtemplate = new mob(mobtemplatename,agl,pre,str,tou);
            xml_node eqs = it->child("equipments");
            xml_node skl = it->child("skills");
            for (xml_node_iterator cit = eqs.begin(); cit != eqs.end(); ++cit){
                mobtemplate->additem(cit->name());
                
            }
            for(pair<string,item*>p:*mobtemplate->getinventory()){
                mobtemplate->equip(p.first);
            }
            for (xml_node_iterator cit = skl.begin(); cit != skl.end(); ++cit){
                mobtemplate->additem(cit->name());
            }
            MOBTEMPLATES.insert({mobtemplatename,mobtemplate});
            MOBDB.erase(mobtemplatename);
            mobtemplate->settemplate();

        }

        return 0;
    }
    int loadEvents(){
        xml_document eventDB;
        
        string path = string(curDir,filelen);
        string ppath = path.substr(0,path.find_last_of("\\/")) + "/data/events.xml";
        wstring widestr = std::wstring(ppath.begin(), ppath.end());
        const wchar_t* widecstrpath = widestr.c_str();
        //cout<<ppath<<endl;

        if (!eventDB.load_file(widecstrpath)){
            if(DEBUG)cout<<"EVENT FILE MISSING, events.xml not found"<<endl;
            return 1;
        }

        xml_node events = eventDB.child("EventDef");
        for (xml_node_iterator it = events.begin(); it != events.end(); ++it)
        {
            if(DEBUG)cout << "Event:" << it->attribute("Name").value();
            

            for (xml_node_iterator cit = it->begin(); cit != it->end(); ++cit){
                if(DEBUG)cout << endl << '\t' << cit->name() << ": " << cit->text().get();
            }

            if(DEBUG)cout << endl;
        }

        if(DEBUG)cout << endl;
        return 0;
    }

    	//executable directory
	int loadInit(){
        filelen = get_current_dir(curDir);
        if(!filelen){
            if(DEBUG)cout<<"Unable to get executable directory, load unsuccessful. [are you using mac :3]"<<endl;
            return 1; 
        }
        if(loadEvents()){
            return 1;
        }
		if(spriteloopthrough()){
			return 1;
		}
        if(loadItems()){
            return 1;
        }
        if(loadMobs()){
            return 1;
        }
        return 0;
    }

	int loadWrap(){
		//deconstruct SPRITEDB
		for(pair<const string,sprite*> p: SPRITEDB){
			/*
			for(string line: *(p.second->getlines())){
				cout<<line<<endl;
			}
			*/
			delete(p.second);
		}
		return 0;
	}
}
