#pragma once
#include <memory>
#include <unordered_map>

template <typename T>
using sp = std::shared_ptr<T>;

template <typename T>
using wp = std::weak_ptr<T>;

template <typename K, typename T>
using umap = std::unordered_map<K, T>;

