#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../include/main.h"

pid_t *pidList;
int pidCount;

int main()
{
	pidCount = 0;
	pidList = (pid_t*) malloc(sizeof(pid_t) * 1);

	while(1)
	{
		// Prompt gösteriliyor..
		prompt();

		// Kullanıcıdan komut alınıp çalıştırılıyor...
		runUserInput();
	}

	free(pidList);
}

void prompt()
{
	char cwd[1024];
    getcwd(cwd, sizeof(cwd));
	
	COLOR("\n┌──[", COLOR_GREEN);   // Prompt looks like this :
	COLOR(cwd, COLOR_B_BLUE_BR);	//
	COLOR("]\n└─", COLOR_GREEN);	// ┌──[/home/brz/osHomework]
	COLOR("sau", COLOR_B_WHITE);	// └─sau > {commands_here}
	COLOR(" > ", COLOR_B_BLUE_BR);	
}

void runUserInput()
{
	char command[81];
	fgets(command, sizeof(command), stdin);
	command[strcspn(command, "\r\n")] = 0;

	char** parsedCommand = NULL;
	parsedCommand = parseInput(command);

	if(parsedCommand[0] != NULL) 
	{
		if(strcmp(parsedCommand[0], "exit") == 0)
		{
			printf("exit");
			free(parsedCommand);
			free(pidList);
			exit(EXIT_SUCCESS);
		}
		else if(strcmp(parsedCommand[0], "cd") == 0)
		{
			if(chdir(parsedCommand[1]) == 0)
			{
				char cwd[1024];
    			getcwd(cwd, sizeof(cwd));
				setenv("pwd", cwd, 1);
			}
			else
			{
				if(errno = ENOENT)
				{
					printErrorMessage("komut cd: ");
					printf("%s:", parsedCommand[1]);
					printf(" dizin veya dosya bulunamadı.");
				}
				else
				{
					printErrorMessage("komut cd");
				}
			}
		}
		else if(strcmp(parsedCommand[0], "showpid") == 0)
		{
			for(int i = 0; i < pidCount; i++)
			{
				printf("%d\n", pidList[i]);
			}
		}
		else
		{
			runCommand(parsedCommand);
		}
	}
}

char** parseInput(char *command) 
{
	char** parsedArr = NULL;
	int spaceCount = 0;

	char* ptr;
	ptr = strtok(command, " ");
	
	while (ptr != NULL) 
	{
  		parsedArr = realloc(parsedArr, sizeof(char*) * ++spaceCount);

  		if (parsedArr == NULL)
  			exit(EXIT_FAILURE);

  		parsedArr[spaceCount - 1] = ptr;
  		ptr = strtok(NULL, " ");
	}
	parsedArr = realloc(parsedArr, sizeof (char*) * (spaceCount + 1));
	parsedArr[spaceCount] = NULL;

	if(spaceCount > 10)
	{
		printErrorMessage("Komut en fazla 10 kelimeden oluşabilir. ");
		printf("Gelen %d\n", spaceCount);
		parsedArr[0] = NULL;
	}

	return parsedArr;
}

int runCommand(char** args)
{
	pid_t child_pid = fork();
	int child_status;

	if(child_pid == 0) // Child
	{
		execvp(args[0], args);

        printErrorMessage("Komut icra edilemiyor.");
		exit(EXIT_FAILURE);
	}
	else // Parent
	{
		do {
        	pid_t w = waitpid(child_pid, &child_status, WUNTRACED | WCONTINUED);
        	if (w == -1) {
        	    printErrorMessage("Waitpid hatası.");
				kill(child_pid, SIGTERM);
				return -1;
        	}
        } while (!WIFEXITED(child_status) && !WIFSIGNALED(child_status));

		pidList = realloc(pidList, sizeof(pid_t) * (pidCount + 1));
		pidList[pidCount++] = child_pid;

        return child_status;
	}
}

void printErrorMessage(char* message)
{
	COLOR("Hata: ", COLOR_B_RED);
	printf(message);
}