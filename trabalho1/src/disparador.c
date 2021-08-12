#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// SO utilizado: Arch Linux
//
// # uname -a
// Linux [redacted] 5.12.15-arch1-1 #1 SMP PREEMPT Wed, 07 Jul 2021 23:35:29
// +0000 x86_64 GNU/Linux

int comandoParaExecutar;

int tarefa1() {

  // Gera a seed para a função aleatória
  time_t seed;
  // Cria o fd para comunicação entre processos.
  int fd[2];
  pipe(fd);

  // Prepara a função aleatória
  srand((unsigned)time(&seed));

  // Cria variável para armazenar pid do processo filho
  pid_t childpid;

  // Cria o filho através do fork
  if ((childpid = fork()) == -1) {
    perror("failed to fork");
    exit(1);
  }

  // Caso seja o processo filho, fecha o fd[0], porque a comunicação deverá
  // ocorrer apenas no sentido filho -> pai
  if (childpid == 0) {
    close(fd[0]);
    int r = rand() % 100 + 1;
    printf("%d\n", r);
    write(fd[1], &r, sizeof(int));
    close(fd[1]);
    return 0;
  } else {
    close(fd[1]);
    read(fd[0], &comandoParaExecutar, sizeof(int));
    close(fd[0]);
    return 0;
  }

  return 0;
}

int tarefa2(int command) {

  // Cria a variável para armazenar pid do filho
  pid_t childpid;

  // Cria o filho através do fork
  if (((childpid = fork())) == 0) {
    if (command == 0) {
      printf("Não há comando a executar\n");
      exit(1);
    } else if (command % 2 == 0) {
      execlp("/bin/ping", "ping", "8.8.8.8", "-c", "5", NULL);
      return 0;
    } else {
      execlp("/bin/ping", "ping", "paris.testdebit.info", "-c", "5", "-i", "2",
             NULL);
      return 0;
    }
  }
  return 1;
}

// O trecho de código foi baseado no seguinte artigo:
// https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
// A função sig_handler fica responsável pela
// tomada de decisão a partir do sinal recebido.
void sig_handler(int sign) {
  switch (sign) {
  case SIGUSR1:
    tarefa1();
    break;
  case SIGUSR2:
    tarefa2(comandoParaExecutar);
    break;
  case SIGTERM:
    printf("Finalizando o disparador\n");
    exit(0);
  }
}

int main() {
  // Pega o pid do processo pai.
  int pid = getpid();

  printf("%d\n", pid);
  // Associa os sinais importantes à função sig_handler
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);
  signal(SIGTERM, sig_handler);
  // Loop infinito. O programa só é finalizado ao receber um SIGTERM.
  for (;;) {
  }
  return 0;
}
