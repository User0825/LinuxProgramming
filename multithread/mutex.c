/* AUTHOR: JCY
 * DATE: 2020-09-07.
 * DESCRIPTION: 多线程访问变量产生错误的例子
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include <sys/types.h>  //进程头文件
 #include <unistd.h>     //进程头文件
 
 struct student{
	 int id;
	 int age;
	 int name;
 }stu;
 
 int i;
 
 void *thread_fun1(void *arg){
	 while(1){
		 stu.id = i;
		 stu.age = i;
		 stu.name = i;
		 i++;
		 if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name){
			 printf("%d, %d, %d\n", stu.id, stu.age, stu.name);
			 break;
		 }
	 }
	 return (void *)0;
 }
 
 void *thread_fun2(void *arg){
	 while(1){
		 stu.id = i;
		 stu.age = i;
		 stu.name = i;
		 i++;
		 if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name){
			 printf("%d, %d, %d\n", stu.id, stu.age, stu.name);
			 break;
		 }
	 }
	 return (void *)0;
 }
 
 int main(){
	 pthread_t tid1, tid2;
	 int err;
	 
	 err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	 if(err != 0){
		 printf("create new thread 1 failed!\n);
		 return 0;
	 }
	 
	 err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	 if(err != 0){
		 printf("create new thread 2 failed!\n);
		 return 0;
	 }
	 
	 pthread_join(tid1, NULL);
	 pthread_join(tid2, NULL;
	 
	 return 0;
 }