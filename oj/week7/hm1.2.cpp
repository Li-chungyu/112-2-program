#include <algorithm> 

using namespace std;

template<class T>
T* sort(T* array, int n) {
    sort(array, array + n);
    return array;
}