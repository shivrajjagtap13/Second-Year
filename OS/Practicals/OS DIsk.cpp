#include <iostream>
#include <cmath>
using namespace std;

// ---------------- FCFS ----------------
void fcfs(int requests[], int n, int head) {
    int total_seek = 0;
    int current = head;

    cout << "\nFCFS Order: ";

    for (int i = 0; i < n; i++) {
        cout << requests[i] << " ";
        total_seek += abs(requests[i] - current);
        current = requests[i];
    }

    float avg = (float)total_seek / n;

    cout << "\nTotal Seek Time: " << total_seek;
    cout << " | Average Seek Time: " << avg << endl;
}


// ---------------- SSTF ----------------
void sstf(int requests[], int n, int head) {
    int total_seek = 0;
    int current = head;

    int visited[100] = {0};

    cout << "\nSSTF Order: ";

    for (int i = 0; i < n; i++) {
        int min_dist = 100000;
        int index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(requests[j] - current);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        cout << requests[index] << " ";
        total_seek += abs(requests[index] - current);
        current = requests[index];
    }

    float avg = (float)total_seek / n;

    cout << "\nTotal Seek Time: " << total_seek;
    cout << " | Average Seek Time: " << avg << endl;
}


// ---------------- SCAN ----------------
void scan(int requests[], int n, int head, int disk_size) {
    int total_seek = 0;
    int current = head;

    int left[100], right[100];
    int l = 0, r = 0;

    // Divide requests
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    // Sort left (descending)
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    // Sort right (ascending)
    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    cout << "\nSCAN Order: ";

    // Right side first
    for (int i = 0; i < r; i++) {
        cout << right[i] << " ";
        total_seek += abs(right[i] - current);
        current = right[i];
    }

    // Move to end
    total_seek += abs((disk_size - 1) - current);
    current = disk_size - 1;

    // Left side
    for (int i = 0; i < l; i++) {
        cout << left[i] << " ";
        total_seek += abs(left[i] - current);
        current = left[i];
    }

    float avg = (float)total_seek / n;

    cout << "\nTotal Seek Time: " << total_seek;
    cout << " | Average Seek Time: " << avg << endl;
}


// ---------------- C-SCAN ----------------
void cscan(int requests[], int n, int head, int disk_size) {
    int total_seek = 0;
    int current = head;

    int left[100], right[100];
    int l = 0, r = 0;

    // Divide requests
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    // Sort both ascending
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    cout << "\nC-SCAN Order: ";

    // Right side
    for (int i = 0; i < r; i++) {
        cout << right[i] << " ";
        total_seek += abs(right[i] - current);
        current = right[i];
    }

    // Move to end
    total_seek += abs((disk_size - 1) - current);
    current = disk_size - 1;

    // Jump to beginning
    total_seek += abs(current - 0);
    current = 0;

    // Left side
    for (int i = 0; i < l; i++) {
        cout << left[i] << " ";
        total_seek += abs(left[i] - current);
        current = left[i];
    }

    float avg = (float)total_seek / n;

    cout << "\nTotal Seek Time: " << total_seek;
    cout << " | Average Seek Time: " << avg << endl;
}


// ---------------- MAIN ----------------
int main() {

    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = 8;

    int head = 53;
    int disk_size = 200;

    cout << "Disk Requests: ";
    for (int i = 0; i < n; i++)
        cout << requests[i] << " ";

    cout << "\nInitial Head Position: " << head << endl;

    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size);
    cscan(requests, n, head, disk_size);

    return 0;
}