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
		//unique_lock�� condition_variableֻ���ܸ����͵���
		unique_lock<mutex> locker(mtx);	// ����
		products.push(i + 1);				// ���²�Ʒ����
		locker.unlock();					// ����
		condVar.notify_one();				// ���ѵȴ��߳�
		std::this_thread::sleep_for(std::chrono::seconds(4));
	}
}

void consumer(){
	for (int i = 0; i < PRODUCTNUM; i++){
		unique_lock<mutex> locker(mtx);
		//lamda ���ʽ ������ע����ͬ
		//wait(locker, predicate) predicateΪfalseʱ �߳��������ȴ�����
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