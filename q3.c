#include <math.h>
#include <pthread.h>
#include <stdio.h>

#define MAX 200000
#define THREADS 16

int total_primes = 0;
pthread_mutex_t lock;

int is_prime(int n) {
  if (n < 2)
    return 0;
  for (int i = 2; i <= sqrt(n); i++)
    if (n % i == 0)
      return 0;
  return 1;
}

void *worker(void *arg) {
  int start = ((int *)arg)[0];
  int end = ((int *)arg)[1];
  int local_count = 0;

  for (int i = start; i <= end; i++)
    if (is_prime(i))
      local_count++;

  pthread_mutex_lock(&lock);
  total_primes += local_count;
  pthread_mutex_unlock(&lock);

  return NULL;
}

int main() {
  pthread_t threads[THREADS];
  int ranges[THREADS][2];

  pthread_mutex_init(&lock, NULL);

  int step = MAX / THREADS;

  for (int i = 0; i < THREADS; i++) {
    ranges[i][0] = i * step + 1;
    ranges[i][1] = (i == THREADS - 1) ? MAX : (i + 1) * step;

    pthread_create(&threads[i], NULL, worker, ranges[i]);
  }

  for (int i = 0; i < THREADS; i++)
    pthread_join(threads[i], NULL);

  printf("Total primes: %d\n", total_primes);

  pthread_mutex_destroy(&lock);
  return 0;
}
