#pragma once

#include <iostream>

class interface_calculatable
{
public:
	virtual double calculate() = 0;

	virtual bool operator<(interface_calculatable& rhs)
	{
		return this->calculate() < rhs.calculate();
	}

	virtual bool operator<(std::shared_ptr<interface_calculatable> rhs)
	{
		return this->calculate() < rhs->calculate();
	}
	


	virtual bool operator<=(interface_calculatable& rhs)
	{
		return this->calculate() <= rhs.calculate();
	}
	virtual bool operator<=(std::shared_ptr<interface_calculatable> rhs)
	{
		return this->calculate() <= rhs->calculate();
	}


	virtual bool operator>=(interface_calculatable& rhs)
	{
		return this->calculate() >= rhs.calculate();
	}
	virtual bool operator>=(std::shared_ptr<interface_calculatable> rhs)
	{
		return this->calculate() >= rhs->calculate();
	}



	virtual bool operator==(interface_calculatable& rhs)
	{
		return this->calculate() == rhs.calculate();
	}
	virtual bool operator==(std::shared_ptr<interface_calculatable> rhs)
	{
		return this->calculate() == rhs->calculate();
	}


	virtual bool operator>(interface_calculatable& rhs)
	{
		return this->calculate() > rhs.calculate();
	}
	virtual bool operator >(std::shared_ptr<interface_calculatable> rhs)
	{
		return this->calculate() > rhs->calculate();
	}
};