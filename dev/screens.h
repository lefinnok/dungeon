#ifndef _DGSCREENS_H_
#define _DGSCREENS_H_
#include <string>
#include <list>
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

	class dynamic_string_selector: public screen{
		public:
			dynamic_string_selector(std::string scr_handle, std::string, std::list<string> options, int, int, int, int);
			~dynamic_string_selector();
			//~dynamic_string_selector();
			int execute(int key);
			void optionsup();
			void optionsdown();
			void updatecursorloc();
			//void print();
		private:
			vector<string> option_ie_handles;
			string cursor_ie_handle;
			string down_ie_handle;
			string up_ie_handle;
			string modifdshandle;
			int sx;
			int sy;
			int maxoption;
			int option_code = 0;
	};
}
#endif
