#include "io.h"
#include "uielements.h"
#include "databases.h"
#include <vector>
#include <list>
#include <iostream>
//#include <ncurses.h>
using namespace dg; 
        
namespace dg{
	//UITEXT
    	uitext::uitext(wstring itext, string handle, int xl, int yl):interface_element(handle,xl,yl){
		text = 	itext;
		size_y = 1;
		size_x = itext.size();
    	}
	void uitext::print(int xrel, int yrel){
		printat(text,xrel+x,yrel+y,iemask);	
	}
	wstring uitext::getstring(){return text;}

	void uitext::updatesizex(){size_x=text.size();}
	void uitext::setstring(wstring intxt){text=intxt;updatesizex();}
	//DYNOVAL
	void dynoval_wrap(){
		vector<dynamicvalue*> buflst;
		for(pair<string, dynamicvalue*> p: VALDB){
			buflst.push_back(p.second);
		}
		for(dynamicvalue* dv: buflst){
			delete(dv);
		}
	}

	
	dynamicvalue::~dynamicvalue(){
		VALDB.erase(handle);
		if(DEBUG)cout<<"Dynoval <"<<handle<<"> Deactivated"<<endl;
	}
	//DYNOINT
	dynamicint::dynamicint(string hdl, int val){
		handle = hdl;
		VALDB.insert({handle,this});
		value = val;
		if(DEBUG)cout<<"Dynoint <"<<handle<<"> Created"<<endl;
	}

	int dynamicint::getint(){
		return any_cast<int>(value);
	}

	string dynamicint::getstring(){
		return to_string(getint());
	}
	//DYNOSTRING
	dynamicstring::dynamicstring(string hdl, string val){
		handle = hdl;
		VALDB.insert({handle,this});
		value = val;
		if(DEBUG)cout<<"Dynostring <"<<handle<<"> Created"<<endl;
	}
	string dynamicstring::getstring(){
		return any_cast<string>(value);
	}

	void dynamicvalue::set(any val){
		value = val;
	}
	any dynamicvalue::get(){
		return value;
	}
	string dynamicvalue::gethandle(){
		return handle;
	}
	//DYNOTEXT
	dynamictext::dynamictext(string dynohandle, string ie_handle, int xl, int yl):interface_element(ie_handle,xl,yl){
		//ievariant=1;
		destroy_on_deconstruct = true;
		dynamicval_handle = dynohandle;
		size_y = 1;
		size_x = VALDB[dynohandle]->getstring().size();
	}
	dynamictext::~dynamictext(){
		if(destroy_on_deconstruct){
			if(DEBUG)cout<<"DYNOVAL DELETING"<<endl;
			delete(VALDB[dynamicval_handle]);
		}
		//delete(VALDB[dynamicval_handle]);
	}
	void dynamictext::setnotdestroy(){
		destroy_on_deconstruct = false;
	}
	void dynamictext::print(int xrel, int yrel){
		printat(towstring(VALDB[dynamicval_handle]->getstring()),x+xrel,y+yrel, iemask);
	}
	//BACKGROUND
	uibackground::uibackground(int sx, int sy, string handle, int xl, int yl):interface_element(handle,xl,yl){
		size_x = sx;
		size_y = sy;
	}

	void uibackground::print(int xrel, int yrel){
		for(int i = 0; i<size_y;i++){
			printat(wstring(size_x, ' '),x+xrel,y+yrel+i, iemask);
		}
	
	}
	//BOX
	void uibox::print(int xrel, int yrel){
		printat((L"╔"+wstring(size_x-2,L'─')+L"╗"),x+xrel,y+yrel,iemask);
		for(int i=1; i<size_y;i++){
			printat((L"│"+wstring(size_x-2,' ')+L"│"),x+xrel,y+yrel+i,iemask);
		}	
		printat((L"╚"+wstring(size_x-2,L'─')+L"╝"),x+xrel,y+yrel+size_y,iemask);

	}

	uiboxVseperator::uiboxVseperator(int sy,string handle, int xl, int yl):interface_element(handle,xl,yl){
		size_x = 1;
		size_y = sy;
	}
	void uiboxVseperator::print(int xrel, int yrel){
		printat(L"╦",x+xrel,y+yrel,iemask);
		for(int i=1; i<size_y;i++){
			printat(L"│",x+xrel,y+yrel+i,iemask);
		}	
		printat(L"┴",x+xrel,y+yrel+size_y,iemask);
	}

	uiboxHseperator::uiboxHseperator(int sx,string handle, int xl, int yl):interface_element(handle,xl,yl){
		size_x = sx;
		size_y = 1;
	}
	void uiboxHseperator::print(int xrel, int yrel){
		printat(wstring(L"╠")+wstring(size_x-2,L'─')+wstring(L"┤"),x+xrel,y+yrel,iemask);
		//for(int i=1; i<size_y;i++){
		//	printat(L"│",x+xrel,y+yrel+i,iemask);
		//}	
		//printat(L"┤",x+xrel,y+yrel+size_y,iemask);
	}
	void uiprogressbar::updatemax(int max){maximum=max;}
	void uiprogressbar::updateval(int val){value=val;}
	uiprogressbar::uiprogressbar(int sx,int val, int max, string handle, int xl, int yl):interface_element(handle,xl,yl){
		maximum = max;
		value = val;
		size_x = sx;
		size_y = 1;
	}
	void uiprogressbar::print(int xrel, int yrel){
		int fullbars = 0;
		if(value)fullbars = ((double)((double)value/(double)maximum)*size_x) ;
        if(value>maximum)fullbars=size_x;
		printat(wstring(fullbars,L'█')+wstring(size_x-fullbars,L'▁'),x+xrel,y+yrel);
	}

	void uiprogressbar2::print(int xrel, int yrel){
		int fullbars = 0;
		if(value)fullbars = ((double)((double)value/(double)maximum)*size_x) ;
        if(value>maximum)fullbars=size_x;
		printat(wstring(fullbars,L'▮')+wstring(size_x-fullbars,L'▯'),x+xrel,y+yrel);
	}
    
    /*statblock::~statblock(){

    }*/
    statblock::statblock(mob* target, string handle, int xl, int yl):interface_element(handle,xl,yl){
        target_mob = target;
    }

    void statblock::print(int xrel, int yrel){
        int fx = xrel + x;
        int fy = yrel + y;
        //this is very dumb
        //this is very inefficient
        //but this is worth it
        //when you're having double vision
        uibox basebox(28,20,"doesn't matter",0,0);
        basebox.print(fx,fy);
        string target_name = target_mob->gethandle();
        printat(wstring(L"┌")+wstring(target_name.size(),L'═')+wstring(L"┐"),fx+1,fy-1);
        printat(wstring(L"╣")+towstring(target_name)+wstring(L"╠"),fx+1,fy);
        uisprite portrait("look", SPRITEDB["character_eye"], 1, 1);
        portrait.print(fx,fy);
        uiboxHseperator s1(28, "does anything?", 0, 6);
        s1.print(fx,fy);
        int curhp = target_mob->getcurrenthitpoint();
        int maxhp = target_mob->getmaxhitpoint();
        printat(wstring(L"HEALTH ")+ to_wstring(curhp)+wstring(L"/")+to_wstring(maxhp),fx+2,fy+6);
        s1.print(fx,fy+2);
        uiprogressbar p1(26, curhp, maxhp, "idk", 1, 7);
        p1.print(fx,fy);
         
        string status_text = "";
        
        for(status_effect* s: *(target_mob->getstatuslist())){
           status_text += s->getname() + string("|") + to_string(s->getvalue()) + string("|") + to_string(s->getduration()) + string(" "); 
        }
        printat(L"STATUS",fx+2,fy+8);
        printat(towstring(status_text),fx+1,fy+9);
        s1.print(fx,fy+4);
        printat(L"EQUIPMENTS",fx+2,fy+10);
        int fromy = fy+11;
        for(string equip: *target_mob->getequipments()){
            printat(towstring(equip),fx+1,fromy);
            fromy++;
        }

    }
    playlog::playlog(int sx, int sy, string handle, int xl, int yl):interface_element(handle,xl,yl){
       //iemask = mask(x,y,);
       size_x = sx;
       size_y = sy;
    }
    void playlog::print(int xrel, int yrel){
        int fx = xrel+x;
        int fy = yrel+y;

        uibox basebox(size_x,size_y,"nope",0,0);
        basebox.print(fx,fy);
        printat(L"JOURNAL",fx+1,fy);
        int limit = size_y-1;
        int count = 0;
        for(list<wstring>::reverse_iterator it = SYSTEMLOG.rbegin();it!=SYSTEMLOG.rend();it++){
            if(count>=limit)break;
            printat(*it,fx+1,fy-1+(size_y-count));
            count++;
        }
    }
} 

