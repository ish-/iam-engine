#include "Symbol.hpp"

TSymbol Symbols::getSymbolID(const std::string& symbol) {
    // std::lock_guard<std::mutex> lock(mutex_);
    auto it = symbolToID_.find(symbol);
    if (it != symbolToID_.end()) {
        return it->second;
    }

    // Register new symbol
    TSymbol id = nextID_++;
    symbolToID_[symbol] = id;
    idToSymbol_[id] = symbol;
    return id;
}

// Retrieve the symbol name for a given ID (if exists)
std::string Symbols::getSymbolName(TSymbol id) const {
    // std::lock_guard<std::mutex> lock(mutex_);
    auto it = idToSymbol_.find(id);
    if (it != idToSymbol_.end()) {
        return it->second;
    }
    return "<Unknown Symbol>";
}

Symbol::Symbol (const std::string& symbol) : value(Symbols::get().getSymbolID(symbol)) {}

std::string Symbol::name () const {
  return Symbols::get().getSymbolName(value);
}
