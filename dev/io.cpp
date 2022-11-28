#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <list>
#include <algorithm>
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
using namespace std;




namespace dg{
    int SCREENX;
    int SCREENY;
	

    char* outbuf;

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
				lines.push_back(line);
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
		for(string line: lines){
			move(y+at_line,x);
			printw(line.c_str());
			at_line++;
		}
	}
	//getter for lines
	vector<string>* sprite::getlines(){
		return &lines;
	}
	
	interface_element::interface_element(string hdl, int xl, int yl){
		handle = hdl;
		x = xl;
		y = yl;
	}

	interface_element::~interface_element(){
		cout<<"Element Deactiviated <"<<handle<<'>'<<endl;
	}
	string interface_element::get_handle(){
		return handle;
	}
	void interface_element::print(){
		//this is empty
	}
	void interface_element::print(int, int){
		//this is also empty
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

	uisprite::uisprite(string hdl, sprite* sp, int xl, int yl):interface_element(hdl,xl,yl){
		sprite_reference = sp;
	}
	void uisprite::print(){
		sprite_reference->print(x,y);
	}
	void uisprite::print(int relx, int rely){
		sprite_reference->print(x+relx,y+rely);
	}

	screen::screen(string handle){
		cout<<"Building Screen <"<<handle<<">"<<endl;
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
			delete(p.second);

		}
		cout<<"Screen Deactivated <"<<handle<<'>'<<endl;
	}
	void screen::move(int dx, int dy){
		x += dx;
		y += dy;
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
	void screen::remove_ie(string handle){
		delete(iemap[handle]);
		iemap.erase(handle);
		iestack.remove(handle);
	}
	void screen::print(){
		for(string ie_handle: iestack){
			iemap[ie_handle]->print(x,y);
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
    //called when screensize updates
    void update_screen_size(){
        getmaxyx(stdscr, SCREENX, SCREENY);
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
        //update_screen_size();
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
	void printat(const char *c_str, int x, int y){
		move(y,x);
        printw(c_str);
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
    
}
