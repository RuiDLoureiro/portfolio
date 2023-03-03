
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


int counter;
int* bufferx;
float* buffery;
int* pdimbuf;
int* pkmax;
pthread_mutex_t lock;

void* tx(void* arg)
{
    pthread_mutex_lock(&lock);
    srand (223);
    int aux =0;

    for (int i=0;i<*pdimbuf;i++){
        
        aux = (rand() % 2)-1;
        bufferx[i]= aux;
    }

    pthread_mutex_unlock(&lock);
      return 0;
}

void* ty (void* arg){

    pthread_mutex_lock(&lock);
    for (int i=0; i<*pkmax;i++){
        buffery[i]= exp(pdimbuf[i]);
    }

    pthread_mutex_unlock(&lock);
      return 0;
}

void* tp (void* arg){

    pthread_mutex_lock(&lock);

    size_t aux = sizeof(*buffery) / sizeof(float);
    for (int i=0; i<aux;i++){
        printf("%.5f\n", buffery[i]);
        buffery[i] = 0;

    }
    pthread_mutex_unlock(&lock);
    return 0;
}



int main(int argc, char *argv[])
{

    if (argc != 5 ){
        printf("Argumentos inválidos\n");
        return 0;
    }
    int nt,n,dimbuf,kmax, thy;
    sscanf(argv[1], "%d", &nt);
    sscanf(argv[1], "%d", &n);
    sscanf(argv[1], "%d", &dimbuf);
    sscanf(argv[1], "%d", &kmax);

    if (nt<1 || n < nt || (dimbuf> n || dimbuf<1) || (kmax > dimbuf || kmax<1)){
        printf("Argumentos inválidos\n");
        return 0;
    }
    printf ("Cálculo de %d valores de e^x com %d tarefas, dimbuf = %d e kmax = %d", n, nt, dimbuf, kmax);

    bufferx = (int*) malloc (dimbuf);
    buffery = (float*) malloc (dimbuf);

    *pdimbuf = dimbuf;
    *pkmax = kmax;

    pthread_t tid[nt+2];

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
        }

    pthread_create(&(tid[0]), NULL, &tx, NULL);

    for(int i=1; i<nt;i++){

        thy = pthread_create(&(tid[i]), NULL, &ty, NULL);
        if (thy != 0)
            printf("\nThread can't be created : [%s]", strerror(thy));
        i++;
    }

    pthread_create(&(tid[nt+1]), NULL, &tp, NULL);

    for (int j=0; j< nt+2; j++){
        pthread_join(tid[j], NULL);
    }
    pthread_mutex_destroy(&lock); 

    return 0;
}
