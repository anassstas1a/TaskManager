#pragma once
#include "Task.h"
#include "TaskDto.h"

class TaskMapper {
 public:
  static oatpp::Object<TaskDto> toDto(const Task& task) {
    auto dto = TaskDto::createShared();
    dto->id = task.getId();
    dto->description = task.getDescription();
    dto->isCompleted = task.isCompletedTask();
    return dto;
  }
};
