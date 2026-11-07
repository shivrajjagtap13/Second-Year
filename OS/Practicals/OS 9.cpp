#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

// Shared resource
int counter = 0;

// Mutex declaration
pthread_mutex_t lock;

// ---------------- Thread Function ----------------
void* criticalSection(void* arg)
{
    for (int i = 0; i < 5; i++)
    {
        // Lock before entering critical section
        pthread_mutex_lock(&lock);

        cout << "Thread " << pthread_self() << " entered Critical Section" << endl;

        // Read shared variable
        int temp = counter;

        // Increment
        temp++;

        // Simulate delay
        sleep(1);

        // Update shared variable
        counter = temp;

        cout << "Thread " << pthread_self() << " updated counter to " << counter << endl;
        cout << "Thread " << pthread_self() << " leaving Critical Section\n" << endl;

        // Unlock mutex
        pthread_mutex_unlock(&lock);

        // Sleep outside critical section
        sleep(1);
    }

    return NULL;
}

// ---------------- MAIN ----------------
int main()
{
    pthread_t t1, t2;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&t1, NULL, criticalSection, NULL);
    pthread_create(&t2, NULL, criticalSection, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Final result
    cout << "\nFinal value of counter: " << counter << endl;

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}