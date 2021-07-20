#include  <stdio.h>
#include  <sys/types.h>
void  parse(char *line, char **argv)
{
     while (*line != '\0') {
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';
          *argv++ = line;
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n')
               line++;
     }
     *argv = '\0';
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {
          if (execvp(*argv, argv) < 0) {
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {
          while (wait(&status) != pid);
     }
}

int cd(char **args)
{
    if (chdir(args[1]) != NULL)
        chdir("lsh");

    return 1;
}

void  main(void)
{
     char  line[1024];
     char  *argv[64];

     while (1) {
          printf("Shell -> ");
          fgets(line,1024,stdin);
          int i = strlen(line)-1;
          if( line[ i ] == '\n')
              line[i] = '\0';
          parse(line, argv);
          if (strcmp(argv[0], "exit") == 0)
               exit(0);

        else  if (strcmp(argv[0], "cd") == 0)
               cd(argv);

         else execute(argv);
     }
}
