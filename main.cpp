#include <iostream>
#include "lab01.hpp"

using namespace std;

const int CAP = 8;

void displayArray(const int a[], int size)
{
    if (size == 0)
    {
        cout << "Array is empty.\n";
        return;
    }

    cout << "Active elements: ";
    for (int i = 0; i < size; ++i)
    {
        cout << a[i] << ' ';
    }
    cout << "\nLogical size: " << size << "\n";
    cout << "Capacity: " << CAP << "\n";
}

void demonstrateBoundaryCases()
{
    cout << "=== Required boundary-case demonstrations ===\n";

    // Full-array insertion: size equals capacity.
    int fullArray[3] = {10, 20, 30};
    int fullSize = 3;
    cout << "Before insertion into full array: ";
    for (int i = 0; i < fullSize; ++i) cout << fullArray[i] << ' ';
    cout << "\n";
    bool inserted = insertAt(fullArray, fullSize, 3, 1, 99);
    cout << "Insert result: " << (inserted ? "success" : "rejected") << "\n";
    cout << "After attempt (must be unchanged): ";
    for (int i = 0; i < fullSize; ++i) cout << fullArray[i] << ' ';
    cout << "\nSize remains: " << fullSize << "\n\n";

    // Empty-array deletion: there is no valid index to delete.
    int emptyArray[3] = {0, 0, 0};
    int emptySize = 0;
    bool deleted = deleteAt(emptyArray, emptySize, 0);
    cout << "Delete from empty array: "
         << (deleted ? "success" : "rejected") << "\n";
    cout << "Size remains: " << emptySize << "\n";
    cout << "============================================\n\n";
}

int main()
{
    int a[CAP] = {10, 20, 30, 40};
    int size = 4; // Number of active elements; CAP is allocated capacity.
    int choice;

    demonstrateBoundaryCases();

    do
    {
        cout << "\n===== CSC-531 Lab 01: Array Menu =====\n";
        cout << "1. Display array\n";
        cout << "2. Insert an element\n";
        cout << "3. Delete an element\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            displayArray(a, size);
        }
        else if (choice == 2)
        {
            int pos, value;
            cout << "Enter insertion index (0 to " << size << "): ";
            cin >> pos;
            cout << "Enter value: ";
            cin >> value;

            if (insertAt(a, size, CAP, pos, value))
                cout << "Insertion successful.\n";
            else
                cout << "Insertion rejected: invalid position or array full.\n";
        }
        else if (choice == 3)
        {
            int pos;
            cout << "Enter deletion index (0 to " << size - 1 << "): ";
            cin >> pos;

            if (deleteAt(a, size, pos))
                cout << "Deletion successful.\n";
            else
                cout << "Deletion rejected: invalid index or array empty.\n";
        }
        else if (choice == 4)
        {
            cout << "Exiting program.\n";
        }
        else
        {
            cout << "Invalid menu choice. Select 1, 2, 3 or 4.\n";
        }

    } while (choice != 4);

    return 0;
}
