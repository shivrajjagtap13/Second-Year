#include <iostream>
using namespace std;

// Calculate NEED matrix
void calculateNeed(int n, int m, int maxNeed[][10],
                   int allocation[][10],
                   int need[][10]) {
//We leave the first dimension empty because the compiler only needs the number of columns to calculate memory addresses in a 2D array
//we can replace 10 with the actual number of resources, but it must match the column size of the array and remain consistent across the program.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

// Safety Algorithm
int isSafe(int n, int m, int processes[],
           int available[],
           int maxNeed[][10],
           int allocation[][10],
           int safeSequence[]) {

    int need[10][10];
    calculateNeed(n, m, maxNeed, allocation, need);

    int work[10];
    int finish[10] = {0};   // 0 = false, 1 = true

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    cout << "\nChecking system safety...\n";

    while (count < n) {
        int allocated = 0;   
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {

                int canExecute = 1;  // replaces bool canExecute

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute == 1) {
                    cout << "Process P" << i << " can execute, available before: ";
                    for (int k = 0; k < m; k++) 
                    cout << work[k] << " ";
                    cout << endl;

                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    allocated = 1;

                    cout << "Process P" << i << " finished, available now: ";
                    for (int k = 0; k < m; k++) cout << work[k] << " ";
                    cout << endl;
                }
            }
        }

        if (allocated == 0) {
            cout << "System is NOT in safe state!\n";
            return 0;   // false
        }
    }

    cout << "System is in SAFE state.\n";
    return 1;   // true
}

// Resource Request Algorithm
void requestResources(int n, int m, int processes[],
                      int available[],
                      int maxNeed[][10],
                      int allocation[][10],
                      int pid, int request[]) {

    cout << "\nProcess P" << pid << " requesting: ";
    for (int i = 0; i < m; i++) 
    cout << request[i] << " ";
    cout << endl;

    int need[10][10];
    calculateNeed(n, m, maxNeed, allocation, need);

    // Check request <= need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[pid][i]) {
            cout << "Error: Exceeded maximum claim!\n";
            return;
        }
    }

    // Check request <= available
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            cout << "Resources not available. Wait.\n";
            return;
        }
    }

    // Temporary allocation
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
    }

    int safeSequence[10];

    if (isSafe(n, m, processes, available, maxNeed, allocation, safeSequence) == 1) {
        cout << "Request GRANTED.\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << safeSequence[i] << " ";
        cout << endl;
    } else {
        cout << "Request DENIED. Rolling back...\n";

        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
        }
    }
}

// MAIN
int main() {

    int processes[5] = {0, 1, 2, 3, 4};
    int n = 5;
    int m = 3;

    int available[10] = {3, 3, 2};

    int maxNeed[10][10] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allocation[10][10] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    cout << "Initial System State\n";

    cout << "Available: ";
    for (int i = 0; i < m; i++) cout << available[i] << " ";
    cout << endl;

    int safeSequence[10];

    if (isSafe(n, m, processes, available, maxNeed, allocation, safeSequence) == 1) {
        cout << "Safe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << safeSequence[i] << " ";
        cout << endl;
    }

    int request[3] = {1, 0, 2};
    requestResources(n, m, processes, available, maxNeed, allocation, 1, request);

    return 0;
}