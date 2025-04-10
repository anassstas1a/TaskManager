#pragma once
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

class CorsInterceptor
    : public oatpp::web::server::interceptor::RequestInterceptor {
 public:
  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override {
    auto response = OutgoingResponse::createShared(
        oatpp::web::protocol::http::Status::CODE_200, nullptr);

    response->putHeader("Access-Control-Allow-Origin", "*");
    response->putHeader("Access-Control-Allow-Methods",
                        "GET, POST, PUT, DELETE, OPTIONS");
    response->putHeader("Access-Control-Allow-Headers", "Content-Type");

    if (request->getStartingLine().method == "OPTIONS") {
      return response;
    }

    return nullptr;
  }
};
