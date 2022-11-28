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
        free(outbuf);
        return 0;
    }
	//draw character
    void drawc(char c, int x, int y){
        outbuf[10] = c;
    }
	//out buffer
    void buffer_out(){
        
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
        curses_init();
        printsprite();
        getch();
        curses_wrapup();
        return 0;
    }
    
}
