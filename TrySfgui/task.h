#ifndef TASK

#define TASK

#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class Task
{
public:
	Task(const int idTask, const int idTypeTask, const std::string name);
	Task(const int idTask, const int idTypeTask, const std::string name, const std::pair<int, int>);
	std::string GetTaskName() const;
	std::pair<int, int> GetTarget() const;
	void SetTaget(std::pair<int, int> target);
	int GetIdTypeTask() const;
	bool Done() const;
	void Task::SetDone();
protected:
	int idTask, idTypeTask;
	std::string name;
	std::pair<int, int> target;
	bool done;
};

#endif TASK