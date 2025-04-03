#pragma once
#include "../core/Task.hpp"
#include "../dto/TaskDto.hpp"

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
