/* DATE: 2020-09-05
 * AUTHOR : JCY
 * DESCRIPTION: 验证几种线程的退出方式
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include <sys/types.h>  //进程头文件
 #include <unistd.h>     //进程头文件
 
 void *thread_fun(void *arg){
	 //如果传的参数是 1，那么就采用return方式退出
	 if(strcmp("1",(char *)arg) == 0){
		 printf("new thread return!\n");
		 return (void *)1;
	 }
	 //如果传的参数是 2，那么就采用pthread_exit方式退出
	 if(strcmp("2",(char *)arg) == 0){
		 printf("new thread pthread_exit!\n");
		 pthread_exit((void *)2);
	 }
	 //如果传的参数是 3，那么就采用exit方式退出
	 if(strcmp("3",(char *)arg) == 0){
		 printf("new thread exit!\n");
		 exit(3);
	 }
 }
 
 int main(int argc, char *argv[]){
	 int err;
	 pthread_t tid;
	 
	 err = pthread_create(&tid,NULL,thread_fun,(void *)argv[1]);
	 if(err != 0){
		 printf("create new thread failed!\n");
		 return 0;
	 }
	 
	 sleep(1);
	 printf("main thread\n");
	 return 0;
 }
 