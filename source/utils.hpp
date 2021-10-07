#pragma once
#include <array>


template<class T, int L>
T safeGet(int index, std::array<T, L> data, T base = 0){
    if (index < L && index >= 0)
        return data[index];
    return base;
}
