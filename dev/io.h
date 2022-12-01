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
			virtual ~interface_element();
			virtual void print();
			//print relative to this coordniate
			//input is the x and y coordinate of the element
			//output is the element
			virtual void print(int x, int y);
			bool getfunctional();
			void setfunctional(bool);
			string get_handle();
			void move(int,int);
			void setloc(int,int);
			void addattr(int);
			void rmvattr(int);
			list<int> attrs;
			//int getvariant();
		protected:
			int x,y;
			string handle;
			bool functional;
			//int ievariant;
			
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
			//get the value of controllable from protected member controllable
			bool getcontrollable();
			//set the controllable's value
			void setcontrollable(bool);
			void move_ie(string, int, int);
			//move the screen by x and y coordinate inputted
			void move(int,int);
			void setloc(int,int);
			void destruct();
			// set the screen to center
			void setcenter(bool);
			bool iscenter();
			string gethandle();
		protected:
			//if the screen is currently (or entirely) controllable, if not, the screen plays automatically, enabling animations and such
			//at default it is set to be true
			bool controllable = true;
			//screen coordinates
			int x = 0;
			int y = 0;
			string handle;
			map<string,interface_element*> iemap;
			list<string> iestack;
			bool opaque;
			bool center = false;
			//bool bold;
			
	};
	int curses_init();
	int curses_wrapup();
    int ioloop();
	void printat(const char* c_str, int x, int y);
}
#endif
