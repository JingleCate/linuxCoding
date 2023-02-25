/**
 * @Author  JingleCath
 * @Date  2/25/23 - 1:08 PM
 * @Version 0.1
 * @Description ...
*/

#include "fd.h"
#include <iostream>
#include "fcntl.h"
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <dirent.h>

// 路径最大长度
#define PATH_SIZE 255
// 测试目录路径
#define TEST_DIR_PATH "/home/master/Desktop/Projects/Temp"

/*
 * Test linux file descriptor, including method "open", "dup", "write", "close".
 */
void fdTest1() {
    // std::cout << "Hello, World!" << std::endl;
    // char path[PATH_SIZE];
    // getcwd(path, PATH_SIZE);
    // std::clog << "path:" << *path <<std::endl;

    // char *_workspace;
    // getcwd(_workspace, PATH_SIZE);
    // _workspace = get_current_dir_name();
    // std::cout << "path:" << _workspace <<std::endl;
    const char *_workspace = "/home/master/ProgramFiles/ClionProjects/BaseTest/";

    std::cout << "Current work directory: " << _workspace << std::endl;
    std::cout << "=====================================" << std::endl;
    // 创建新文件, 文件权限 -rw-rw-r-- 0664 八进制
    char f1[PATH_SIZE];
    strcpy(f1, _workspace);
    int fd0 = open(strcat(f1, "textFiles/fdor1.txt"), O_RDWR | O_CREAT, 0664);
    if (fd0 == -1) {
        std::cerr << errno << std::endl;
        if (errno == EEXIST) {
            std::cerr << "EEXIST 参数pathname 所指的文件已存在, 却使用了O_CREAT 和O_EXCL 旗标. \r\n" << std::endl;

        } else if (errno == EACCES) {
            std::cerr << "EACCESS 参数pathname 所指的文件不符合所要求测试的权限.\r\n" << std::endl;

        } else if (errno == EROFS) {
            std::cerr << "EROFS 欲测试写入权限的文件存在于只读文件系统内.\r\n" << std::endl;
        } else if (errno == ENOENT) {
            std::cerr << "文件不存在" << std::endl;
        }
        std::cerr << "1 :=> Creating file failed. " << std::endl;
        exit(0);
    }
    std::cout << "File description flag: " << fd0 << std::endl;

    // 写入数据
    const char *_wtext = "\n \nHello, I have nothing to do. Can you help me? \n";
    // 成功写入后文件指针在尾部
    write(fd0, f1, strlen(f1));
    write(fd0, _wtext, strlen(_wtext));


    std::cout << "=====================================" << std::endl;
    // 创建第二个文件
    // int fd1 = open("./textFiles/fdor1.txt", O_RDWR|O_CREAT, 0664);
    // if (fd1 == -1) {
    //     std::cerr << "2 :=> Creating file failed. ";
    //     exit(0);
    // }
    // 复制文件描述符
    int newfd = dup(fd0);
    std::cout << "File description flag: " << newfd << std::endl;

    // 关闭
    close(fd0);
    const char *_nwtext = "（（（ 千帆竞过，万木逢春。 ））））";
    write(newfd, _nwtext, strlen(_nwtext));
    close(newfd);

    // TODO dup2 and fcntl
}

/*
 * Dir 3 methods: opendir(), readdir(), closedir(); 非递归
 * 如果需要递归则可
 * // 打开目录
 * DIR *opendir(const char *name);
 * 参数: name -> 要打开的目录的名字
 * 返回值: DIR*, 结构体类型指针。打开成功返回目录的实例，打开失败返回 NULL
 *
 * struct dirent *readdir(DIR *dirp);
 * 参数：dirp -> opendir () 函数的返回值
 * 返回值：函数调用成功，返回读到的文件的信息，目录文件被读完了或者函数调用失败返回 NULL
 *
 * // 关闭目录, 参数是 opendir() 的返回值
 * int closedir(DIR *dirp);
 * 参数：dirp-> opendir () 函数的返回值
 * 返回值：目录关闭成功返回 0, 失败返回 -1
 */
void dirTest() {
    std::cout << "*****************************************************" << std::endl;
    DIR *dirp = opendir(TEST_DIR_PATH);
    if (dirp == NULL) {
        std::cerr << "Open dest dir failed. Exit with code 0." << std::endl;
        exit(0);
    }

    std::cout << "Dir point: " << dirp << std::endl;

    // 变粒dest目录
    int count = 0;
    while (true) {
        dirent *ptr = readdir(dirp);
        if (ptr == NULL) {
            std::cout << "Reading dest dir finished." << std::endl;
            break;
        }
        if (strcmp(ptr->d_name, ".") == 0 ||
            strcmp(ptr->d_name, "..") == 0) {
            continue;
        }
        /*
         * 文件的类型, linux中有7中文件类型
         * DT_BLK：块设备文件
         * DT_CHR：字符设备文件
         * DT_DIR：目录文件
         * DT_FIFO ：管道文件
         * DT_LNK：软连接文件
         * DT_REG ：普通文件
         * DT_SOCK：本地套接字文件
         * DT_UNKNOWN：无法识别的文件类型
         */
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Name: " << ptr->d_name << "    ";
        std::cout << "Inode: " << ptr->d_ino << std::endl;
        std::cout << "Length: " << ptr->d_reclen << "    ";
        if (ptr->d_type == DT_DIR)
            // 目录文件
            std::cout << "Type: " << "Directory" << std::endl;
        else if (ptr->d_type == DT_REG)
            // 普通文件
            std::cout << "Type: " << "Regular file" << std::endl;
        else if (ptr->d_type == DT_UNKNOWN)
            std::cout << "Type: " << "Unknown file type" << std::endl;

        std::cout << "----------------------------------" << std::endl;
        count++;
    }
    std::cout << "Total: " << count << std::endl;

    std::cout << "*****************************************************" << std::endl;
}