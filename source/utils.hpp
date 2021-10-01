#pragma once

template<class T>
T safeGet(int index, T* data, int length, T base = 0){
    if (index < length)
        return *(data+index);
    return base;
}
