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
 
 void *thread_func1(void *arg){
	 printf("thread 1\n");
	 return (void *)1;
 }
 
 void *thread_func2(void *arg){
	 printf("thread 2\n");
	 pthread_detach(pthread_self());
	 pthread_exit((void *)2);
 }
 
 int main(){
	 int err1,err2;
	 pthread_t tid1, tid2;
	 void *rval1, *rval2;
	 
	 err1 = pthread_create(&tid1, NULL, thread_func1, NULL);
	 err2 = pthread_create(&tid2, NULL, thread_func2, NULL);
	 
	 if(err1 || err2){
		 printf("create new thread failed.\n");
		 return 0;
	 }
	 
	 printf("main thread.\n");
	 printf("join1 rval is %d.\n",pthread_join(tid1, &rval1));
	 printf("join2 rval is %d.\n",pthread_join(tid2, &rval2));
	 
	 printf("thread1 exit code is %d.\n", (int *)rval1);
	 printf("thread2 exit code is %d.\n", (int *)rval2);
	 printf("main thread.\n");
	 
	 return 0;
	 
 }