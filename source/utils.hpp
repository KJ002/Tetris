#pragma once
#include <array>


template<class T, int L>
T safeGet(int index, std::array<T, L> data, T base = 0){
  if (index < L && index >= 0)
    return data[index];
  return base;
}

template<class T>
int round(T x){
  return (int)(x + .5);
}

int intDiv(int x, int y){
  return x/y;
}
