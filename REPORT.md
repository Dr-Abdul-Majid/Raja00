# CSC-531 Lab 01 — Arrays, Address Calculations and Safe Insertion/Deletion

- **Name:** Sayam Abbasi
- **Roll No:** 46
- **Programme:** BSCS (Section A), Session 2025–29
- **Course:** CSC-531 Data Structures & Algorithms

## Task A — Array representation and address worksheet

An array with capacity 8 and logical size 4:

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|-------|---|---|---|---|---|---|---|---|
| Value | 70 | 80 | 90 | 85 | – | – | – | – |

- **Active elements:** indices 0–3 (70, 80, 90, 85). Logical size = 4.
- **Unused slots:** indices 4–7. They are allocated but hold no active data.
- **Next append position:** index 4.

Capacity (8) is the total allocated slots; size (4) is how many are actually in use. They are kept separate.

### Address calculations

Formula for a 1D array: **address of A[i] = B + i × w**, where B is the base address and w is the size of one element.

With B = 4000 and w = 4:

- A[0] = 4000 + 0 × 4 = **4000**
- A[3] = 4000 + 3 × 4 = **4012**
- A[7] = 4000 + 7 × 4 = **4028**

For a row-major 2D array M[rows][cols], the offset of M[i][j] is **i × cols + j** (full rows before it, plus the column inside its row).

For M[4][5] with B = 2000 and w = 4, element M[2][3]:

- Offset = 2 × 5 + 3 = 10 + 3 = **13** (2 full rows of 5 elements each = 10, plus 3 more in row 2)
- Address = 2000 + 13 × 4 = 2000 + 52 = **2052**

These are conceptual calculations; they do not assume `sizeof(int) == 4` on every platform.

## Task B — Safe array functions

`insertAt(a, size, cap, pos, x)` rejects an invalid position (`pos < 0` or `pos > size`) and a full array (`size == cap`). Otherwise it shifts elements right starting from the end, writes `x` at `pos`, and increases `size`.

`deleteAt(a, size, pos)` rejects an invalid index (`pos < 0` or `pos >= size`). Otherwise it shifts elements left starting from `pos` and decreases `size`. The loop stops at `size - 2`, so it never reads beyond the final active element.

On a failed operation both functions return `false` before touching anything, so `size` and the array contents stay unchanged.

## Task C — Menu and demonstrations

`main.cpp` keeps `size` separate from `CAP` (8) and offers a menu: 1 Display, 2 Insert, 3 Delete, 4 Exit. At startup it also demonstrates the two boundary cases: inserting into a full array (rejected) and deleting from an empty array (rejected). Normal cases are done through the menu.

## Trace

Starting array: [70, 80, 90, 85], size = 4.

**Insert 75 at index 2:**
1. Check: pos 2 is valid (0 ≤ 2 ≤ 4), array not full (4 < 8).
2. Shift right from the end: a[4] = a[3] → 85 moves to index 4. Array: [70, 80, 90, 85, 85].
3. Shift right: a[3] = a[2] → 90 moves to index 3. Array: [70, 80, 90, 90, 85].
4. Write a[2] = 75. Array: [70, 80, 75, 90, 85].
5. size becomes 5. Result: **[70, 80, 75, 90, 85], size = 5**. ✔

**Delete index 1:**
1. Check: pos 1 is valid (0 ≤ 1 < 5).
2. Shift left: a[1] = a[2] → 75 moves to index 1. Array: [70, 75, 75, 90, 85].
3. Shift left: a[2] = a[3] → 90 moves to index 2. Array: [70, 75, 90, 90, 85].
4. Shift left: a[3] = a[4] → 85 moves to index 3. Array: [70, 75, 90, 85, 85].
5. size becomes 4, so the last slot is inactive. Result: **[70, 75, 90, 85], size = 4**. ✔

## Tests

| # | Test | Expected | Actual | Result |
|---|------|----------|--------|--------|
| 1 | Insert 75 at index 2 into [70, 80, 90, 85] | [70, 80, 75, 90, 85], size 5 | [70, 80, 75, 90, 85], size 5 | Pass |
| 2 | Delete index 1 from [70, 80, 75, 90, 85] | [70, 75, 90, 85], size 4 | [70, 75, 90, 85], size 4 | Pass |
| 3 | Insert into a full array (size = CAP) | Returns false, nothing changes | Returns false, nothing changes | Pass |
| 4 | Delete at index -1 and at index == size | Returns false, nothing changes | Returns false, nothing changes | Pass |
| 5 | Delete the only element of a 1-element array | size becomes 0 (empty) | size becomes 0 | Pass |

## Complexity

| Function | Worst-case time | Auxiliary space | Why |
|----------|----------------|-----------------|-----|
| `insertAt` | O(n) | O(1) | In the worst case (insert at index 0) every element shifts right once. Only one loop variable is used. |
| `deleteAt` | O(n) | O(1) | In the worst case (delete at index 0) every element shifts left once. Only one loop variable is used. |
| `display` | O(n) | O(1) | It visits each active element once. |

Direct access by index, A[i], is O(1) because the address is computed with one formula.

## One bug fixed

**Bug:** During insertion I first shifted elements forward, starting from the insertion position. Each step copied an element over the next one before that next element had been moved, so data was overwritten and lost (for example, inserting at index 2 turned [70, 80, 90, 85] into [70, 80, 75, 90, 90] — the 85 disappeared).

**Fix:** Shift backward, starting from the last active element and moving toward the insertion position. Each element moves into a slot that is already free, so nothing is overwritten. Deletion keeps shifting forward, because overwriting the deleted slot is exactly what we want there.

## Reflection

1. **How many shifts does insertion at position p need in a list of n elements?**
   It needs n − p shifts: every element from p to the end moves one place right. Inserting at the end (p = n) needs 0 shifts; inserting at the front (p = 0) needs n shifts.

2. **Why does insertion shift backward but deletion shift forward?**
   Insertion shifts backward so each element moves into an already-empty slot; shifting forward would overwrite the next element before it is moved and lose data. Deletion shifts forward because the goal is to fill the deleted slot — overwriting it is intended.

3. **When is an array a good choice, and when is it not?**
   An array is good when we need frequent direct access by index, which is O(1), and when the data size is known in advance. It is a poor choice when elements are often inserted or deleted near the front, because that costs O(n) shifts every time.
