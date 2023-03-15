#pragma once
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue : public std::enable_shared_from_this <ThreadSafeQueue<T>>
{
private:
	std::mutex queue_mutex;
	std::queue<T> safe_queue;
public:
	ThreadSafeQueue<T>()
	{

	}

	~ThreadSafeQueue<T>()
	{

	}

	std::queue<T>& operator=(const std::queue<T>& other)
	{
		std::scoped_lock lock(queue_mutex);
		safe_queue = other;
	}

	std::queue<T>& operator=(const std::queue<T>&& other)
	{
		std::scoped_lock lock(queue_mutex);
		safe_queue = other;
	}

	void push(const T element)
	{
		std::scoped_lock lock(queue_mutex);
		safe_queue.push(element);
	}

	void pop()
	{
		std::scoped_lock lock(queue_mutex);
		safe_queue.pop();
	}

	T& front()
	{
		std::scoped_lock lock(queue_mutex);
		return safe_queue.front();
	}

	T& back()
	{
		std::scoped_lock lock(queue_mutex);
		return safe_queue.back();
	}

	bool empty()
	{
		std::scoped_lock lock(queue_mutex);
		return safe_queue.empty();
	}

	size_t size()
	{
		std::scoped_lock lock(queue_mutex);
		return safe_queue.size();
	}
};

