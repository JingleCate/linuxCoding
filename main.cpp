#include <iostream>
#include "sources/include/fd.h"
#include "sources/include/proc.h"



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
    orphanProc();
    return 0;
}
