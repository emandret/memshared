#include "shared.h"

int main(void)
{
    // shmget returns an identifier in shmid
    int shmid = shmget(IPC_PRIVATE, sizeof(struct s_shared), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget error: %s\n", strerror(errno));
        return 1;
    }

    // shmat to attach to shared memory
    struct s_shared *shmem = (struct s_shared *) shmat(shmid, NULL, 0);

    // shmat return (void *) -1 in case of error
    if (shmem == (void *) -1) {
        fprintf(stderr, "shmat error: %s\n", strerror(errno));
        return 1;
    }

    // initialize shared type
    struct s_shared shared = {21, 42, "Hello world"};

    // copy data to shared memory (*shmem = shared)
    memcpy(shmem, &shared, sizeof(struct s_shared));

    // print the identifier to stdout
    printf("%d\n", shmid);

    // shmdt to detach from shared memory
    shmdt(shmem);

    return 0;
}
