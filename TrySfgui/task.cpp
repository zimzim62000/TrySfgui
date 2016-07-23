#include "task.h"

Task::Task(const int idTask, const int idTypeTask, const std::string name, const std::pair<int,int>)
{
	this->idTask = idTask;
	this->idTypeTask = idTypeTask;
	this->name = name;
	this->target = target;
	this->done = false;
	this->run = false;
	this->onTarget = true;
}

Task::Task(const int idTask, const int idTypeTask, const std::string name)
{
	this->idTask = idTask;
	this->idTypeTask = idTypeTask;
	this->name = name;
	this->done = false;
	this->run = false;
}

int Task::GetIdTypeTask() const
{
	return this->idTypeTask;
}


std::string Task::GetTaskName() const
{
	return this->name;
}

std::pair<int, int> Task::GetTarget() const
{
	return this->target;
}

void Task::SetTaget(std::pair<int, int> target)
{
	this->target = target;
	this->onTarget = true;
}

bool Task::Done() const
{
	return this->done;
}

void Task::SetDone()
{
	this->done = true;
}

void Task::SetName(std::string name)
{
	this->name += " " + name;
}

void Task::AddName(std::string name)
{
	this->name += " " + name;
}

bool Task::GetRun() const
{
	return this->run;
}

void Task::SetRun()
{
	this->run = true;
}

bool Task::Target() const
{
	return this->onTarget;
}