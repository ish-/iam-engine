#define SINGLETON(NAME) \
  static NAME& get() { \
    static NAME instance; \
    return instance; \
  }

#define PROP_GETSET (TYPE, NAME) \
  TYPE _NAME; \
  TYPE NAME () const { return NAME; } \
  void NAME (const TYPE& _NAME) { NAME = _NAME; }