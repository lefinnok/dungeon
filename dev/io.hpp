#ifndef _DGIO_H_
#define _DGIO_H_
#include <string>
#include <vector>
#include "saveload.hpp"
using namespace std;
namespace dg{
	class sprite{
		public:
			sprite(string,string);
			~sprite();
			vector<string>* getlines();
			void print(int,int);
		private:
			int size_x,size_y;
			vector<string> lines;
			string name;
	};
    int ioloop();

}
#endif
