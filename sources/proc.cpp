/**
 * @Author  JingleCath
 * @Date  2/25/23 - 4:17 PM
 * @Version 0.1
 * @Description .
*/

#include <unistd.h>
#include "include/proc.h"
#include <iostream>

/**
 * Get current and parent proc id <- task_struct in Linux.
 * @return 0
 */
int get_current_pid() {
    std::cout << "********************************" << std::endl;
    pid_t pid = getpid();               // Get current process id
    std::cout << "\tCurrent proc id: " << pid << std::endl;
    std::cout << "********************************" << std::endl;
    get_parent_pid();
    return 0;
}

/**
 * Get parent proc id <- pid(task_struct in Linux).
 * @return 0
 */
int get_parent_pid() {
    std::cout << "********************************" << std::endl;
    pid_t ppid = getppid();
    std::cout << "\tParent proc id: " << ppid << std::endl;
    std::cout << "********************************" << std::endl;
    return 0;
}

/**
 * fork() return two values:\n
 *      \t value > 0, run parent proc. There value1 is child pid\n
 *      \t value = 0, run child proc.\n
 *      \t value = -1, creating child proc failed.\n
 * @return 0 correct.\n
 *         -1 creating failed.
 */
int create_proc() {
    std::cout << "********************************" << std::endl;
    pid_t pid = fork();
    if (pid > 0) {
        // parent proc running -> there pid is the child proc id.
        // My parent proc should run following code.
        std::cout << "--------------------------" << std::endl;
        std::cout << "\tParent Proc" << std::endl;
        std::cout << "Current proc(by getpid): " << getpid() << std::endl;
        std::cout << "Child proc(by fork return): " << pid << "    " << std::endl;
        std::cout << "--------------------------" << std::endl;

    } else if (pid == 0) {
        // child proc running
        // My child proc should run following code.
        std::cout << "--------------------------" << std::endl;
        std::cout << "\tChild Proc" << std::endl;
        std::cout << "Parent proc: " << getppid() << std::endl;
        std::cout << "Current proc: " << getpid() << std::endl;
        std::cout << "--------------------------" << std::endl;
    } else {
        std::cerr << "Creating child proc failed." << std::endl;
        return -1;
    }

    // parent and child will both run the following code.
    for (int i = 0; i < 3; ++i) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    std::cout << "********************************" << std::endl;

    return 0;
}

/**
 * 递归创建子进程 子进程数： 2^n - 1, n最大为5
 * @return TODO count 子进程数量
 */
int loop_proc_recursion(int n) {
    int count = 0;
    if (n > 5) n = 5;
    // 循环创建子进程, 上界为3 则子进程数量为 2^3-1 = 8
    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();
        if (pid == 0)
            count++;
        std::cout << "pid - " << getpid() << std::endl;
    }
    // std::cout << "Total child proc: " << count;
    return count;
}

/**
 * 非递归创建子进程， n最大为5
 * @param n
 * @return TODO count 子进程数量
 */
int loop_proc_nore(int n) {
    int count = 0;
    if (n > 5) n = 5;
    // 循环创建子进程, 上界为n 则子进程数量为 n
    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            break;
        }
    }
    count++;
    std::cout << "pid - " << getpid() << std::endl;
    // std::cout << "Total child proc: " << count;
    return count;
}
/**
 *  需要通过现在运行的进程启动磁盘上的另一个可执行程序，也就是通过一个进程启动另一个进程，
 * 这种情况下我们可以使用exec族函数.exec族函数并没有创建新进程的能力，只是有大无畏的牺牲精神，
 * 让起启动的新进程寄生到自己虚拟地址空间之内，并挖空了自己的地址空间用户区，把新启动的进程数据填充进去。
 * @param path:  executable file path.
 * @return execute code.
 */
int execute(const char *path) {
    int pid = fork();
    if(pid < 0){
        std::cerr << "Creating proc failed.";
        return -1;
    } else if(pid == 0){
        // NULL 表示参数结束
        execl(path, "title", "aux", NULL);
        // 如果成功当前子进程的代码区别 ps中的代码区代码替换
        // 下面的所有代码都不会执行
        // 如果函数调用失败了,才会继续执行下面的代码
        perror("execl");
        printf("++++++++++++++++++++++++\n");
        printf("++++++++++++++++++++++++\n");
    } else if(pid > 0){
        std::cout << "Finished!" << std::endl;
    }
    // execl(path, "title", "aux");
    return 0;
}

/**
 * 孤儿进程
 */
void orphanProc(){
    // 创建子进程
    pid_t pid = fork();

    // 父进程
    if(pid > 0)
    {
        printf("我是父进程, pid=%d\n", getpid());
    }
    else if(pid == 0)
    {
        //TODO Clion 中子进程直接结束不托管
        sleep(1);	// 强迫子进程睡眠1s, 这个期间, 父进程退出, 当前进程变成了孤儿进程
        // 子进程
        printf("我是子进程, pid=%d, 父进程ID: %d\n", getpid(), getppid());
    } else if(pid == -1){
        std::cerr << "Creating proc failed.";
    }
}

