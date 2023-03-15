#pragma once
#include <iostream>
#include "interface_calculatable.h"
#include <mutex>


namespace tsk
{
	enum goal_function_enum { minimize, maximize, target };
	class task
	{
	private:
		double current_task_grade,maximum_task_grade;
		std::mutex task_grade_mutex;
		std::shared_ptr<interface_calculatable> calc_object;
		short goal_function;
		double target_value;
	public:
		task(std::string function_name = "minimize")
		{
			if (function_name != "minimize" || function_name != "maximize" || (function_name.find("target") == std::string::npos))
				throw new std::runtime_error("passed function name invalid, must be of group {minimize,maximize,target%d}");

			if (function_name == "minimize")
				goal_function = tsk::minimize;
			else if (function_name == "maximize")
				goal_function = tsk::maximize;
			else if (function_name.find("target") != std::string::npos)
			{
				goal_function = tsk::target;
				target_value = 0;
			}
			current_task_grade = 0;
			maximum_task_grade = 100;
			calc_object = nullptr;
		}

		task(task& other_task) : calc_object(other_task.calc_object), maximum_task_grade(other_task.maximum_task_grade), goal_function(other_task.goal_function), target_value(other_task.target_value) 
		{
			current_task_grade = 0;
		}

		virtual ~task() {}

		double getGrade()
		{
			double ans = 0;
			task_grade_mutex.lock();
			current_task_grade = calc_object->calculate();
			ans = current_task_grade;
			task_grade_mutex.unlock();
			return ans;
		}

		std::shared_ptr<interface_calculatable> GetPerferedCalculatable(std::shared_ptr<interface_calculatable> other)
		{
			if (goal_function == tsk::minimize){
				if (*this->calc_object <= other)
					return this->calc_object;
				return other;
			}
			else if (goal_function == tsk::maximize){
				if (*this->calc_object >= other)
					return this->calc_object;
				return other;
			}
			else if (goal_function == tsk::target){
				double pa = this->calc_object->calculate();
				double pb = other->calculate();
				return (abs(pa - target_value) <=  abs(pb - target_value)) ? this->calc_object : other;
			}
		}
	};
}