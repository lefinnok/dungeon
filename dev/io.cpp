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
#include "uielements.h"
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
		//ievariant = 0;
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
	void interface_element::addattr(int attr){
		attrs.push_back(attr);
	}
	void interface_element::rmvattr(int attr){
		attrs.remove(attr);
	}
	
	//move the elements's coordinate
	//input is dx(change in x coordinate) and dy(change in y coordinate)
	//output is the new x and y coordinate
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

	/*int interface_element::getvariant(){
		return ievariant;
	}*/

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
	
	//move the screen elements by x and y
	//input is dx(change in x coordinate) and dy(change in y coordinate)
	//output is the new x and y coordinate
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
	void screen::remove_ie(string handle){
		delete(iemap[handle]);
		iemap.erase(handle);
		iestack.remove(handle);
	}
	void screen::print(){
		//if it is opaque, then, it will cover all screens below (clear screen)
		//input 
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
	//check if the screen is controllable or not
	//input is the bool value of controllable in class screen
	//output is the bool value of controllable
	bool screen::getcontrollable(){
		return controllable;
	}
	
	//set the screen to be controllable or not
	//input is the bool value(true/false)
	//output is updating the bool value of controllable
	void screen::setcontrollable(bool con){
		controllable = con;
	}
	
	//set the screen to be at the center or not
	//input is the bool value(true/false)
	//output is updating the bool value of centre
	void screen::setcenter(bool cen){
		center = cen;
	}
	
	//get the bool value of centre
        //output is the bool value of center
	bool screen::iscenter(){
		return center;
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
					getmaxyx(stdscr, SCREENY, SCREENX);
					/*for(string scrhandle: SCREENSTACK){
						screen* scr = ACTIVESCREENS[scrhandle];
						if(scr->iscenter())scr->setloc(SCREENX,SCREENY);
					}*/
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
