#pragma once

template<typename Player>
class WCallbacks {
public:
  virtual const Player& getPlayer();
};
