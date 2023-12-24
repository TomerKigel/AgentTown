/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/
#pragma once
#include <memory>
#include "message.h"
#include <mutex>
#include <optional>
#include <queue>
#include <condition_variable>

template <class T>
class Queue_Manager
{

public:
	Queue_Manager() {}
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
private:
	std::queue<T> message_queue;
	std::condition_variable condition;
	std::mutex mutex;
};

