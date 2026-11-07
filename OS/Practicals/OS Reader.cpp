#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t mutex, writeblock;
int data = 0, rcount = 0;

// ---------------- Reader ----------------
void* reader(void* arg)
{
    int f = *((int*)arg);

    sem_wait(&mutex);
    rcount = rcount + 1;

    if (rcount == 1)
        sem_wait(&writeblock);

    sem_post(&mutex);

    cout << "Data read by reader " << f << " is " << data << endl;
    sleep(1);

    sem_wait(&mutex);
    rcount = rcount - 1;

    if (rcount == 0)
        sem_post(&writeblock);

    sem_post(&mutex);

    return NULL;
}

// ---------------- Writer ----------------
void* writer(void* arg)
{
    int f = *((int*)arg);

    sem_wait(&writeblock);

    data++;
    cout << "Data written by writer " << f << " is " << data << endl;
    sleep(1);

    sem_post(&writeblock);

    return NULL;
}

// ---------------- MAIN ----------------
int main()
{
    int i;
    pthread_t rtid[3], wtid[3];
    int id[3];

    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    for (i = 0; i < 3; i++)
    {
        id[i] = i + 1;

        pthread_create(&wtid[i], NULL, writer, &id[i]);
        pthread_create(&rtid[i], NULL, reader, &id[i]);
    }

    for (i = 0; i < 3; i++)
    {
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}