/* AUTHOR: JCY
 * DATE: 2020-09-07.
 * DESCRIPTION:_验证可以有多个线程同时拥有读模式下到读写锁
 *
 * 读写锁在使用之前必须初始化
 * int pthread_rwlock_init( pthread_rwlock_t *restrict rwlock,
 *                          const pthread_rwlockattr_t *restrict attr);
 * 成功返回0，失败返回错误码
 *
 * 使用完需要销毁
 * int pthread_rwlock_destroy( pthread_rwlock_t *rwlock); 
 * 成功返回0，失败返回错误码
 *
 * 读模式加锁
 * int pthread_rwlock_rdlock( pthread_rwlock_t *rwlock); .
 * int pthread_rwlock_tryrdlock( pthread_rwlock_t *rwlock);
 *
 * 写模式加锁
 * int pthread_rwlock_wrlock( pthread_rwlock_t *rwlock);
 * int pthread_rwlock_trywrlock( pthread_rwlock_t *rwlock);
 *
 * 解锁
 * int pthread_rwlock_unlock( pthread_rwlock_t *rwlock);
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 #include <sys/types.h>  //进程头文件
 #include <unistd.h>     //进程头文件
 
 //定义全局变量 两个线程都需要访问
 int num = 0;
 pthread_rwlock_t rwlock;
 
 void *thread_fun1(void *arg){
	 int err;
	 
	 //pthread_rwlock_rdlock(&rwlock);
	 pthread_rwlock_wrlock(&rwlock);
	 printf("thread 1 print num %d.\n", num);
	 sleep(5);
	 printf("thread 1 over.\n");
	 
	 pthread_rwlock_unlock(&rwlock);
	 
	 return (void *)1;
 }
 
 void *thread_fun2(void *arg){
	 int err;
	 
	 //pthread_rwlock_rdlock(&rwlock);
	 pthread_rwlock_wrlock(&rwlock);
	 printf("thread 2 print num %d.\n", num);
	 sleep(5);
	 printf("thread 2 over.\n");
	 
	 pthread_rwlock_unlock(&rwlock);
	 
	 return (void *)1;
 }
 
 int main(){
	 pthread_t tid1, tid2;
	 int err;
	 
	 // 对互斥量进行初始化 只有初始化过的互斥量才能使用
	 err = pthread_rwlock_init(&rwlock, NULL);
	 if(err != 0){
		 printf("init rwlock failed.\n");
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
	 
	 pthread_rwlock_destroy(&rwlock);
	 
	 return 0;
 }
 