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
	bool Target() const;
	void SetTaget(std::pair<int, int> target);
	int GetIdTypeTask() const;
	bool Done() const;
	void SetDone();
	bool GetRun() const;
	void SetRun();
	void SetName(std::string name);
	void AddName(std::string name);
protected:
	int idTask, idTypeTask;
	std::string name;
	std::pair<int, int> target;

	bool onTarget;
	bool done;
	bool run;
};

#endif TASK