#pragma once
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue : public std::enable_shared_from_this <ThreadSafeQueue<T>>
{
private:
	std::mutex queue_mutex;
	std::queue<T> safe_queue;
	std::unique_lock<std::mutex> ulock;
	std::condition_variable pop_condition;
public:
	ThreadSafeQueue<T>()
	{
		ulock = std::move(std::unique_lock<std::mutex>(queue_mutex));
		ulock.unlock();
	}

	~ThreadSafeQueue<T>()
	{

	}


	ThreadSafeQueue(const ThreadSafeQueue& other)
	{
		ulock = std::move(std::unique_lock<std::mutex>(queue_mutex));
		ulock.unlock();
		safe_queue = other.safe_queue;
	}

	ThreadSafeQueue(const ThreadSafeQueue&& other)
	{
		ulock = std::move(std::unique_lock<std::mutex>(queue_mutex));
		ulock.unlock();
		safe_queue = std::move(other.safe_queue);
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
		ulock.lock();
		safe_queue.push(element);
		pop_condition.notify_one();
		ulock.unlock();
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

	T until_pop()
	{
		ulock.lock();
		if (safe_queue.empty())
			pop_condition.wait(ulock, [this]() {return !safe_queue.empty(); });
		T element = safe_queue.back();
		safe_queue.pop();
		ulock.unlock();
		return element;
	}

};

