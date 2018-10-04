#include "shared.h"
#include <stdlib.h>

int main(void)
{
    char str[1024];

    // retrieve the shmid
    int shmid = atoi(fgets(str, 1024, stdin));

    // shmat to attach to shared memory
    struct s_shared *shmem = (struct s_shared *) shmat(shmid, NULL, 0);

    // shmat return (void *) -1 in case of error
    if (shmem == (void *) -1) {
        fprintf(stderr, "shmat error: %s\n", strerror(errno));
        return 1;
    }

    printf("Shared structure: %d %d %s\n", shmem->x, shmem->y, shmem->str);

    // detach from shared memory
    shmdt(shmem);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
