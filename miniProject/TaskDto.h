#pragma once
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TaskDto : public oatpp::DTO {
  DTO_INIT(TaskDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, description);
  DTO_FIELD(Boolean, isCompleted);
};
#include OATPP_CODEGEN_END(DTO)
