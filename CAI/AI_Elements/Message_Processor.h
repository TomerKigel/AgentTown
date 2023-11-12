//#pragma once
//#include "../Message_System/message.h"
//#include "../Framework/Interfaces/Interface_Runnable.h"
//#include "../Message_System/Message_Parser.h"
//#include "../Message_System/Queue_Manager.h"
//#include "Agent_Parameters.h"
//
//#include <thread>
//#include <mutex>
//
//class Message_Processor : public Interface_Runnable
//{
//public:
//	Message_Processor(Agent_Parameters *params, std::vector<std::weak_ptr<Interface_Graphics_Observer>> *observers)
//	{
//		pParameters = params;
//		pObservers = observers;
//	}
//	~Message_Processor()
//	{
//		agent_thread_.join();
//	}
//	//Message passing
//	inline void push_message(message::Parsed_Message& msg);
//
//	inline void process_message(message::Parsed_Message& msg);
//
//	//Interface_Runnable concurrent interface
//	inline void run();
//
//private:
//	inline void event_controller_();
//
//	//concurrency variables
//	std::mutex param_mutex_;
//	std::mutex observers_mutex_;
//	std::condition_variable cv_;
//	std::thread agent_thread_;
//
//	//Message queue
//	Queue_Manager<message::Parsed_Message> message_queue_;
//
//	//object state ptr
//	Agent_Parameters *pParameters; // maybe weak ptr 
//
//	std::vector<std::weak_ptr<Interface_Graphics_Observer>> *pObservers;
//};
//
//void Message_Processor::event_controller_()
//{
//	std::unique_lock<std::mutex> lock(param_mutex_);
//	while (message_queue_.size() <= 0)
//		cv_.wait(lock, [this] {return message_queue_.size() > 0; });
//
//	lock.unlock();
//
//	std::optional<message::Parsed_Message> msg = message_queue_.pop();
//	if (msg)
//		process_message(msg.value());
//
//	if (pParameters->is_alive()) {
//		event_controller_();
//	}
//}
//
//void Message_Processor::push_message(message::Parsed_Message& msg)
//{
//	std::unique_lock<std::mutex>lock(param_mutex_);
//	message_queue_.push(msg);
//	lock.unlock();
//	cv_.notify_all();
//}
//
//void Message_Processor::run()
//{
//	pParameters->close_for_change();
//	agent_thread_ = std::thread([this]() { event_controller_(); });
//}
//
//void Message_Processor::process_message(message::Parsed_Message& msg)
//{
//	std::lock_guard<std::mutex>lock(observers_mutex_);
//	if (msg.x_position && msg.y_position)
//	{
//		for (std::weak_ptr<Interface_Graphics_Observer> obs : *pObservers)
//			obs.lock()->update_position(msg.x_position.value(), msg.y_position.value());
//		pParameters->setLocation(msg.x_position.value(), msg.y_position.value());
//	}
//	if (msg.type == "disconnect") {
//		for (std::weak_ptr<Interface_Graphics_Observer> obs : *pObservers)
//			obs.lock()->kill();
//		pParameters->kill();
//	}
//}