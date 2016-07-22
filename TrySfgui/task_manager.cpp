#include "task_manager.h"
#include "task.h"

TaskManager::TaskManager() {
	this->idTask = 0;
}

std::shared_ptr<Task> TaskManager::CreateTask(const int idTypeTask)
{
	switch (idTypeTask) {
	case 1:
		return std::make_shared<Task>(this->idTask, idTypeTask, "Moving Dud");
		break;
	default:
		return std::make_shared<Task>(this->idTask, idTypeTask, "Smooking weed :)");
		break;
	}

	this->idTask++;
}