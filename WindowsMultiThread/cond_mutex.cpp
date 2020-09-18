#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
using std::cout;
using std::endl;
using std::mutex;
using std::condition_variable;
using std::queue;
using std::unique_lock;
using std::thread;
using std::this_thread;

#define PRODUCTNUM 10

mutex mtx;
condition_variable condVar;
queue<int> products;

void producer(){
	for (int i = 0; i < PRODUCTNUM; i++){
		//unique_lock锁 condition_variable只接受该类型的锁
		unique_lock<mutex> locker(mtx);	// 加锁
		products.push(i + 1);				// 更新产品队列
		locker.unlock();					// 解锁
		condVar.notify_one();				// 唤醒等待线程
		std::this_thread::sleep_for(std::chrono::seconds(4));
	}
}

void consumer(){
	for (int i = 0; i < PRODUCTNUM; i++){
		unique_lock<mutex> locker(mtx);
		//lamda 表达式 含义与注释相同
		//wait(locker, predicate) predicate为false时 线程阻塞，等待唤醒
		condVar.wait(locker, [](){return products.size(); });
		/*while (products.empty())
			condVar.wait(locker); // Unlock mu and wait to be notified*/
		cout << "Get Product " << products.front() << " From Products." 
			<< "\t Products Size : "<< products.size() << endl;
		products.pop();
		locker.unlock();
	}
}

int main(){

	thread producerThread(producer);
	thread consumerThread(consumer);

	producerThread.join();
	consumerThread.join();

	system("pause");
	return 0;
}