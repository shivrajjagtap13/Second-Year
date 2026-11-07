#include <iostream>
using namespace std;

// Calculate NEED matrix
void calculateNeed(int n, int m, int maxNeed[][10],
                   int allocation[][10],
                   int need[][10]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }
}

// Safety Algorithm (returns 1 = safe, 0 = unsafe)
int isSafe(int n, int m, int processes[],
           int available[],
           int maxNeed[][10],
           int allocation[][10],
           int safeSequence[]) {

    int need[10][10];
    calculateNeed(n, m, maxNeed, allocation, need);

    int work[10];
    int finish[10] = {0};  // 0 = false, 1 = true

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    cout << "\nChecking system safety...\n";

    while (count < n) {
        int allocated = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {

                int canExecute = 1;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute == 1) {
                    cout << "Process P" << i << " can execute, available before: ";
                    for (int k = 0; k < m; k++) cout << work[k] << " ";
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
            return 0;
        }
    }

    cout << "System is in SAFE state.\n";
    return 1;
}

// Resource Request Algorithm
void requestResources(int n, int m, int processes[],
                      int available[],
                      int maxNeed[][10],
                      int allocation[][10],
                      int pid, int request[]) {

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

    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int processes[10];
    for (int i = 0; i < n; i++)
        processes[i] = i;

    int available[10];
    cout << "Enter available resources:\n";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    int maxNeed[10][10], allocation[10][10];

    cout << "Enter MAX NEED matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maxNeed[i][j];
        }
    }

    cout << "Enter ALLOCATION matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    int safeSequence[10];

    if (isSafe(n, m, processes, available, maxNeed, allocation, safeSequence) == 1) {
        cout << "Safe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << safeSequence[i] << " ";
        cout << endl;
    }

    int pid;
    cout << "\nEnter process number making request: ";
    cin >> pid;

    int request[10];
    cout << "Enter request vector:\n";
    for (int i = 0; i < m; i++)
        cin >> request[i];

    requestResources(n, m, processes, available, maxNeed, allocation, pid, request);

    return 0;
}