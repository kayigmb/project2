#include <stdio.h>
#include <time.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
  FILE *src = fopen(argv[1], "rb");
  FILE *dst = fopen(argv[2], "wb");

  char buf[BUF_SIZE];
  size_t n;

  clock_t start = clock();

  while ((n = fread(buf, 1, BUF_SIZE, src)) > 0) {
    fwrite(buf, 1, n, dst);
  }

  clock_t end = clock();

  printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  fclose(src);
  fclose(dst);
  return 0;
}
