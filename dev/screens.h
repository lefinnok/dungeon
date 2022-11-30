#ifndef _DGSCREENS_H_
#define _DGSCREENS_H_
#include <string>
using namespace dg;
namespace dg{
	class titlescreen:public screen{
		public:
			titlescreen(std::string);
			int execute(int key);
	};
	class character_creation:public screen{
		public:
			character_creation(std::string);
			int execute(int key);
	};

	class dynamic_string_mod:public screen{
		public:
			dynamic_string_mod(std::string scr_handle, std::string, int, int, int, int);
			~dynamic_string_mod();
			int execute(int key);
		private:
			string modifdshandle;
			string localdshandle;	
	};
}
#endif
