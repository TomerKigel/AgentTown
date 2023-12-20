#pragma once
enum class system_state { RUNNING, PAUSED, TERMINATED };

template <class T>
class System : public Component
{
public:
	virtual void provide_message(T& msg) = 0;

	virtual std::string service_name() = 0;

	system_state state()
	{
		return system_state_;
	}

private:
	system_state system_state_;
};