/* AUTHOR: JCY
 * DATE: 2020-09-07.
 * DESCRIPTION: 多线程加锁访问变量的例子
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
 
 //定义全局变量 两个线程都需要访问
 int i;
 pthread_mutex_t mutex;
 
 void *thread_fun1(void *arg){
	 while(1){
		 // 加锁 对整个结构体访问进行加锁,防止产生错乱
		 pthread_mutex_lock(&mutex);
		 stu.id = i;
		 stu.age = i;
		 stu.name = i;
		 i++;
		 if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name){
			 printf("%d, %d, %d\n", stu.id, stu.age, stu.name);
			 break;
		 }
		 // 访问变量完成,需要进行解锁,只有这样才能访问
		 pthread_mutex_unlock(&mutex);
	 }
	 return (void *)0;
 }
 
 void *thread_fun2(void *arg){
	 while(1){
		 // 加锁 对整个结构体访问进行加锁,防止产生错乱
		 pthread_mutex_lock(&mutex);
		 stu.id = i;
		 stu.age = i;
		 stu.name = i;
		 i++;
		 if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name){
			 printf("%d, %d, %d\n", stu.id, stu.age, stu.name);
			 break;
		 }
		 // 访问变量完成,需要进行解锁,只有这样才能访问
		 pthread_mutex_unlock(&mutex);
	 }
	 return (void *)0;
 }
 
 int main(){
	 pthread_t tid1, tid2;
	 int err;
	 
	 // 对互斥量进行初始化 只有初始化过的互斥量才能使用
	 err = pthread_mutex_init(&mutex, NULL);
	 if(err != 0){
		 printf("init mutex failed.\n");
		 return 0;
	 }
	 
	 // 创造新线程
	 err = pthread_create(&tid1, NULL, thread_fun1, NULL);
	 if(err != 0){
		 printf("create new thread 1 failed!\n");
		 return 0;
	 }
	 
	 // 创造新线程
	 err = pthread_create(&tid2, NULL, thread_fun2, NULL);
	 if(err != 0){
		 printf("create new thread 2 failed!\n");
		 return 0;
	 }
	 
	 // 等待新线程运行结束
	 pthread_join(tid1, NULL);
	 pthread_join(tid2, NULL);
	 
	 return 0;
 }