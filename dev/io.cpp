#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <list>
#include <algorithm>
#include <cstring>
#ifdef WINDOWS
#include <conio.h>
#else
#include <ncurses.h>
//#include "libs/llvm-15.0.2.src/BinaryFormat/ELF.h"
#endif
#include "databases.h"
#include "saveload.h"
#include <map>
#include <vector>
#include "io.h"
#include "uielements.h"
#include <locale>
#include <codecvt>
//#include <cassert>
using namespace std;


//str size from: http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
#define ONEMASK ((size_t)(-1) / 0xFF)

static size_t
cp_strlen_utf8(const char * _s)
{
	const char * s;
	size_t count = 0;
	size_t u;
	unsigned char b;

	/* Handle any initial misaligned bytes. */
	for (s = _s; (uintptr_t)(s) & (sizeof(size_t) - 1); s++) {
		b = *s;

		/* Exit if we hit a zero byte. */
		if (b == '\0')
			goto done;

		/* Is this byte NOT the first byte of a character? */
		count += (b >> 7) & ((~b) >> 6);
	}

	/* Handle complete blocks. */
	for (; ; s += sizeof(size_t)) {
		/* Prefetch 256 bytes ahead. */
		__builtin_prefetch(&s[256], 0, 0);

		/* Grab 4 or 8 bytes of UTF-8 data. */
		u = *(size_t *)(s);

		/* Exit the loop if there are any zero bytes. */
		if ((u - ONEMASK) & (~u) & (ONEMASK * 0x80))
			break;

		/* Count bytes which are NOT the first byte of a character. */
		u = ((u & (ONEMASK * 0x80)) >> 7) & ((~u) >> 6);
		count += (u * ONEMASK) >> ((sizeof(size_t) - 1) * 8);
	}

	/* Take care of any left-over bytes. */
	for (; ; s++) {
		b = *s;

		/* Exit if we hit a zero byte. */
		if (b == '\0')
			break;

		/* Is this byte NOT the first byte of a character? */
		count += (b >> 7) & ((~b) >> 6);
	}

done:
	return ((s - _s) - count);
}

namespace dg{
	const int MASKED_NOT = 0;
	const int MASKED_UP = 1;
	const int MASKED_DOWN = 2;
	const int MASKED_LEFT = 3;
	const int MASKED_RIGHT = 4;
	const int MASKED_LEFTRIGHT = 5;
	//https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	wstring towstring(string str){
		return converter.from_bytes(str);
	}

	string tostring(wstring str){
		return converter.to_bytes(str);
	}

    	//int SCREENX;
    	//int SCREENY;
	char* outbuf;
	//SPRITE
	//sprite constructor
	sprite::sprite(string path, string sname){
		ifstream istrm(path);
		if(!istrm.is_open()){
			cout << "failed to open " << path << '\n';
			//return 1;
		}else{
			string line;
			//int linecount = 0;
			while(getline(istrm,line)){
				//linecount++;
				lines.push_back(towstring(line));
			}
			//lines = (string*) malloc(buflst.size()*sizeof(string));
			//copy(buflst.begin(),buflst.end(),lines);
			
		}
		name = sname;
		cout << "Sprite <" << name << "> created."<<endl;
	}

	//sprite deconstructor
	sprite::~sprite(){
		//free(lines);
		//for(string s: lines){
		//	delete(&s);
		//}
		cout << "Sprite <"<< name << "> deconstructed."<<endl;
	}
	
	//print sprite in window at coordinate x,y
	void sprite::print(int x, int y){
		int at_line = 0;
		for(wstring line: lines){
			move(y+at_line,x);
			printw(tostring(line).c_str());
			at_line++;
		}
	}
	//getter for lines
	vector<wstring>* sprite::getlines(){
		return &lines;
	}
	
	//INTERFACE_ELEMENT

	interface_element::interface_element(string hdl, int xl, int yl){
		handle = hdl;
		x = xl;
		y = yl;
		iemask.minx = 0;
		iemask.miny = 0;
		iemask.maxx = SCREENX;
		iemask.maxy = SCREENY;
		//ievariant = 0;
	}

	interface_element::~interface_element(){
		cout<<"Element Deactiviated <"<<handle<<'>'<<endl;
	}
	string interface_element::get_handle(){
		return handle;
	}
	void interface_element::setmask(int mix, int miy, int max, int may){
		iemask.minx = mix;
		iemask.miny = miy;
		iemask.maxx = max;
		iemask.maxy = may;
	}
	void interface_element::setmask(int a, int b, int c, int d, int e){
		custommask = true;
		setmask(a,b,c,d);
	}
	void interface_element::print(){
		//this is empty
	}
	void interface_element::print(int, int){
		//this is also empty
	}
	void interface_element::addattr(int attr){
		attrs.push_back(attr);
	}
	void interface_element::rmvattr(int attr){
		attrs.remove(attr);
	}
	void interface_element::move(int dx, int dy){
		x += dx;
		y += dy;
	}
	void interface_element::setloc(int xl, int yl){
		x = xl;
		y = yl;
	}
	bool interface_element::getfunctional(){
		return functional;
	}
	void interface_element::setfunctional(bool func){
		functional = func;
	}
	bool interface_element::iscustommask(){
		return custommask;
	}
	mask interface_element::getmask(){
		return iemask;
	}
	void interface_element::setcustommask(bool cm){
		custommask = cm;
	}
	int interface_element::ismasked(int relx, int rely){
		int fx = relx + x;
		int fy = rely + y;
		int tx = fx + size_x;
		int ty = fy + size_y;

		if(fy<iemask.miny) return MASKED_UP;
		if(ty>iemask.maxy) return MASKED_DOWN;
		if(fx<iemask.minx) return MASKED_LEFT;
		if(tx>iemask.maxx) return MASKED_RIGHT;

		return MASKED_NOT;
	}
	int interface_element::getx(){return x;}
	int interface_element::gety(){return y;}
	/*int interface_element::getvariant(){
		return ievariant;
	}*/
	

	//UISPRITE
	uisprite::uisprite(string hdl, sprite* sp, int xl, int yl):interface_element(hdl,xl,yl){
		sprite_reference = sp;
		vector<wstring> lines = *(sp->getlines());
		size_y = lines.size();
		int max = 0;
		for(wstring line: lines){
			int size = line.size();
			if(size > max) max = size;
		}
		size_x = max;
	}
	void uisprite::print(){
		sprite_reference->print(x,y);
	}
	void uisprite::print(int relx, int rely){
		vector<wstring>* spritelines = sprite_reference->getlines();
		int at_line = 0;
		for(wstring line: *spritelines){
			printat(line,x+relx,y+rely+at_line,iemask);
			at_line++;
		}


	}

	sprite* uisprite::getsprite(){
		return sprite_reference;
	}
	
	//SCREEN
	screen::screen(string handle){
		cout<<"Building Screen <"<<handle<<">"<<endl;	int at_line = 0;
		opaque = false;
		this->handle = handle;
		ACTIVESCREENS.insert({handle,this});
		cout<<"Screen Activated: ";
		if(DEBUG){
			for(pair<string,screen*> p: ACTIVESCREENS){
				cout << p.first << ' ' << p.second;
			}
		}
		cout<<endl;
	}

	screen::~screen(){
		ACTIVESCREENS.erase(handle);
		for(pair<string,interface_element*> p: iemap){
			//interface_element* ie = p.second;
			delete(p.second);
			/*switch(ie->getvariant()){
				case 0:{
					cout<<'0'<<endl;
					delete(ie);
					break;
				}
				case 1:{ 
					cout<<'1'<<endl;
					delete((dynamictext*)ie);
					break;
				}
				default:{ 
					cout<<"def"<<endl;
					delete(ie);
					break;
				}
			}*/

		}
		cout<<"Screen Deactivated <"<<handle<<'>'<<endl;
	}
	void screen::destruct(){
		delete this;
	}
	void screen::move(int dx, int dy){
		x += dx;
		y += dy;
	}
	string screen::gethandle(){
		return handle;
	}
	void screen::setloc(int xl, int yl){
		x = xl;
		y = yl;
	}
	void screen::add_ie(string handle, interface_element* ie){
		iemap.insert({handle,ie});
		iestack.push_back(handle);
	}
	void screen::add_ie(interface_element* ie){
		iemap.insert({ie->get_handle(),ie});
		iestack.push_back(ie->get_handle());
	}
	void screen::add_non_visible_ie(interface_element* ie){
		iemap.insert({ie->get_handle(),ie});
	}
	void screen::remove_ie(string handle){
		delete(iemap[handle]);
		iemap.erase(handle);
		iestack.remove(handle);
	}
	void screen::print(){
		//if it is opaque, then, it will cover all screens below (clear screen)
		if(opaque){
			clear();
		}
		for(string ie_handle: iestack){
			interface_element* printie = iemap[ie_handle];
			for(int attr: printie->attrs){
				attron(attr);
			}
			printie->print(x,y);
			for(int attr: printie->attrs){
				attroff(attr);
			}
		}	
	}
	//move element by x and y
	void screen::move_ie(string handle,int x,int y){
		iemap[handle]->move(x,y);
	}
	//execute key
	int screen::execute(int key){
		return 0;
	}

	bool screen::getcontrollable(){
		return controllable;
	}

	void screen::setcontrollable(bool con){
		controllable = con;
	}
	void screen::setcenter(bool cen){
		center = cen;
	}
	bool screen::iscenter(){
		return center;
	}
	map<string,interface_element*> screen::getiemap(){
		return iemap;
	}
	//METHODS
    //called when screensize updates
    void update_screen_size(){
        getmaxyx(stdscr, SCREENY, SCREENX);
	for(pair<string, screen*> screenp: ACTIVESCREENS){
		for(pair<string, interface_element*> iep: screenp.second->getiemap()){
			if(!(iep.second->iscustommask()))iep.second->setmask(0,0,SCREENX,SCREENY);
		}

	}
        //outbuf = (char*)malloc((SCREENX*SCREENY+1)*sizeof(char));
        //outbuf[SCREENX*SCREENY+1] = '\0';
    }
    //initialize ncurses librarys
    int curses_init(){
	setlocale(LC_ALL, "");
        initscr();
        timeout(-1);
		noecho();
		curs_set(0);
        update_screen_size();
	keypad(stdscr, TRUE);
	new debugoverlay();//DEBUGOVERLAY handle	
        return 0;
    }

	//wrapup for curses windows
    int curses_wrapup(){
        endwin();
		vector<screen*> deactivates;
		for(pair<string,screen*> p: ACTIVESCREENS){
			deactivates.push_back(p.second);
		}
		for(screen* s: deactivates){
			delete(s);
		}
        return 0;
    }
	//draw character
    void drawc(char c, int x, int y){
        outbuf[10] = c;
    }
    /*======TEST FUNCTIONS======*/
    void test_screen_size(){
        printw("%d %d|",SCREENX, SCREENY);
        while(1){
            if(getch()==KEY_RESIZE){
                update_screen_size();
                break;
            }
        }
        printw("%d %d|",SCREENX, SCREENY);
        getch();
    }
    void printsprite(){
		SPRITEDB["celt_knot_1"]->print(0,10);
		SPRITEDB["dungeon_core_title"]->print(6,10);
    }
    void test_screen_draw(){
        move(5,10);
        printw("ABCD\nABCD");
        //refresh();
    }
    /*=^^^==TEST FUNCTIONS==^^^=*/
	void printat(std::wstring outstr, int x, int y, dg::mask iemask){
		if(y>(iemask.maxy-1)||y<iemask.miny||x>iemask.maxx||y>SCREENY-1||x>SCREENX)return;
		int charlen = outstr.size();
		//VALDB["DEBUG_OUT_1"] -> set(to_string(charlen));
		if((x+charlen)>iemask.maxx||x<iemask.minx){
			//i'll do sth extra extra stupid, don't judge me, my brain juices lacking now :D
			move(y,x);
			if((x+charlen)>iemask.maxx){
				int diff = iemask.maxx-x;
				//outstr=outstr.substr(0,charlen-diff);
				printw(tostring(outstr.substr(0,diff)).c_str());
				return;
			}
			if(x<iemask.minx){
				int diff = iemask.minx-x;
				outstr=outstr.substr(diff);
				move(y,x+diff);
			}
			printw(tostring(outstr).c_str());
			return;
		}
		move(y,x);
        	printw(tostring(outstr).c_str());
	}
	void printat(wstring outstr, int x, int y){
		mask iemask;
		printat(outstr,x,y,iemask);

	}
	//input output functions called in loop
    int ioloop(){
		//clear the screen
		clear();
        //display current screenstack
		for(string screen_handle: SCREENSTACK){
			screen* scr = ACTIVESCREENS[screen_handle];
			scr->print();
		}
		//if debug mode, draw debug overlay
		ACTIVESCREENS["DEBUGOVERLAY"] ->print();
		//wait for valid input and execute it
		int exec_code = 0;
		while(!exec_code){
			screen* current_control_screen = (ACTIVESCREENS[*(--SCREENSTACK.end())]);
			int input = 0;	
			if(current_control_screen->getcontrollable()){
				input = getch();
			}
			//global input
			switch(input){
				/*case('q'):{
					exec_code = 1;
					EXIT = 1;
					break;
				}*/
				case(KEY_RESIZE):{
					getmaxyx(stdscr, SCREENY, SCREENX);
					/*for(string scrhandle: SCREENSTACK){
						screen* scr = ACTIVESCREENS[scrhandle];
						if(scr->iscenter())scr->setloc(SCREENX,SCREENY);
					}*/
					update_screen_size();
					exec_code = 1;
					break;
				}
				
				default:{
					//screen input
					exec_code = current_control_screen->execute(input);
					break;
				}
			}
		}
        return 0;
    }
    debugoverlay::debugoverlay():screen("DEBUGOVERLAY"){
		setloc(0,0);
		new dynamicstring("DEBUG_OUT_1", "");
		add_ie(new dynamictext("DEBUG_OUT_1","DEBUG_OUT_!",0,1));
	}
    void debugoverlay::print(){
	    screen::print();
	    printat(to_wstring(SCREENX),0,0);
	    /*
	    if(ACTIVESCREENS.count("title_screen")){
		   //https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
		    string title_s = (((uisprite*)(ACTIVESCREENS["title_screen"]->getiemap()["title_bar"]))->getsprite()->getlines())->at(0);
		    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                    std::wstring wide = converter.from_bytes(title_s);
		    std::string narrow = converter.to_bytes(wide.substr(0,3));

		    printat(to_string(wide.size()),0,2);
		    printat(narrow, 0,3);

	    }*/
	    //if(ACTIVESCREENS.count("title_screen")) printat(to_string(FindCutPosition((((uisprite*)(ACTIVESCREENS["title_screen"]->getiemap()["title_bar"]))->getsprite()->getlines())->at(0),20)),0,3);
    }
}
