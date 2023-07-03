#pragma once
#include <memory>
#include "message.h"
#include <mutex>
#include <optional>
#include <queue>

template <class T>
class Queue_Manager
{
	std::queue<T> message_queue;
	std::condition_variable condition;
	std::mutex mutex;
public:
	Queue_Manager(){}

	void push(T element)
	{
		std::unique_lock<std::mutex> lock(mutex);
		message_queue.push(element);
		condition.notify_one();
	}

	T stop_until_pop()
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (message_queue.size() == 0)
			condition.wait(lock, [this]() {return message_queue.size() != 0; });
		T element = message_queue.front();
		message_queue.pop();
		return element;
	}


	std::optional<T> pop()
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (message_queue.size() > 0) {
			T element = message_queue.front();
			message_queue.pop();
			return element;
		}
		return std::nullopt;
	}

	size_t size()
	{
		std::unique_lock<std::mutex> lock(mutex);
		size_t size = message_queue.size();
		return size;
	}

};

