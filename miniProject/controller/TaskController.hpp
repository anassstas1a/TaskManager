#pragma once
#include "AppComponent.hpp"
#include "core/TaskManager.hpp"
#include "dto/TaskDto.hpp"
#include "mapper/TaskMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class TaskController : public oatpp::web::server::api::ApiController {
 private:
  std::shared_ptr<TaskManager> taskManager;

 public:
  TaskController(
      const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper,
      const std::shared_ptr<TaskManager>& taskManager)
      : oatpp::web::server::api::ApiController(objectMapper),
        taskManager(taskManager) {}

  static std::shared_ptr<TaskController> createShared(
      const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper,
      const std::shared_ptr<TaskManager>& taskManager) {
    return std::make_shared<TaskController>(objectMapper, taskManager);
  }

  ENDPOINT("GET", "/tasks", getTasks) {
    auto tasks = taskManager->getTasks();
    auto dtoList = oatpp::List<oatpp::Object<TaskDto>>::createShared();

    for (const auto& task : tasks) {
      dtoList->push_back(TaskMapper::toDto(task));
    }
    return createDtoResponse(Status::CODE_200, dtoList);
  }

  ENDPOINT("POST", "/tasks", createTask, BODY_DTO(Object<TaskDto>, taskDto)) {
    taskManager->addTask(taskDto->description);
    return createResponse(Status::CODE_201, "Task created");
  }

  ENDPOINT("PUT", "/tasks/{id}/complete", completeTask, PATH(Int32, id)) {
    bool success = taskManager->completeTask(id);
    if (success) {
      return createResponse(Status::CODE_200, "Task completed");
    } else {
      return createResponse(Status::CODE_404, "Task not found");
    }
  }

  ENDPOINT("DELETE", "/tasks/{id}", deleteTask, PATH(Int32, id)) {
    bool success = taskManager->deleteTask(id);
    if (success) {
      return createResponse(Status::CODE_200, "Task deleted");
    } else {
      return createResponse(Status::CODE_404, "Task not found");
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)
