#ifndef _DGIO_H_
#define _DGIO_H_
#include <string>
#include <vector>
#include <list>
#include "saveload.h"
//???
using namespace std;
namespace dg{
	extern const int MASKED_NOT;
	extern const int MASKED_UP;
	extern const int MASKED_DOWN;
	extern const int MASKED_LEFT;
	extern const int MASKED_RIGHT;
	extern const int MASKED_LEFTRIGHT;

	wstring towstring(string);
	string tostring(wstring);
	class mask{
		public:
			mask() = default;
			int minx=0;
			int miny=0;
			int maxx=999;
			int maxy=999;
	};

	//base sprite, not an interface element, but the storage of sprite characters
	class sprite{
		public:
			sprite(string,string);
			~sprite();
			vector<wstring>* getlines();
			void print(int,int);
		private:
			//int size_x,size_y;
			vector<wstring> lines;
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
			mask getmask();
			void setmask(int,int,int,int);
			void setmask(int,int,int,int,int);
			bool iscustommask();
			void setcustommask(bool);
			int ismasked(int relx, int rely);
			int getx();
			int gety();
			//int getvariant();
		protected:
			int x,y;
			int size_x;
			int size_y;
			string handle;
			bool functional;
			mask iemask;
			bool custommask = false;
			//int ievariant;
			
	};
	//an instance that references the sprite image which has its own coordinates
	class uisprite:public interface_element{
		public:
			uisprite(string,sprite*,int,int);
			void print();
			void print(int,int);
			sprite* getsprite();
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
			void add_non_visible_ie(interface_element*);
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
			map<string,interface_element*> getiemap();
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
			bool opaque = false;
			bool center = false;
			//bool bold;
			
	};
	int curses_init();
	int curses_wrapup();
    	int ioloop();
	void printat(wstring outstr, int x, int y, mask iemask);
	void printat(wstring outstr, int x, int y);
	void test_screen_size();
	class debugoverlay:public screen{
		public:
			debugoverlay();
			void print();
	};
}
#endif
