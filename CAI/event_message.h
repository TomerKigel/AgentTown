#pragma once

class event_message
{
private:
	unsigned int message_id,reciever_id,sender_id;
public:

	event_message(unsigned int message_id, unsigned int reciever_id, unsigned int sender_id)
	{
		this->message_id = message_id;
		this->reciever_id = reciever_id;
		this->sender_id = sender_id;
	}
		
	
	friend std::ostream& operator<<(std::ostream& os, event_message* em)
	{
		os << em->message_id; os<< std::endl;
		os << em->reciever_id; os << std::endl;
		os << em->sender_id; os << std::endl;
		return os;
	}
};