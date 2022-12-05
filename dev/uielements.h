#ifndef _DGUIELEMENTS_H_           
#define _DGUIELEMENTS_H_           
#include <string>
#include <any>
#include "io.h"
#include "mob.h"
using namespace dg;
using namespace std;
namespace dg{                   
	class uitext:public interface_element{   
        	public:                 
            		uitext(wstring text, string handle, int xl,int yl);
			void print(int xl, int yl);
			wstring getstring();
			void setstring(wstring);
			void updatesizex();
		private:
			wstring text;
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
    class statblock:public interface_element{
        public:
            //~statblock();
            statblock(mob* target_mob, string handle, int xl, int yl);
            void print(int xl, int yl);
            void setmob(mob* mb);
        private:
            
            mob* target_mob;
    };
    class playlog: public interface_element{
        public:
            playlog(int size_x, int size_y, string handle,int xl, int yl);
            void print(int xl, int yl);
    };
	class uiboxVseperator: public interface_element{
		public:
			uiboxVseperator(int size_y,string handle, int xl, int yl);
			void print(int xl, int yl);
		/*protected:
			int size_y;*/
	};

	class uiboxHseperator: public interface_element{
		public:
			uiboxHseperator(int size_x,string handle, int xl, int yl);
			void print(int xl, int yl);
		/*protected:
			int size_x;*/
	};
	class uiprogressbar: public interface_element{
		public:
			uiprogressbar(int size_x, int val, int max, string handle, int xl, int yl);
			void print(int xl, int yl);
			void updateval(int);
			void updatemax(int);
		protected:
			//int size_y;
			int value, maximum;
	};

	class uiprogressbar2: public uiprogressbar{
		public:
            using uiprogressbar::uiprogressbar;
			void print(int xl, int yl);
	};
}                               
#endif  
