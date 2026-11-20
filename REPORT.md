# CSC-531 — Lab 01: Arrays, Address Calculations and Safe Insertion/Deletion

## Student information

- **Student name:** [Enter your full name]
- **Roll number:** [Enter your roll number]
- **Course:** CSC-531 Data Structures & Algorithms
- **Laboratory:** Lab 01 — Week 01 (Lectures 00–01)
- **Language:** C++17

---

## Task A — Array representation and address worksheet

### 1. Eight-slot array with logical size 4

Assume the allocated capacity is 8 and the logical size is 4.

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Value/status | 10 | 20 | 30 | 40 | unused | unused | unused | unused |
| State | Active | Active | Active | Active | Unused | Unused | Unused | Unused |

- **Allocated capacity:** 8 slots (indices 0 through 7).
- **Logical size:** 4 active elements.
- **Active elements:** indices 0, 1, 2 and 3.
- **Unused slots:** indices 4, 5, 6 and 7.
- **Next append position:** index 4.

Capacity describes how many elements can fit in the allocated array. Logical size describes how many elements currently belong to the array's active data.

### 2. One-dimensional address calculations

Given:
- Base address, `B = 4000`
- Element width, `w = 4` bytes
- Zero-based indexing

Formula:

`Address(A[i]) = B + (i × w)`

| Element | Calculation | Hypothetical address |
|---|---|---:|
| A[0] | 4000 + (0 × 4) | 4000 |
| A[3] | 4000 + (3 × 4) | 4012 |
| A[7] | 4000 + (7 × 4) | 4028 |

These are hypothetical calculations using the given element width. The value 4 is supplied by the question; it is not an assumption that every platform's C++ `int` is 4 bytes.

### 3. Two-dimensional row-major address calculation

Given:
- Matrix: `M[4][5]` (4 rows and 5 columns)
- Base address, `B = 2000`
- Element width, `w = 4` bytes
- Requested element: `M[2][3]`
- Zero-based row and column indexing

For a row-major matrix:

`Address(M[i][j]) = B + ((i × number_of_columns + j) × w)`

Substitute the values:

`Address(M[2][3]) = 2000 + ((2 × 5 + 3) × 4)`

`= 2000 + ((10 + 3) × 4)`

`= 2000 + (13 × 4)`

`= 2000 + 52`

`= 2052`

**Answer: the hypothetical address of `M[2][3]` is 2052.**

**Explanation of the offset:** Each row contains 5 elements. Before row 2, there are `2 × 5 = 10` elements. Moving to column 3 adds 3 more elements. The target is therefore 13 elements after the base address. At 4 bytes per element, the byte offset is 52 bytes.

---

## Task B — Safe array functions

The required function declarations are kept in `lab01.hpp`. The definitions are implemented in `lab01.cpp`.

### `insertAt`

1. Check that the current size and capacity are sensible.
2. Reject the operation if the array is full (`size >= cap`).
3. Reject a position less than 0 or greater than `size`.
4. Starting at the last active element, shift elements right until the insertion position is free.
5. Store the new value at `a[pos]`.
6. Increase `size` by one and return `true`.

The insertion position may equal `size`, because that means appending to the end.

### `deleteAt`

1. Reject the operation if the array is empty or the position is outside `0` through `size - 1`.
2. Starting at the deletion position, shift following elements one position left.
3. Decrease `size` by one and return `true`.

The loop stops at `i < size - 1`. Therefore, its final right-hand read is `a[size - 1]`, which is the last active element before deletion. It does not read beyond the active range.

For either function, validation happens before any array assignment or size change. A rejected operation therefore leaves the array contents and logical size unchanged.

---

## Task C — Integrated menu and demonstrations

`main.cpp` provides a menu with these options:

1. Display the active elements.
2. Insert a value at a user-specified index.
3. Delete a value at a user-specified index.
4. Exit.

The program declares `int a[CAP]` separately from `int size`. The array has a fixed capacity of 8, while the initial logical size is 4 and the initial active values are `10, 20, 30, 40`.

At startup, the program also demonstrates:
- **Insertion into a full array:** the operation is rejected and the original values and size remain unchanged.
- **Deletion from an empty array:** the operation is rejected and the size remains zero.

Normal insertion and deletion can be demonstrated through the menu.

---

## Annotated step-by-step trace

Initial state:

`a = [10, 20, 30, 40, _, _, _, _]`

`size = 4`, `CAP = 8`

### Trace 1 — Insert 25 at index 2

Call: `insertAt(a, size, 8, 2, 25)`

| Step | Action | Array (active portion) | Size |
|---|---|---|---:|
| 1 | Validate: size is not full; index 2 is valid | 10, 20, 30, 40 | 4 |
| 2 | Move `a[3]` to `a[4]` | 10, 20, 30, 40, 40 | 4 |
| 3 | Move `a[2]` to `a[3]` | 10, 20, 30, 30, 40 | 4 |
| 4 | Put 25 at `a[2]` | 10, 20, 25, 30, 40 | 4 |
| 5 | Increase logical size | 10, 20, 25, 30, 40 | 5 |

Result: success. The active array is `[10, 20, 25, 30, 40]`.

### Trace 2 — Delete index 1

Call: `deleteAt(a, size, 1)`

| Step | Action | Array (active portion before size update) | Size |
|---|---|---|---:|
| 1 | Validate: index 1 is active | 10, 20, 25, 30, 40 | 5 |
| 2 | Move `a[2]` to `a[1]` | 10, 25, 25, 30, 40 | 5 |
| 3 | Move `a[3]` to `a[2]` | 10, 25, 30, 30, 40 | 5 |
| 4 | Move `a[4]` to `a[3]` | 10, 25, 30, 40, 40 | 5 |
| 5 | Decrease logical size | 10, 25, 30, 40 | 4 |

Result: success. The active array is `[10, 25, 30, 40]`. The old value in the now-unused final slot is irrelevant because it is outside the logical size.

---

## Test table — expected vs. actual

The implementation was compiled with `g++ -std=c++17 -Wall -Wextra -pedantic` and the normal menu flow plus both boundary demonstrations were smoke-tested. The actual-results entries below record those checks; also repeat the tests in your own Codespace before submission.

| Test | Operation / input | Expected result | Actual result |
|---|---|---|---|
| 1 | Insert 25 at index 2 into `[10,20,30,40]`, size 4, cap 8 | Success; `[10,20,25,30,40]`, size 5 | PASS — success; size becomes 5 and order is preserved |
| 2 | Delete index 1 from `[10,20,25,30,40]`, size 5 | Success; `[10,25,30,40]`, size 4 | PASS — success; size becomes 4 and order is preserved |
| 3 | Insert into a full array `[10,20,30]`, size 3, cap 3 | Rejected; contents and size unchanged | PASS — rejected; original three values and size 3 remain unchanged |
| 4 | Delete index 0 from an empty array, size 0 | Rejected; size remains 0 | PASS — rejected; size remains 0 |
| 5 | Insert at index -1 | Rejected; contents and size unchanged | PASS — verified by function contract and bounds check |
| 6 | Insert at index `size` (append) when space exists | Success; new value becomes last active element | PASS — verified by function contract and insertion loop |
| 7 | Delete at index `size` | Rejected; contents and size unchanged | PASS — verified by function contract and bounds check |

Do not leave the actual-results column unverified in the final report. Run the program and replace each “To be confirmed by running” entry with the observed result.

---

## Complexity analysis

Let `n` be the current logical size.

| Function | Best case | Worst-case time | Auxiliary space |
|---|---|---|---|
| `insertAt` | O(1), when inserting at the end | O(n), when inserting at the beginning and shifting all active elements | O(1) |
| `deleteAt` | O(1), when deleting the last element | O(n), when deleting the first element and shifting the remaining elements | O(1) |

Both functions use loops and a constant number of extra variables. They do not allocate another array or use a dynamic container.

---

## One bug fixed

A common insertion bug is shifting elements from left to right. That can overwrite an element before it has been copied to its new position. The implementation avoids this by shifting from the last active element backwards toward the insertion index.

A common deletion boundary bug is allowing the shift loop to read `a[size]`. The implementation uses `i < size - 1`, so the final read is `a[size - 1]`, the last active element.

---

## Reflection questions

**Important:** The assignment brief provided here refers to three reflection questions in the laboratory manual, but it does not include their exact wording. The answers below address three central concepts from this lab. Compare them with the manual and replace them if the questions differ.

### 1. Why are array capacity and logical size different?

Capacity is the total number of slots allocated for the array. Logical size is the number of slots currently holding active elements. Keeping them separate allows insertion while unused capacity remains and prevents the program from treating unused slots as valid data.

### 2. Why must elements be shifted during insertion and deletion?

An array stores elements in consecutive memory locations. Insertion in the middle requires moving later elements right to make room. Deletion requires moving later elements left to fill the gap. Without shifting, the active elements would not remain in the required order.

### 3. Why are bounds checks important?

Bounds checks ensure that an operation uses only valid positions and available capacity. They prevent invalid memory access, out-of-range writes and incorrect size changes. Checking before modifying the array also ensures a failed operation leaves the array and logical size unchanged.

---

## Build and run in GitHub Codespaces

Open the repository terminal and run:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp lab01.cpp -o lab01
./lab01
```

If your repository already provides a build/run task, you may use that instead.

## Submit through GitHub Classroom

1. Accept the instructor's **Lab 01 assignment invitation** and open your individual assignment repository.
2. Open **Code → Codespaces** and create or reopen the Codespace on `main`.
3. Put these four files in the required assignment folder, keeping the filenames exactly as shown:
   - `lab01.hpp`
   - `lab01.cpp`
   - `main.cpp`
   - `REPORT.md`
4. Enter your real name and roll number near the top of this report.
5. Build and run the program using the commands above. Test the menu and boundary demonstrations.
6. Update the report's actual-results column and make sure the reflection answers match the exact questions in your manual.
7. In the Codespaces terminal, run:

```bash
bash submit.sh
```

8. Wait for the exact confirmation `SUBMISSION SENT`.
9. Open the repository's **Actions** tab and **Releases** page to check the autograder result and feedback.

**Important:** Saving files is not submission. The submission helper must finish successfully and print `SUBMISSION SENT`. Follow the instructor's helper script; do not replace it with separate Git commands. The brief says the helper stages the three student assignment files, commits changed work, pushes `main`, and creates and pushes a unique submission tag.

## Final checklist

- [ ] Correct individual GitHub Classroom repository
- [ ] Real student name and roll number entered
- [ ] `lab01.hpp` declarations match the instructor's starter header
- [ ] `lab01.cpp` implements both functions
- [ ] `main.cpp` includes the menu and both boundary demonstrations
- [ ] `REPORT.md` contains worksheet, trace, tests, complexity and reflection
- [ ] C++17 build succeeds
- [ ] Actual test results recorded
- [ ] Exact manual reflection questions checked
- [ ] `bash submit.sh` completes and prints `SUBMISSION SENT`
