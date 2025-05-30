#define SINGLETON(T) \
  static T& get() { \
    static T instance; \
    return instance; \
  }

#define SINGLETON_PTR(T) \
  SINGLETON(T) \
  static std::shared_ptr<T> getPtr() { \
    static std::shared_ptr<T> instancePtr(&get(), [](T*) { \
    }); \
    return instancePtr; \
  }

#define PROP_GETSET (TYPE, NAME) \
  TYPE _NAME; \
  TYPE NAME () const { return NAME; } \
  void NAME (const TYPE& _NAME) { NAME = _NAME; }