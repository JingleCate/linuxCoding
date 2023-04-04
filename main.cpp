#include <iostream>
#include "sources/include/fd.h"
#include "sources/include/proc.h"
#include "sources/include/socket.h"

#include "sources/include/slc.h"



/**
 * Test main method.
 * @param argc
 * @param args
 * @return
 */
int main(int argc, char *args[]) {
    // fdTest1();
    // dirTest();
    // get_current_pid();
    // create_proc();

    // int count = loop_proc_nore(3);
    // std::cout << count;

    // execute("/bin/ps");
    // orphanProc();
    // server();
    // client();
    // pipeProc();
    str s;
    std::string str;
    std::cout << "Please input str: ";
    std::cin >> str;
    initStr(s, str);
    int *next = getNextArray(s);
    printStr(s, std::string("Template str"));
    for(int i = 1; i <= s.length; i++)
        std::cout << "n[" << i << "]\t";
    std::cout << std::endl;
    for(int i = 1; i < s.length; i++)
        std::cout << "-------|";
    std::cout << "------\n";
    for(int i = 1; i <= s.length; i++)
        std::cout << "  " << next[i] << "\t";
    std::cout << std::endl;

    return 0;
}
