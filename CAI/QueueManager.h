#pragma once
#include <memory>
#include "message.h"
#include "ThreadSafeQueue.h"
#include <unordered_map>

template <class T>
class QueueManager
{
	std::queue<T> incoming_message_queue;
	std::unordered_map<int,ThreadSafeQueue<T>> outgoing_message_queues;
	std::condition_variable incoming_condition;
	//std::condition_variable outgoing_condition;
	std::mutex incoming_mutex;
	//std::mutex outgoing_mutex;
	std::unique_lock<std::mutex> in_lock;
	//std::unique_lock<std::mutex> out_lock;
public:
	QueueManager()
	{
		in_lock = std::move(std::unique_lock(incoming_mutex));
		in_lock.unlock();
		//out_lock = std::move(std::unique_lock(outgoing_mutex));
		//out_lock.unlock();
	}

	void in_push(T element)
	{
		in_lock.lock();
		incoming_message_queue.push(element);
		incoming_condition.notify_one();
		in_lock.unlock();
	}
	void out_push(T element,int id)
	{
		//out_lock.lock();
		outgoing_message_queues.at(id).push(element);
		//outgoing_condition.notify_one();
		//out_lock.unlock();
	}

	T stop_until_in_pop()
	{
		in_lock.lock();
		if (incoming_message_queue.size() == 0)
			incoming_condition.wait(in_lock, [this]() {return incoming_message_queue.size() != 0; });
		T element = incoming_message_queue.front();
		incoming_message_queue.pop();
		in_lock.unlock();
		return element;
	}
	/*T stop_until_out_pop(int id)
	{
		out_lock.lock();
		if (outgoing_message_queues.at(id).size() == 0)
			outgoing_condition.wait(out_lock, [this]() {return outgoing_message_queues.at(id).size() != 0; });
		T element = outgoing_message_queues.at(id).front();
		outgoing_message_queues.at(id).pop();
		out_lock.unlock();
		return element;
	}*/

	std::optional<T&> in_pop()
	{
		in_lock.lock();
		if (incoming_message_queue.size() > 0) {
			T& element = incoming_message_queue.front();
			incoming_message_queue.pop();
			in_lock.unlock();
			return element;
		}
		in_lock.unlock();
		return std::nullopt;
	}

	//T& out_pop(int id)
	//{
	//	out_lock.lock();
	//	if (outgoing_message_queues.at(id).size() > 0) {
	//		T& element = outgoing_message_queues.at(id).front();
	//		outgoing_message_queues.at(id).pop();
	//		out_lock.unlock();
	//		return element;
	//	}
	//	out_lock.unlock();
	//	return std::nullopt;
	//}

	
	std::optional<ThreadSafeQueue<T>*> get_out_queue(int connection_id)
	{
		if(outgoing_message_queues.count(connection_id) == 0)
			return std::nullopt;

		return &outgoing_message_queues.find(connection_id)->second;
		
	}

	void add_out_queue(int connection_id)
	{
		if(outgoing_message_queues.count(connection_id == 0))
			outgoing_message_queues.emplace(std::make_pair(connection_id, ThreadSafeQueue<T>()));
	}

	size_t size_in()
	{
		in_lock.lock();
		size_t size = incoming_message_queue.size();
		in_lock.unlock();
		return size;
	}


	/*size_t size_out()
	{
		out_lock.lock();
		size_t size = outgoing_message_queues.size();
		out_lock.unlock();
		return size;
	}*/
};

