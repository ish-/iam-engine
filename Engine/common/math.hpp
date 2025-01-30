#pragma once

template<typename T>
inline T invlerp (T from, T to, T value){
  return (value - from) / (to - from);
}

template<typename T>
inline T remap (T origFrom, T origTo, T targetFrom, T targetTo, T value){
  T rel = invlerp(origFrom, origTo, value);
  return mix(targetFrom, targetTo, rel);
}

template<typename T>
inline T loop(T value, T minRange, T maxRange) {
    T range = maxRange - minRange;
    if (range == 0.0) {
        return minRange; // Avoid division by zero if the range is zero
    }
    return mod((value - minRange), range) + minRange;
}