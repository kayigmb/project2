#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
  int src = open(argv[1], O_RDONLY);
  int dst = open(argv[2], O_CREAT | O_WRONLY, 0644);

  char buf[BUF_SIZE];
  ssize_t n;

  clock_t start = clock();

  while ((n = read(src, buf, BUF_SIZE)) > 0) {
    write(dst, buf, n);
  }

  clock_t end = clock();

  printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  close(src);
  close(dst);
  return 0;
}
