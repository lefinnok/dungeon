#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
//#include "libs/llvm-15.0.2.src/BinaryFormat/ELF.h"
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
//Dynamic Function Load [Name]:
//https://stackoverflow.com/questions/25270275/get-functions-names-in-a-shared-library-programmatically


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
    /*
    static int callback(struct dl_phdr_info *info, size_t size, void *data)
    {
        // data is copy of 2nd arg in dl_iterate_phdr
        // you can use it for your lib name as I did
        const char * libname = (const char *)data;

        // if current elf's name contains your lib
        if (strstr(info->dlpi_name, libname))
        {

            printf("loaded %s from: %s\n", libname, info->dlpi_name);

            for (int j = 0; j < info->dlpi_phnum; j++)
            {
                // we need to save dyanmic section since it contains symbolic table
                if (info->dlpi_phdr[j].p_type == PT_DYNAMIC)
                {
                    Elf64_Sym * symtab = nullptr;
                    char * strtab = nullptr;
                    int symentries = 0;
                    auto dyn = (Elf64_Dyn *)(info->dlpi_addr + info->dlpi_phdr[j].p_vaddr);
                    for (int k = 0; k < info->dlpi_phdr[j].p_memsz / sizeof(Elf64_Dyn); ++k)
                    {
                        if (dyn[k].d_tag == DT_SYMTAB)
                        {
                            symtab = (Elf64_Sym *)dyn[k].d_un.d_ptr;
                        }
                        if (dyn[k].d_tag == DT_STRTAB)
                        {
                            strtab = (char*)dyn[k].d_un.d_ptr;
                        }
                        if (dyn[k].d_tag == DT_SYMENT)
                        {
                            symentries = dyn[k].d_un.d_val;
                        }
                    }
                    int size = strtab - (char *)symtab;
                    // for each string in table
                    for (int k = 0; k < size / symentries; ++k)
                    {
                        auto sym = &symtab[k];
                        auto str = &strtab[sym->st_name];
                        printf("%s\n", str);
                    }
                    break;
                }
            }
        }
        return 0;
    }
    */
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