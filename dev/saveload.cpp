#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <algorithm>
#include "libs/pugixml-1.13/src/pugixml.hpp"
using namespace pugi;
using namespace std;
//references:
//https://linuxhint.com/parse_xml_in_cpp/
//https://www.tutorialspoint.com/find-out-the-current-working-directory-in-c-cplusplus
//https://blog.csdn.net/wteruiycbqqvwt/article/details/112664432
//https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from


int get_current_dir(char pBuf[FILENAME_MAX]) {
    int n;
    #ifdef WINDOWS
    n = GetModuleFileName(NULL, pBuf, FILENAME_MAX);
    #else
    n = readlink("/proc/self/exe", pBuf, FILENAME_MAX);
    #endif
    if(n>0&&n<FILENAME_MAX){
        cout<<pBuf<<endl;
        return 0;
    }
    return 1;
}


namespace dg{
    
    int loadEvents(){
        xml_document eventDB;
        char pBuf[FILENAME_MAX];
        if(get_current_dir(pBuf)){
            cout<<"Unable to get executable directory, load unsuccessful. [are you using mac :3]"<<endl;
            return 1; 
        }
        

        if (!eventDB.load_file("data/events.xml")){
            cout<<"EVENT FILE MISSING, events.xml not found"<<endl;
            return 1;
        }
        return 0;
    }
    int loadInit(){
        if(loadEvents()){

        }
        return 0;
    }
}