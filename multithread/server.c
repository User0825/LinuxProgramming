/*DATA : 2020-09-09
 * AUTHOR:
 * DESCRIPTION : 多线程TCP服务器
 * 1、int socket( int domain, int type, int protocol);
 * 2、int bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * 3、int listen(int sockfd, int backlog);
 * 4、int accept( int sockfd, struct sockaddr *addr, socklen_ t * addrlen);
 * 5、read、write
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#icnlude <errno.h>

#define MAX_LISTEN 10

char buf[100];
struct sockaddr_in server_ip, remote_ip;
int ad[MAX_LISTEN];

void *thread_fun(void *arg){
	while(1){
		printf("read data from client : %s\n", inet_ntoa(remote_ip.sin_addr.s_addr));
		read(ad[(int)arg], buf, 100);
		printf("buf is %s.\n", buf);
	}
	return NULL;
}

int main(){
	int server_len, remote_len;
	
	int err, sd;
	pthread_t tid[MAX_LISTEN];
	int i = 0;
	
	// 创建socket
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd == -1){
		prinf("create socket failed, errno is %d\n", errno);
		return -1;
	}
	
	// 设置ip地址和端口
	server_ip.sin_family = AF_INET;
	server_ip.sin_port = htons(5678);
	server_ip.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(server_ip.sin_zero, 0, 8);
	
	// 绑定ip地址和端口到socke
	err = bind(sd, (struct sockaddr *)(&server_ip), sizeof(struct sockaddr));
	if(err == -1){
		printf("bind error. errno is %d.\n", errno);
		close(sd);
		return -1;
	}
	
	// 设置服务器的最大连接数
	err = listen(sd, MAX_LISTEN);
	if(err == -1){
		printf("listen error. errno is %d.\n", errno);
		close(sd);
		return -1;
	}
	
	// 获取客户端的ip地址的长度
	remote_len = sizeof(struct sockaddr);
	
	// 利用while循环 确保不停的有客户端可以连接到服务器
	while(1){
		// 等待客户端的请求，如果请求来到 返回一个新的socket
		// 服务器和客户端利用新的socket来通信
		ad[i] = accept(sd, (struct sockaddr *)(&remote_ip), &remote_len);
		if(ad[i] == -1){
			printf("accept error, errno is 5d.\n", errno);
			close(sd);
			return -1;
		}
		
		// 抛出一个新的线程 新线程使用while循环 确保不停交换数据
		err = pthread_create(&tid[i], NULL, thread_fun, (void *) i)
		if(err != 0){
			printf("create new thread failed\n");
			close(ad[i]);
		}
		i++;
		read(ad[i], buf, 100);
		printf("buf is %s.\n", buf);
	
		close(ad[i]);
	}
	
	close(sd);
	
	return 0;
}