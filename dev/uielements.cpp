#include "io.h"
#include "uielements.h"
#include "databases.h"
#include <vector>
#include <iostream>
//#include <ncurses.h>
using namespace dg; 
        
namespace dg{
	//UITEXT
    	uitext::uitext(string itext, string handle, int xl, int yl):interface_element(handle,xl,yl){
		text = 	itext;
    	}
	void uitext::print(int xrel, int yrel){
		printat(text.c_str(),xrel+x,yrel+y);	
	}
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
		cout<<"Dynoval <"<<handle<<"> Deactivated"<<endl;
	}
	//DYNOINT
	dynamicint::dynamicint(string hdl, int val){
		handle = hdl;
		VALDB.insert({handle,this});
		value = val;
		cout<<"Dynoint <"<<handle<<"> Created"<<endl;
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
		cout<<"Dynostring <"<<handle<<"> Created"<<endl;
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
	}
	dynamictext::~dynamictext(){
		if(destroy_on_deconstruct){
			cout<<"DYNOVAL DELETING"<<endl;
			delete(VALDB[dynamicval_handle]);
		}
		//delete(VALDB[dynamicval_handle]);
	}
	void dynamictext::setnotdestroy(){
		destroy_on_deconstruct = false;
	}
	void dynamictext::print(int xrel, int yrel){
		printat((VALDB[dynamicval_handle]->getstring()).c_str(),x+xrel,y+yrel);
	}
	//BACKGROUND
	uibackground::uibackground(int sx, int sy, string handle, int xl, int yl):interface_element(handle,xl,yl){
		size_x = sx;
		size_y = sy;
	}

	void uibackground::print(int xrel, int yrel){
		for(int i = 0; i<size_y;i++){
			printat(string(size_x, ' ').c_str(),x+xrel,y+yrel+i);
		}
	
	}
	//BOX
	void uibox::print(int xrel, int yrel){
		printat((string("┌")+string(size_x-2,'-')+string("┐")).c_str(),x+xrel,y+yrel);
		for(int i=1; i<size_y-1;i++){
			printat((string("|")+string(size_x-2,' ')+string("|")).c_str(),x+xrel,y+yrel+1);
		}	
		printat((string("└")+string(size_x-2,'-')+string("┘")).c_str(),x+xrel,y+yrel+size_y);

	}
} 
