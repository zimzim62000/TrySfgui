#ifndef TASKMANAGER

#define TASKMANAGER

class Task;

#include <memory>

#pragma once

class TaskManager {

public:
	TaskManager();
	std::shared_ptr<Task> CreateTask(const int idTypeTask);

private:
	int idTask;
};


#endif TASKMANAGER