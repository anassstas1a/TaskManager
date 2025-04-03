#include "TaskManager.h"

#include <mutex>
void TaskManager::addTask(const std::string& description) {
  std::lock_guard<std::mutex> lock(mtx);
  tasks.emplace_back(nextId++, description);
}
bool TaskManager::deleteTask(int id) {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto it = tasks.begin(); it != tasks.end(); it++) {
    if (it->getId() == id) {
      tasks.erase(it);
      return true;
    }
  }
  return false;
}
bool TaskManager::completeTask(int id) {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto& task : tasks) {
    if (task.getId() == id) {
      task.markAsCompleted();
      return true;
    }
  }
  return false;
}
std::vector<Task> TaskManager::getTasks() const {
  std::lock_guard<std::mutex> lock(mtx);
  return tasks;
}
