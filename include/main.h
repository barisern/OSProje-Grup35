#ifndef MAIN_H 
#define MAIN_H

#define COLOR_B_RED     "\x1b[1;31m"
#define COLOR_GREEN     "\x1b[22;32m"
#define COLOR_YELLOW    "\x1b[22;33m"
#define COLOR_BLUE      "\x1b[22;34m"
#define COLOR_B_BLUE_BR "\x1b[1;94m"
#define COLOR_MAGENTA   "\x1b[22;35m"
#define COLOR_CYAN      "\x1b[22;36m"
#define COLOR_B_WHITE   "\x1b[1;37m"
#define COLOR_RESET     "\x1b[22;0m"
#define COLOR(X, COLOR)  printf("%s%s%s", COLOR, X, COLOR_RESET);

void prompt();
void runUserInput();

char** parseInput(char*);
int runCommand(char** args);
void printErrorMessage(char* message);

#endif