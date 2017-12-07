#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 1001

void create_semaphore(int val) {
  int sem_id = semget(KEY, 1, IPC_CREAT | IPC_EXCL);
  int sem_val = semctl(sem_id, 0, SETVAL, val);
  printf("sempahore created: %d\n value set: %d\n", sem_id, sem_val);
}

int main() {
  create_semaphore(4);
  return 0;
}
