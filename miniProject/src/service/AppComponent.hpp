#pragma once
#include "core/TaskManager.hpp"
#include "interceptor/CorsInterceptor.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
class AppComponent {
 public:
  OATPP_CREATE_COMPONENT(
      std::shared_ptr<oatpp::network::ServerConnectionProvider>,
      serverConnectionProvider)([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"localhost", 8000, oatpp::network::Address::IP_4});
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                         httpRouter)([] {
    auto router = oatpp::web::server::HttpRouter::createShared();
    return router;
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<CorsInterceptor>, corsInterceptor)([] {
    return std::make_shared<CorsInterceptor>();
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                         serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                    httpRouter);
    auto handler =
        oatpp::web::server::HttpConnectionHandler::createShared(httpRouter);

    OATPP_COMPONENT(std::shared_ptr<CorsInterceptor>, corsInterceptor);
    handler->addRequestInterceptor(corsInterceptor);

    return handler;
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                         objectMapper)([] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<TaskManager>, taskManager)([] {
    return std::make_shared<TaskManager>();
  }());
};
