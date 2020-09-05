/* AUTHOR: JCY
 * DATE: 2020-09-04.
 * getpid()				获取进程ID
 * pthread_ self()      获取线程ID
 * int pthread_create (pthread_ t * thread,
 *                     const pthread_ attr_t *attr,
 *                     void *(*start_ routine) (void *),
 *                     void *arg);
 * 第一个参数，新线程id,创建成功系统回填
 * 第二个参数，新线程到属性，NULL为默认属性
 * 第三个参数，新线程到启动函数 
 * 第四个参数，传递编新线程
 */

#include <stdio.h>
#include <stdlib. h>
#include <pthread.h>	//线程头文件
#include <sys/types.h>  //进程头文件
#include <unistd.h>     //进程头文件

void print_id(char *s){
     pid_t pid;
     pthread_t tid;
     
     pid = getpid();
     tid = pthread_self();
     
     printf("%s pid is %u, tid is %ld\n", s, pid, tid);
}

void *thread_fun(void *arg){
     print_id(arg);
     return (void *)0;
}

int main(void){
    pthread_t ntid;
    int err;

    err = pthread_create(&ntid,NULL,thread_fun,"new thread");
    if(err != 0){
	printf("create new thread failed!\n");
	return 0;
    }

    print_id("main thread : ");
    sleep(2);
    return 0;
}