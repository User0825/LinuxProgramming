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
#include <string.h>
#include <stdlib. h>
#include <pthread.h>	//线程头文件
#include <sys/types.h>  //进程头文件
#include <unistd.h>     //进程头文件

struct student{
	int age;
	char name[20];
};

void *thread_fun(void *stu){
	//sleep(1); //若主线程不调用pthread_exit()函数退出，新线程不能打印就直接退出
	printf("student age is %d, name is %s\n", ((struct student*)stu)->age, ((struct student*)stu)->name);
}

int main(int argc, char *argv[]){
	pthread_t tid;
	int err;
	//int *rval;
	
	struct student stu;
	stu.age = 20;
	memcpy(stu.name,"zhangsan",20);
	err = pthread_create(&tid,NULL,thread_fun,(void *)(&stu));
	if(err != 0){
		printf("creat new thread failed!\n");
		return 0;
	}
	int i;
	printf("main thread have %d args\n", argc);
	for(i = 0;i < argc;i++){
		printf("main thread args is %s\n", argv[i]);
	}
	//pthread_exit(rval); //主线程退出，不影响创建的线程继续运行
	
	sleep(1);
	return 0;
}