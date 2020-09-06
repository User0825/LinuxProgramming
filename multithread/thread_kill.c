 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include <sys/types.h>  //进程头文件
 #include <unistd.h>     //进程头文件
 #include <signal.h>     //包含SIGQUIT定义
 #include <errno.h>		 //错误码头文件 包含ESRCH定义
 
 void *thread_fun(void *arg){
	 sleep(1);
	 printf("new thread.\n");
	 return (void *)0;
 }
 
 int main(){
	 pthread_t tid;
	 int err, s;
	 void *rval;
	 err = pthread_create(&tid,NULL,thread_fun,NULL);
	 if(err != 0){
		 printf("create new thread failed.\n");
		 return;
	 }
	 
	 //sleep(1);
	 
	 //s = pthread_kill(tid, 0);
	 s = pthread_kill(tid, SIGQUIT);
	 if(s == ESRCH){
		 printf("thread tid is not found.\n");
	 }
	 pthread_join(tid, &rval);
	 printf("main thread.\n");
	 return 0;
 }