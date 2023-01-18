#include <pthread.h>
#include <stdlib.h>
typedef struct {
    //Or whatever information that you need
    int *max_prime;
    int *ith_prime;
} compute_prime_struct;

void *compute_prime (void *args) {
    compute_prime_struct *actual_args = args;
    //...
    free(actual_args);
    return 0;
}
#define num_threads 10
int main() {
    int max_prime = 0;
    int primeArray[num_threads];
    pthread_t primes[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        compute_prime_struct *args = malloc(sizeof *args);
        args->max_prime = &max_prime;
        args->ith_prime = &primeArray[i];
        if(pthread_create(&primes[i], NULL, compute_prime, args)) {
            free(args);
            //goto error_handler;
        }
    }
    return 0;
}