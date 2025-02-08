#pragma once
#include <memory>

template <typename T>
using sp = std::shared_ptr<T>;

template <typename T>
using wp = std::weak_ptr<T>;