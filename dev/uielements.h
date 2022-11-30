#ifndef _DGUIELEMENTS_H_           
#define _DGUIELEMENTS_H_           
#include <string>
#include <any>
using namespace dg;             
namespace dg{                   
	class uitext:public interface_element{   
        	public:                 
            		uitext(string text, string handle, int xl,int yl);
			void print(int xl, int yl);
		private:
			string text;
   	};
	void dynoval_wrap();
	//omg this is gold, reference: https://stackoverflow.com/questions/2919584/override-number-of-parameters-of-pure-virtual-functions [ended up not using]
	//ok, this is bad, i know, alot of void pointers, im sorry to whoever is reading this and cringing their guts out
	//actually, I am going to use any :3
	class dynamicvalue{
		public:
			virtual ~dynamicvalue();
			void set(any);
			any get();
			virtual string getstring() = 0;
			string gethandle();
		protected:
			string handle;
			any value;
	};
	class dynamicint:public dynamicvalue{
		public:
			dynamicint(string handle, int);
			string getstring();
			int getint();
	};
	class dynamicstring:public dynamicvalue{
		public:
			dynamicstring(string handle, string);
			string getstring();
	};
	class dynamictext: public interface_element{
		public:
			dynamictext(string dynamicval_handle, string ie_handle, int xl, int yl);
			~dynamictext();
			void print(int xl, int yl);
			void setnotdestroy();
		protected:
			string dynamicval_handle;
			bool destroy_on_deconstruct=true;
			//int ievariant = 1;
	};
	class uibackground:public interface_element{
		public:
			uibackground(int size_x, int size_y, string handle, int xl, int yl);
			void print(int xl, int yl);
		protected:
			int size_x, size_y;
	};
	class uibox:public uibackground{
		public:
			using uibackground::uibackground;
			void print(int xl, int yl);
	};
}                               
#endif  
