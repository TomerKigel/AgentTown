#pragma once

#include <iostream>

class Interface_Calculatable
{
public:
	virtual double calculate() = 0;

	virtual bool operator<(Interface_Calculatable& rhs)
	{
		return this->calculate() < rhs.calculate();
	}

	virtual bool operator<(std::shared_ptr<Interface_Calculatable> rhs)
	{
		return this->calculate() < rhs->calculate();
	}
	


	virtual bool operator<=(Interface_Calculatable& rhs)
	{
		return this->calculate() <= rhs.calculate();
	}
	virtual bool operator<=(std::shared_ptr<Interface_Calculatable> rhs)
	{
		return this->calculate() <= rhs->calculate();
	}


	virtual bool operator>=(Interface_Calculatable& rhs)
	{
		return this->calculate() >= rhs.calculate();
	}
	virtual bool operator>=(std::shared_ptr<Interface_Calculatable> rhs)
	{
		return this->calculate() >= rhs->calculate();
	}



	virtual bool operator==(Interface_Calculatable& rhs)
	{
		return this->calculate() == rhs.calculate();
	}
	virtual bool operator==(std::shared_ptr<Interface_Calculatable> rhs)
	{
		return this->calculate() == rhs->calculate();
	}


	virtual bool operator>(Interface_Calculatable& rhs)
	{
		return this->calculate() > rhs.calculate();
	}
	virtual bool operator >(std::shared_ptr<Interface_Calculatable> rhs)
	{
		return this->calculate() > rhs->calculate();
	}
};