#ifndef _DGSCREENS_H_
#define _DGSCREENS_H_
#include <string>
#include <list>
#include "mob.h"
#include "io.h"
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
    void advanceround();
	class play_screen: public screen{
		public:
			play_screen(std::string);
            ~play_screen();
			int execute(int key);
			void updateuielements();
			void print();
            //void advanceround();
			//void setplayer(mob* player);
		private:
			string player_handle;
			string status_string_handle;
            //list<mob*> enemies;
	};
    
    class use_menu: public screen{
        public:
            ~use_menu();
            use_menu(std::string,string player_handle);
            int execute(int key);
        private:
            string player_handle;
            string selector_handle;
            map<int,string> optioncodetoinventoryhandle;
    };
    class inventory_menu: public screen{
        public:
            ~inventory_menu();
            inventory_menu(std::string,string player_handle);
            int execute(int key);
            void updateuielements();
            void print();
        private:
            string player_handle;
            map<string, item*>* player_inventory;
            string inventory_selector_handle;
            string equipment_selector_handle;
            string equip_ds_handle;
            string unequip_ds_handle;
            bool selector_code = 0;
    };

	class pause_menu: public screen{
		public:
			//~pause_menu();
			pause_menu(std::string);
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
			dynamic_string_selector(std::string scr_handle, std::string, std::list<string> options, int xl, int yl, int size_x, int size_y);
			~dynamic_string_selector();
			//~dynamic_string_selector();
			int execute(int key);
			void optionsup();
			void optionsdown();
			void updatecursorloc();
            int option_code = 0;
            int maxoption;
            bool empty = false;
            void setoptions(list<string> options);
            string getmodifdshandle();
            string getcurrentoptionstring();
			//void print();
		private:
			vector<string> option_ie_handles;
			string cursor_ie_handle;
			string down_ie_handle;
			string up_ie_handle;
			string modifdshandle;
			int sx;
			int sy;
			//int maxoption;
			//int option_code = 0;
	};
    void cleanMOBDB();
    
}
#endif
