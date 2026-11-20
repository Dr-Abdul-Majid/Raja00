#ifndef LAB01_HPP
#define LAB01_HPP

// Inserts x at index pos in the active portion of a fixed-capacity array.
// Returns true on success and false if the position is invalid or the
// array is already full. On failure, the array and size remain unchanged.
bool insertAt(int a[], int& size, int cap, int pos, int x);

// Deletes the element at index pos from the active portion of the array.
// Returns true on success and false if pos is invalid.
// On failure, the array and size remain unchanged.
bool deleteAt(int a[], int& size, int pos);

#endif
