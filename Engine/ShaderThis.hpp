#include <memory>

class SharedThis : public std::enable_shared_from_this<SharedThis> {
public:
  std::shared_ptr<SharedThis> getSharedThis() {
    return shared_from_this();
  }
};
