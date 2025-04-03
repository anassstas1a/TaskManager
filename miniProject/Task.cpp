#include "Task.h"

Task::Task(int id, const std::string& description)
    : id(id), description(description), isCompleted(false) {}
int Task::getId() const { return id; }
std::string Task::getDescription() const { return description; }
void Task::markAsCompleted() { isCompleted = true; }
bool Task::isCompletedTask() const { return isCompleted; }
