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
  OATPP_LOGI("MyApp", "Frontend running on port 3000");

  server.run();
}
#include OATPP_CODEGEN_END(ApiController)
int main() {
  oatpp::base::Environment::init();

  std::thread frontThread([]() {
    std::system(
        "cd /d C:/Users/anast/source/repos/miniProject/miniProject && "
        "python -m http.server 3000");
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

#ifdef _WIN32
  std::system("start http://localhost:3000");
#elif __APPLE__
  std::system("open http://localhost:3000");
#else
  std::system("xdg-open http://localhost:3000");
#endif

  run();
  oatpp::base::Environment::destroy();
  return 0;
}
