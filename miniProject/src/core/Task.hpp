#pragma once
#include <string>
class Task {
 private:
  int id;
  std::string description;
  bool isCompleted;

 public:
  Task(int id, const std::string& description);

  int getId() const;
  std::string getDescription() const;
  void markAsCompleted();
  bool isCompletedTask() const;
};
