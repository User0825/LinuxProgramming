#include <iostream>
#include <deque>
#include <thread>
#include <mutex>

std::deque<int> q;
std::mutex mu;

void producer() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		count--;
	}
}

void consumer() {
	int data = 0;
	while (data != 1) {
		std::unique_lock<std::mutex> locker(mu);
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			std::cout << "t2 got a value from t1: " << data << std::endl;
		}
		else {
			locker.unlock();
		}
	}
}
int main() {
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();

	system("pause");
	return 0;
}
