#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

pthread_mutex_t lock;
FILE *out;

typedef struct {
  char *filename;
  char *keyword;
} Task;

void *search_file(void *arg) {
  Task *task = (Task *)arg;
  FILE *f = fopen(task->filename, "r");

  if (!f)
    return NULL;

  char line[1024];
  int count = 0;

  while (fgets(line, sizeof(line), f)) {
    if (strstr(line, task->keyword))
      count++;
  }

  fclose(f);

  pthread_mutex_lock(&lock);
  fprintf(out, "%s: %d\n", task->filename, count);
  pthread_mutex_unlock(&lock);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("Usage: ./search keyword output file1 ... threads\n");
    return 1;
  }

  char *keyword = argv[1];
  out = fopen(argv[2], "w");

  int num_threads = atoi(argv[argc - 1]);
  int file_count = argc - 4;

  pthread_t threads[num_threads];
  Task tasks[file_count];

  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < file_count; i++) {
    tasks[i].filename = argv[i + 3];
    tasks[i].keyword = keyword;

    pthread_create(&threads[i % num_threads], NULL, search_file, &tasks[i]);
  }

  for (int i = 0; i < num_threads; i++)
    pthread_join(threads[i], NULL);

  fclose(out);
  pthread_mutex_destroy(&lock);

  return 0;
}
