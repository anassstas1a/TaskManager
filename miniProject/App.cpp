#include <iostream>

#include "AppComponent.hpp"
#include "controller/TaskController.hpp"
#include "oatpp/network/Server.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)
void run() {
  AppComponent components;

  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                  serverConnectionProvider);
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                  serverConnectionHandler);
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                  objectMapper);
  OATPP_COMPONENT(std::shared_ptr<TaskManager>, taskManager);

  auto taskController = TaskController::createShared(objectMapper, taskManager);
  httpRouter->addController(taskController);

  oatpp::network::Server server(serverConnectionProvider,
                                serverConnectionHandler);

  OATPP_LOGI("MyApp", "Server running on port %s",
             serverConnectionProvider->getProperty("port").getData());

  server.run();
}
#include OATPP_CODEGEN_END(ApiController)
int main() {
  /*oatpp::base::Environment::init();
  std::cout << "Oat++ успешно подключен!" << std::endl;
  oatpp::base::Environment::destroy();
  int n = 100;
  auto dbConnectionProvider =
      std::make_shared<oatpp::postgresql::ConnectionProvider>(
          "postgresql://user:password@localhost:5432/taskmanager");
  auto dbExecutor =
      std::make_shared<oatpp::postgresql::Executor>(dbConnectionProvider);*/

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
