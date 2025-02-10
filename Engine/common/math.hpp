#pragma once

template<typename T>
inline T lerp (const std::type_identity_t<T>& from, const std::type_identity_t<T>& to, const T& value){
  return from + (to - from) * value;
}

template<typename T>
inline T invlerp (const T& from, const T& to, const T& value){
  return (value - from) / (to - from);
}

template<typename T>
inline T remap (const T& origFrom, const T& origTo, const T& targetFrom, const T& targetTo, const T& value){
  T rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

template<typename T>
inline T loop(const T& value, const T& minRange, const T& maxRange) {
    T range = maxRange - minRange;
    if (range == 0.0) {
        return minRange; // Avoid division by zero if the range is zero
    }
    return mod((value - minRange), range) + minRange;
}