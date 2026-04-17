#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>

int contador = 0;

void sig_handler(int num)
{
    contador++;
    printf("Chamou Ctrl+C\n");
    if (contador == 3)
    {
        struct sigaction handler;

        handler.sa_handler = SIG_DFL;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);

        /*
        Envia o sinal para si mesmo.
        Outra forma: raise(SIGINT);
        */
        kill(getpid(), SIGINT);
    }
}

int main()
{

    struct sigaction handler;

    handler.sa_handler = sig_handler;
    handler.sa_flags = 0;
    sigemptyset(&handler.sa_mask);

    sigaction(SIGINT, &handler, NULL);

    printf("Meu pid: %d\n", getpid());

    while (1)
    {
        sleep(1);
    }
    return 0;
}
