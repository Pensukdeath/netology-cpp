#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

/*
Потокобезопасная очередь
*/

template<class T>
class Safe_Queue 
{
private:
	std::queue<T> works;
	std::mutex mutex;
	std::condition_variable cond_var;
public:
	void push(T work) 
	{
		std::unique_lock<std::mutex> lockMutex(mutex);
		works.push(work);
	};
	T pop() 
	{
		std::unique_lock<std::mutex> lockMutex(mutex);
		cond_var.wait(lockMutex, [this]() { return !works.empty(); });
		T work = std::move(works.front());
		works.pop();
		return work;
	};
	bool empty() 
	{
		std::unique_lock<std::mutex> lock(mutex);
		return works.empty();
	};
	int getSize()
	{
		std::unique_lock<std::mutex> lock(mutex);
		return works.size();
	}


};