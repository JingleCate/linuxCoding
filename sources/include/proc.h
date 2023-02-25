/**
 * @Author  JingleCath
 * @Date  2/25/23 - 4:17 PM
 * @Version 0.1
 * @Description ...
*/


#ifndef BASETEST_PROC_H
#define BASETEST_PROC_H

int get_current_pid();
int get_parent_pid();
int create_proc();
int loop_proc_recursion(int n);
int loop_proc_nore(int n);
int execute(const char *path);
void orphanProc();

#endif //BASETEST_PROC_H