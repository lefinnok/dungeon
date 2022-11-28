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
			interface_element(string,int,int);
			~interface_element();
			virtual void print();
			//print relative to this coordniate
			virtual void print(int x, int y);
			bool getfunctional();
			void setfunctional(bool);
			string get_handle();
			void move(int,int);
			void setloc(int,int);
		protected:
			int x,y;
			string handle;
			bool functional;
	};
	//an instance that references the sprite image which has its own coordinates
	class uisprite:public interface_element{
		public:
			uisprite(string,sprite*,int,int);
			void print();
			void print(int,int);
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
			bool getcontrollable();
			void setcontrollable(bool);
			void move_ie(string, int, int);
			void move(int,int);
			void setloc(int,int);
		private:
			//if the screen is currently (or entirely) controllable, if not, the screen plays automatically, enabling animations and such
			bool controllable;
			//screen coordinates
			int x, y;
			string handle;
			map<string,interface_element*> iemap;
			list<string> iestack;
			
	};
	int curses_init();
	int curses_wrapup();
    int ioloop();
	void printat(const char* c_str, int x, int y);
}
#endif
