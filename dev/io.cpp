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
	};

	//sprite deconstructor
	sprite::~sprite(){
		//free(lines);
		//for(string s: lines){
		//	delete(&s);
		//}
		cout << "Sprite <"<< name << "> deconstructed."<<endl;
	};
	
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
	
	interface_element::~interface_element(){
		cout<<"Element Deactiviated <"<<handle<<'>'<<endl;
	}
	string interface_element::get_handle(){
		return handle;
	}
	void interface_element::print(){
	
	}
	bool interface_element::functional(){
		return false;
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
	
	void screen::add_ie(string handle, interface_element* ie){
		iemap.insert({handle,ie});
	}
	void screen::add_ie(interface_element* ie){
		iemap.insert({ie->get_handle(),ie});
	}
	void screen::remove_ie(string handle){
		delete(iemap[handle]);
		iemap.erase(handle);
	}
	void screen::print(){
		for(pair<string,interface_element*> p: iemap){
			p.second->print();
		}	
	}
	int screen::execute(int key){
		return 0;
	}
    //called when screensize updates
    void update_screen_size(){
        getmaxyx(stdscr, SCREENX, SCREENY);
        free(outbuf);
        outbuf = (char*)malloc((SCREENX*SCREENY+1)*sizeof(char));
        outbuf[SCREENX*SCREENY+1] = '\0';
    }
    //initialize ncurses librarys
    int curses_init(){
		setlocale(LC_ALL, "");
        initscr();
        timeout(-1);
        update_screen_size();
        return 0;
    }

	//wrapup for curses windows
    int curses_wrapup(){
        endwin();
		for(pair<string,screen*> p: ACTIVESCREENS){
			delete(p.second);
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
	//input output functions called in loop
    int ioloop(){
        //display current screenstack
		for(string screen_handle: SCREENSTACK){
			screen* scr = ACTIVESCREENS[screen_handle];
			scr->print();
		}
		//wait for valid input and execute it
		int exec_code = 1;
		while(!exec_code){
			int input = getch();
			//global input
			//screen input
			exec_code = (ACTIVESCREENS[*(--SCREENSTACK.end())])->execute(input);
		}
        return 0;
    }
    
}
