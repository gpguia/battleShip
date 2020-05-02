#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>



#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

bool checkArgs(int argc, char *argv[]);


// Print functions
void setNrmColor();
void printErrorMsg(char *msg);
void printErrorMsgInt(char *msg, int num);
void printSuccessMsg(char * msg);
void printWarningMsg(char *msg);
void printWarningMsgInt(char *msg, int num);
void deBug(char *msg);
void clearScreen();