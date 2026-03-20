#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  pipe(fd); // create pipe

  pid_t p1 = fork();

  if (p1 == 0) {
    dup2(fd[1], STDOUT_FILENO); // write to pipe
    close(fd[0]);
    close(fd[1]);

    char *args[] = {"ps", "aux", NULL};
    execvp(args[0], args);
    perror("exec failed");
    exit(1);
  }

  pid_t p2 = fork();

  if (p2 == 0) {
    // Second child: grep root
    dup2(fd[0], STDIN_FILENO); // read from pipe
    close(fd[1]);
    close(fd[0]);

    char *args[] = {"grep", "root", NULL};
    execvp(args[0], args);
    perror("exec failed");
    exit(1);
  }

  // Parent
  close(fd[0]);
  close(fd[1]);

  int out = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

  char buffer[256];
  int pipe2[2];
  pipe(pipe2);

  if (fork() == 0) {
    dup2(pipe2[1], STDOUT_FILENO);
    close(pipe2[0]);
    close(pipe2[1]);

    execlp("ps", "ps", "aux", NULL);
  }

  wait(NULL);
  wait(NULL);

  // Read part of file
  int file = open("output.txt", O_RDONLY);
  int n = read(file, buffer, sizeof(buffer) - 1);
  buffer[n] = '\0';

  printf("Partial Output:\n%s\n", buffer);

  close(file);
  close(out);

  return 0;
}
