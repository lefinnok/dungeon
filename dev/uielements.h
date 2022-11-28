#ifndef _DGUIELEMENTS_H_           
#define _DGUIELEMENTS_H_           
#include <string>
using namespace dg;             
namespace dg{                   
    class uitext:public interface_element{   
        public:                 
            uitext(string text, string handle, int xl,int yl);
			void print(int xl, int yl);
		private:
			string text;
    };                          
}                               
#endif  
