#ifndef _DGIO_H_
#define _DGIO_H_
#include <string>
#include <vector>
#include <list>
#include "saveload.h"
//???
using namespace std;
namespace dg{
	//base sprite, not an interface element, but the storage of sprite characters
	class sprite{
		public:
			sprite(string,string);
			~sprite();
			vector<string>* getlines();
			void print(int,int);
		private:
			//int size_x,size_y;
			vector<string> lines;
			string name;
	};
	//user interface element, base class of all elements, must contain print function
	class interface_element{
		public:
			~interface_element();
			virtual void print();
			virtual bool functional();
			string get_handle();
		private:
			int x,y;
			string handle;
	};
	//an instance that references the sprite image which has its own coordinates
	class uisprite: interface_element{
		public:
			uisprite(sprite*);
			void print();
		private:
			sprite* sprite_reference;
			

	};
	class screen{
		public:
			//constructor
			screen(string);
			//deconstructor
			~screen();
			//a function called when getch gets key, return 0 when valid execution
			virtual int execute(int key);
			//print out all interface_elements
			virtual void print();
			void add_ie(interface_element*);
			void add_ie(string, interface_element*);
			void remove_ie(string);
		private:
			string handle;
			map<string,interface_element*> iemap;
			
	};
	int curses_init();
	int curses_wrapup();
    int ioloop();

}
#endif
