#ifndef _DGIO_H_
#define _DGIO_H_
#include <string>
#include <vector>
#include "saveload.h"
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
			virtual void print();
		private:
			int x,y;
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
			screen();
		private:

	};
    int ioloop();

}
#endif
