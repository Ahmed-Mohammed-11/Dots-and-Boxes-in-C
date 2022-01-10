#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "manual_functions.h"

int main()
{
    system("");
    /*main menu*/
    default_color();
    printf("\n\t\t\t\t\t\t\t\t\t Welcome To Dots&Boxes Game\n");
    printf("\n\t\t\t\t\t\t\t   Choose One Of These Modes By Typing Suitable Number\n\n");
    yellow();
    printf("\t\t\t\t\t\t\t\t\t  1) 2 Players\n");
    printf("\t\t\t\t\t\t\t\t\t  2) You VS Computer\n");
    printf("\t\t\t\t\t\t\t\t\t  3) Load a Game\n ");
    printf("\t\t\t\t\t\t\t\t\t  4) List of Top 10 players\n");
    printf("\t\t\t\t\t\t\t\t\t  5) Escape\n"
           "\t\t\t\t\t\t\t  _____________________________________________________\n\n");
    int user_input ;
    blue();
    printf("Enter the choice :");
    //user_input=readInt();
    while(5){
    user_input=readInt();
       if(1<=user_input && user_input <=5){
          input_main(user_input) ;
          break ;
       }else{
          red();
          printf("Invalid Choice \n");
          blue();
          printf("Enter the choice :");
       }
    }
    return 0;
}
