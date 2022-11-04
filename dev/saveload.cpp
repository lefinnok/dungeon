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
    int len;
    #ifdef WINDOWS
    len = GetModuleFileName(NULL, pBuf, FILENAME_MAX);
    #else
    len = readlink("/proc/self/exe", pBuf, FILENAME_MAX);
    #endif
    if(len>0&&len<FILENAME_MAX){
        //cout<<pBuf<<endl;
        return len;
    }
    return 0;
}


namespace dg{
    
    int loadEvents(){
        xml_document eventDB;
        char pBuf[FILENAME_MAX];
        int filelen = get_current_dir(pBuf);
        if(!filelen){
            cout<<"Unable to get executable directory, load unsuccessful. [are you using mac :3]"<<endl;
            return 1; 
        }
        string path = string(pBuf,filelen);
        string ppath = path.substr(0,path.find_last_of("\\/")) + "/data/events.xml";
        wstring widestr = std::wstring(ppath.begin(), ppath.end());
        const wchar_t* widecstrpath = widestr.c_str();
        //cout<<ppath<<endl;

        if (!eventDB.load_file(widecstrpath)){
            cout<<"EVENT FILE MISSING, events.xml not found"<<endl;
            return 1;
        }

        xml_node events = eventDB.child("EventDef");
        for (xml_node_iterator it = events.begin(); it != events.end(); ++it)
        {
            cout << "Event:" << it->attribute("Name").value();


            for (xml_node_iterator cit = it->begin(); cit != it->end(); ++cit){
                cout << endl << '\t' << cit->name() << ": " << cit->text().get();
            }

            cout << endl;
        }

        cout << endl;
        return 0;
    }
    int loadInit(){
        if(loadEvents()){

        }
        return 0;
    }
}