#include <iostream>
using namespace std;

// ---------------- FIFO Page Replacement ----------------
int fifo(int pages[], int n, int capacity) {
    int memory[100];
    int size = 0;
    int page_faults = 0;
    int index = 0;

    cout << "\nFIFO Page Replacement:\n";

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if page exists
        for (int j = 0; j < size; j++) {
            if (memory[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            page_faults++;

            if (size < capacity) {
                memory[size++] = page;
            } else {
                memory[index] = page;
                index = (index + 1) % capacity;
            }

            cout << "Page " << page << " -> Fault | Memory: ";
        } else {
            cout << "Page " << page << " -> Hit   | Memory: ";
        }

        for (int j = 0; j < size; j++)
            cout << memory[j] << " ";
        cout << endl;
    }

    return page_faults;
}


// ---------------- LRU Page Replacement ----------------
int lru(int pages[], int n, int capacity) {
    int memory[100];
    int size = 0;
    int page_faults = 0;

    cout << "\nLRU Page Replacement:\n";

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pos = -1;

        // Find page in memory
        for (int j = 0; j < size; j++) {
            if (memory[j] == page) {
                pos = j;
                break;
            }
        }

        if (pos == -1) { // Fault
            page_faults++;

            if (size < capacity) {
                memory[size++] = page;
            } else {
                // Shift left (remove least recently used)
                for (int j = 0; j < capacity - 1; j++)
                    memory[j] = memory[j + 1];

                memory[capacity - 1] = page;
            }

            cout << "Page " << page << " -> Fault | Memory: ";
        } else { // Hit
            int temp = memory[pos];

            // Shift left
            for (int j = pos; j < size - 1; j++)
                memory[j] = memory[j + 1];

            memory[size - 1] = temp;

            cout << "Page " << page << " -> Hit   | Memory: ";
        }

        for (int j = 0; j < size; j++)
            cout << memory[j] << " ";
        cout << endl;
    }

    return page_faults;
}


// ---------------- Optimal Page Replacement ----------------
int optimal(int pages[], int n, int capacity) {
    int memory[100];
    int size = 0;
    int page_faults = 0;

    cout << "\nOptimal Page Replacement:\n";

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if page exists
        for (int j = 0; j < size; j++) {
            if (memory[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            page_faults++;

            if (size < capacity) {
                memory[size++] = page;
            } else {
                int index_to_replace = -1;
                int farthest = -1;

                for (int j = 0; j < capacity; j++) {
                    int k;

                    // Find future use
                    for (k = i + 1; k < n; k++) {
                        if (memory[j] == pages[k])
                            break;
                    }

                    // If not used again
                    if (k == n) {
                        index_to_replace = j;
                        break;
                    }

                    // Farthest use
                    if (k > farthest) {
                        farthest = k;
                        index_to_replace = j;
                    }
                }

                memory[index_to_replace] = page;
            }

            cout << "Page " << page << " -> Fault | Memory: ";
        } else {
            cout << "Page " << page << " -> Hit   | Memory: ";
        }

        for (int j = 0; j < size; j++)
            cout << memory[j] << " ";
        cout << endl;
    }

    return page_faults;
}


// ---------------- MAIN PROGRAM ----------------
int main() {

    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = 13;
    int capacity = 3;

    cout << "Page Reference String: ";
    for (int i = 0; i < n; i++)
        cout << pages[i] << " ";

    cout << "\nNumber of Frames: " << capacity << endl;

    // FIFO
    int fifo_faults = fifo(pages, n, capacity);
    cout << "Total Page Faults (FIFO): " << fifo_faults << endl;

    // LRU
    int lru_faults = lru(pages, n, capacity);
    cout << "Total Page Faults (LRU): " << lru_faults << endl;

    // Optimal
    int optimal_faults = optimal(pages, n, capacity);
    cout << "Total Page Faults (Optimal): " << optimal_faults << endl;

    return 0;
}