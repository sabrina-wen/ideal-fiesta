#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#define KEY 45

int main(int argc, char * argv[]) {
  if (argc == 3 && strcmp(argv[1], "-c") == 0) {
    //printf("hi\n");
    // creates semaphore, note the permissions
    int sem_id = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0777);
    if (sem_id == -1) {
      printf("semaphore already exists\n");
    } else {
      printf("sempahore created: %d\n", sem_id);
      semctl(sem_id, 0, SETVAL, atoi(argv[2]));
      if ((semctl(sem_id, 0, GETVAL)) == -1) {
        printf("Semctl error: %s\n", strerror(errno));
      } else {
        printf("value set: %d\n", semctl(sem_id, 0, GETVAL));
      }
    }
  } else if (argc == 2 && strcmp(argv[1], "-v") == 0) {
    int sem_id = semget(KEY, 0, 0777);
    if ((semctl(sem_id, 0, GETVAL)) == -1) {
      printf("Semctl error: %s\n", strerror(errno));
    } else {
      printf("value set: %d\n", semctl(sem_id, 0, GETVAL));
    }
  } else if (argc == 2 && strcmp(argv[1], "-r") == 0) {
    int sem_id = semget(KEY, 0, 0777);
    semctl(sem_id, 0, IPC_RMID);
    printf("semaphore removed: %d\n", sem_id);
  } else {
    printf("args invalid\n");
  }
  return 0;
}
