#define SINGLETON(NAME) \
  static NAME& get() { \
    static NAME instance; \
    return instance; \
  }