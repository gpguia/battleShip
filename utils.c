#include "utils.h"

bool checkArgs(int argc, char *argv[]){
    if(argc == 1)
        return false;
    if(argc == 3 && isdigit(*argv[1]) && isdigit(*argv[2])){
        return true;
    }

    printErrorMsg("If you are using args, please insert 2 values like: 20 20");
    return false;
}

void setNrmColor(){
    printf(KNRM);
}

void printErrorMsg(char *msg){
    printf(KRED "%s\n",msg);
    setNrmColor();
}

void printErrorMsgInt(char *msg, int num){
    printf(KRED "%s %d\n",msg,num);
    setNrmColor();
}

void printSuccessMsg(char * msg){
    printf(KGRN "%s\n",msg);
    setNrmColor();
}

void printWarningMsg(char *msg){
    printf(KYEL "%s\n",msg);
    setNrmColor();
}

void printWarningMsgInt(char *msg, int num){
    printf(KYEL "%s %d\n",msg,num);
    setNrmColor();
}


void deBug(char *msg){
    printf(KMAG "%s\n",msg);
    setNrmColor();
}

void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}