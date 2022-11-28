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
}
#endif
