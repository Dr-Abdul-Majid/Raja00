#include "lab01.hpp"

bool insertAt(int a[], int& size, int cap, int pos, int x)
{
    // Valid insertion positions are 0 through size (inclusive).
    // A full array has no available slot for another element.
    if (size < 0 || cap < 0 || size >= cap || pos < 0 || pos > size)
    {
        return false;
    }

    // Move active elements one position to the right, starting at
    // the last active element. Moving backwards prevents overwriting.
    for (int i = size; i > pos; --i)
    {
        a[i] = a[i - 1];
    }

    a[pos] = x;
    ++size;
    return true;
}

bool deleteAt(int a[], int& size, int pos)
{
    // Valid deletion positions are 0 through size - 1.
    if (size <= 0 || pos < 0 || pos >= size)
    {
        return false;
    }

    // Shift the elements after pos one position to the left.
    // The final assignment reads a[size - 1], the last active element.
    for (int i = pos; i < size - 1; ++i)
    {
        a[i] = a[i + 1];
    }

    --size;
    return true;
}
