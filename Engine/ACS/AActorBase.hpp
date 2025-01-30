// class AActorBase : public Transform, public std::enable_shared_from_this<AActorBase> {
// // AActorBase
// protected:
//   std::weak_ptr<AActorBase> parent;
// public:
//   template<typename... Args>
//   AActorBase (Args&&... args): Transform(std::forward<Args>(args)...) {}

//   std::vector<std::shared_ptr<AActorBase>> children;

//   // void attach(const AActorBase& child);
//   void attach(const std::shared_ptr<AActorBase>& child);
//   std::shared_ptr<AActorBase> getParent() const;

//   mat4 getAbsTransformMatrix() const;

// // AActor
//   // TODO:
//   std::string name = "Actor";

//   std::unordered_map<std::type_index, std::shared_ptr<AComponent>> components;

//   virtual void init();
//   virtual void update();

//   template <typename T>
//   std::shared_ptr<T> getComponent() {
//       auto it = components.find(typeid(T));
//       if (it != components.end()) {
//           return std::dynamic_pointer_cast<T>(it->second);
//       }
//       return nullptr;
//   }
// };
