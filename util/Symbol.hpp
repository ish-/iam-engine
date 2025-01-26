#pragma once
#include <cmath>
#include <cstdint>
#include <string>
// #include <mutex>
#include <unordered_map>
#include "MACRO.hpp"

using TSymbol = uint32_t;

class Symbols {
public:
    SINGLETON(Symbols)

    TSymbol getSymbolID(const std::string& symbol);
    std::string getSymbolName(TSymbol id) const;

private:
    // mutable std::mutex mutex_;
    std::unordered_map<std::string, TSymbol> symbolToID_;
    std::unordered_map<TSymbol, std::string> idToSymbol_;
    TSymbol nextID_ = 1;
};

class Symbol {
public:

  Symbol () = default;
  Symbol (const std::string& symbol);

  std::string name () const;

  bool operator== (const Symbol& other) const {
    return value == other.value;
  }

  TSymbol operator() () const {
    return value;
  }

// private:
  TSymbol value = 0;
};

namespace std {

  template <>
  struct hash<Symbol> {
    std::size_t operator()(const Symbol& s) const noexcept {
      return std::hash<TSymbol>()(s.value);
    }
  };

}