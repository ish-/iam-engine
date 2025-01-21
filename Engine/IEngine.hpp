#pragma once
#include <memory>
#include "WObject.hpp"

class IEngine {
public:
  virtual ~IEngine() = default;

  virtual std::shared_ptr<WObject> create() = 0;
};
