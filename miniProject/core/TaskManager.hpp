#pragma once
#include <mutex>
#include <vector>

#include "Task.hpp"
class TaskManager {
 private:
  std::vector<Task> tasks;
  int nextId = 1;
  mutable std::mutex mtx;

 public:
  void addTask(const std::string& description);
  bool deleteTask(int id);
  bool completeTask(int id);
  std::vector<Task> getTasks() const;
};
