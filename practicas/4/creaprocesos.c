#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void signalHandler(int signum) {
    if(signum == 17) {
        int status;
        wait(&status);
        printf("Terminando después del hijo y estatus %d\n", status);
    } else if(signum ==  2) {
        printf("\njajaja no me matas\n");
    }
}

int main(int argc, char *argv[]) {
    signal(17, signalHandler);
    signal(2, signalHandler);
    unsigned pid = fork();
    if(pid == 0) {
        sleep(5);
        printf("Soy el proceso hijo\n");
        execv(argv[1],&argv[1]);
        return 10;
    } else {
        printf("Soy el proceso padre y mi hijo es: %u\n", pid);
        while(1) {
            sleep(2);
            printf("Trabajando...\n");
        }
    }
    printf("Hola mundo\n");
    return 0;
}