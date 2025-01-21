#pragma once
#include <memory>
class WContext;

class WObject {
public:
  // WObject (WContext& ctx): ctx(ctx) {};
  // virtual ~WObject () = default;

  WContext& ctx;

  // virtual void draw() = 0;
  // virtual void update() = 0;
};
