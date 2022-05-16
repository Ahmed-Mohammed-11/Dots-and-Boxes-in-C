#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "AI.h"


int beginTime = 0,time1;
int load_time ;
int minutes = 0;
int seconds = 0;
int score1=0 , score2=0 ;
char user_1[50] = {} , user_2[50] = {} ;
int user_1namelen , user_2namelen ;
int size_r , size_c ;
int no_undo = 0 ;
int player1Move = 0 ;
int player2Move = 0 ;
int AI_v ;
static int load_check = 0;
int file_number ;
int load_checker = 0 ;
int total_lines ;

void red(){
        printf("\033[0;31m");
}
void blue(){
        printf("\033[0;34m");
}
void yellow(){
        printf("\033[0;33m");
}
void green(){
        printf("\033[0;32m");
}
void default_color(){
        printf("\033[0;37m");
}

int readInt(){
    int i , r=0 , s  , len ;  /* r is the Integer returned | s is the result of the string | len is length of the string */
    char readStr[1000] ;
    gets(readStr);
    len=strlen(readStr);
    if(len>2){return -1 ;}
    else{
    for(i=0;readStr[i]!='\0';i++ ){
        if(47<readStr[i] && readStr[i]<58){
            s=readStr[i]-48;
        }else{
            return -1 ;
        }
        r=r*10+s;
    }
    return r ;
    }
}


/* function to check the boxes */
void checkBox(int row , int col ,int size_r , int size_c , char boxArray[size_r][size_c] , int player_turn , char mainArray[size_r][size_c] , int *check , int noofmoves , int total_lines , int grid_history[total_lines][7] ){
    // check if the move is vertical or horizontal .
    if(row%2==0)        // the move is horizontal , we will check the upper and the lower boxes ,
    {
        if(row+2<size_r) //we will check the lower box
        {
            if(boxArray[row+2][col]==mainArray[row+2][col]){
                if(boxArray[row+1][col-1]==mainArray[row+1][col-1]){
                     if(boxArray[row+1][col+1]==mainArray[row+1][col+1]){
                            if(player_turn==1){

                                boxArray[row+1][col]='A';
                                score1++;
                                //*player_turn=*player_turn+1;
                            }else{

                                boxArray[row+1][col]='B';
                                score2++;
                                //*player_turn=*player_turn+1;
                                }
                                grid_history[noofmoves][3]=row+1;
                                grid_history[noofmoves][4]=col;
                                *check=*check+1;
                     }
                }
            }

        }
        if(row-2>=0)  //we will check the upper box
        {
            if(boxArray[row-2][col]==mainArray[row-2][col]){
                if(boxArray[row-1][col-1]==mainArray[row-1][col-1]){
                    if(boxArray[row-1][col+1]==mainArray[row-1][col+1]){
                            if(player_turn%2==1){
                                boxArray[row-1][col]='A';
                                score1++;
                                //*player_turn=*player_turn+1;
                            }else{
                                boxArray[row-1][col]='B';
                                score2++;
                                //*player_turn=*player_turn+1;
                                }
                                grid_history[noofmoves][5]=row-1;
                                grid_history[noofmoves][6]=col;
                                *check=*check+1;
                    }
                }
            }

        }
        }
        else     // the move is vertical , we will check the right and the left boxes .
        {
            if(col+2<size_c)   //we will check the right box .
            {
                if(boxArray[row][col+2]==mainArray[row][col+2]){
                    if(boxArray[row-1][col+1]==mainArray[row-1][col+1]){
                        if(boxArray[row+1][col+1]==mainArray[row+1][col+1]){

                            if(player_turn%2==1){
                                boxArray[row][col+1]='A';
                                score1++;
                                //*player_turn=*player_turn+1;
                            }else{
                                boxArray[row][col+1]='B';
                                score2++;
                                //*player_turn=*player_turn+1;
                                }
                                grid_history[noofmoves][3]=row;
                                grid_history[noofmoves][4]=col+1;
                                *check=*check+1;
                        }
                    }
                }
            }
            if(col-2>=0)  //we will check the left box
            {
                if(boxArray[row][col-2]==mainArray[row][col-2]){
                    if(boxArray[row-1][col-1]==mainArray[row-1][col-1]){
                        if(boxArray[row+1][col-1]==mainArray[row+1][col-1]){
                            if(player_turn%2==1){
                                boxArray[row][col-1]='A';
                                score1++;
                            }else{
                                boxArray[row][col-1]='B';
                                score2++;
                                }
                                grid_history[noofmoves][5]=row;
                                grid_history[noofmoves][6]=col-1;
                                *check=*check+1;
                        }
                    }
                }
            }
        }
    }

void undo(int *player_turn , int no_of_moves,int total_lines , int grid_history[total_lines][7] ,int size_r , int size_c , char boxArray[size_r][size_c] , char movesPlayed[size_r+1][size_c+1] ) {
        int row , col , box_r1 , box_r2 , box_c1 , box_c2 ;
        *player_turn=grid_history[no_of_moves-1][0];
        row=grid_history[no_of_moves-1][1];
        col=grid_history[no_of_moves-1][2];
        box_r1=grid_history[no_of_moves-1][3];
        box_c1=grid_history[no_of_moves-1][4];
        box_r2=grid_history[no_of_moves-1][5];
        box_c2=grid_history[no_of_moves-1][6];


 boxArray[row][col] = ' ';
        movesPlayed[row][col] = '0';
        if(*player_turn==1){
             player1Move--;
        }else{
             player2Move--;
        }
        if((box_r1!=0)&&(box_c1!=0)){

            boxArray[box_r1][box_c1] = ' ';
            grid_history[no_of_moves-1][3]=0;
            grid_history[no_of_moves-1][4]=0;
           if(*player_turn == 1){
                score1 -= 1;
           }else{
                score2 -= 1;
           }

        }if((box_r2!=0)&&(box_c2!=0)){

            boxArray[box_r2][box_c2] = ' ';
            grid_history[no_of_moves-1][5]=0;
            grid_history[no_of_moves-1][6]=0;
            if(*player_turn == 1){
                score1 -= 1;
           }else{
                score2 -= 1;
           }
        }
    }


void loading_function(int *noofmoves , int *player1Move , int *player2Move , int *score1 , int *score2 ,int total_lines , int *player_turn ,int size_r , int size_c, char movesPlayed[size_r+1][size_c+1] , int grid_history[total_lines][7] , char boxArray[size_r][size_c] , char user_1[], char user_2[] , int AI_v , int file_number){
  FILE *file;
  int i , j ;
  if(file_number == 1){
    file=fopen("1.bin","rb");
  }else if(file_number == 2){
    file=fopen("2.bin","rb");
  }else{
    file=fopen("3.bin","rb");
  }

  fscanf(file , "%d\n" , AI_v);
  fscanf(file, "%d\n" , &size_r);
  fscanf(file, "%d\n" , &size_c);
  fscanf(file , "%d\n" , noofmoves);
  fscanf(file , "%d\n" , player1Move);
  fscanf(file , "%d\n" , player2Move);
  fscanf(file , "%d\n" , score1);
  fscanf(file , "%d\n" , score2);
  fscanf(file , "%d\n" , player_turn);
  for(i = 0 ; i < size_r+1 ; i ++){
    for(j = 0 ; j < size_c+1 ; j ++){
      fscanf(file , "%d " , movesPlayed[i][j]);
    }fscanf(file , "\n");
  }
  for(i = 0 ; i < total_lines ; i ++){
    for(j = 0 ; j < 7 ; j ++){
      fscanf(file , "%d " , grid_history[i][j]);
    }fscanf(file , "\n");
  }for(i = 0 ; i < size_r ; i ++){
    for(j = 0 ; j < size_c ; j ++){
      fscanf(file , "%c " , boxArray[i][j]);
    }fscanf(file , "\n");
  }
  fscanf(file , "%s\n" , user_1);
  fscanf(file, "%s\n" , user_2);
  fclose(file);
}


void redo (int *player_turn , int no_of_moves,int total_lines , int grid_history[total_lines][7] ,int size_r , int size_c , char boxArray[size_r][size_c] , char movesPlayed[size_r+1][size_c+1],char mainArray[size_r][size_c] ,int *check ){
        int row , col  ;
        char h=205 ,v=186 ;
        *player_turn=grid_history[no_of_moves][0];
        row=grid_history[no_of_moves][1];
        col=grid_history[no_of_moves][2];
        if(*player_turn==1){
             player1Move++;
        }else{
             player2Move++;
        }
        if((row%2==0)&&(col%2!=0)){
                //system("cls");
                boxArray[row][col]=h;
                if(*player_turn==1){
                    movesPlayed[row][col]='1';
                }else{
                    movesPlayed[row][col]='2';
                }
                checkBox(row,col,size_r,size_c,boxArray,*player_turn,mainArray,&*check,no_of_moves,total_lines,grid_history);

        }else if((row%2!=0)&&(col%2==0)){
                //system("cls");
                boxArray[row][col]=v;
                if(*player_turn==1){
                    movesPlayed[row][col]='1';
                }else{
                    movesPlayed[row][col]='2';
                }
               checkBox(row,col,size_r,size_c,boxArray,*player_turn,mainArray,&*check,no_of_moves,total_lines,grid_history);
        }
    }

void printBox(int size_r ,int size_c ,char boxArray[size_r][size_c],char movesPlayed[size_r+1][size_c+1]){

    int i , j ;
    char h=205 ,v=186 ,dot=254 ,sp=' ' ;
    printf("\n\n\t\t\t\t  ");
    for(i=0;i<size_c;i++){
        if(i==0){printf(" ");}
        if(i<8){
            printf("%d ",i+1);
        }else{
            printf("%d",i+1);
            }
    }
    printf("\n\t\t\t\t");
    for(i=0;i<size_r;i++){
            if(i<9){
             printf("%d  ",i+1);
            }else{
              printf("%d ",i+1);
            }
            for(j=0;j<size_c;j++){  //printf("%c ",boxArray[i][j]);
                if((i%2==0)&&(j%2==0)){
                     if((movesPlayed[i][j+1]=='1')||(movesPlayed[i][j+1]=='2')){
                        printf("%c",boxArray[i][j]);
                     }else{
                        printf("%c ",boxArray[i][j]);
                     }

                }else if((i%2==1)&&(j%2==0)){
                    if((boxArray[i][j+1]=='A')||(boxArray[i][j+1]=='B')){
                      if(movesPlayed[i][j]=='1'){
                          blue();
                          printf("%c",v);
                          default_color();
                      }else if(movesPlayed[i][j]=='2'){
                          red();
                          printf("%c",v);
                          default_color();
                      }else{
                          printf("%c ",boxArray[i][j]);
                      }
                    }else{
                        if(movesPlayed[i][j]=='1'){
                          blue();
                          printf("%c ",v);
                          default_color();
                      }else if(movesPlayed[i][j]=='2'){
                          red();
                          printf("%c ",v);
                          default_color();
                      }else{
                          printf("%c ",boxArray[i][j]);
                      }

                    }
                }else if((i%2==0)&&(j%2==1)){
                    if(movesPlayed[i][j]=='1'){
                        blue();
                        printf("%c%c%c",h,h,h);
                        default_color();
                    }else if(movesPlayed[i][j]=='2'){
                        red();
                        printf("%c%c%c",h,h,h);
                        default_color();
                    }else{
                        printf("%c ",boxArray[i][j]);
                    }

                }else if((i%2==1)&&(j%2==1)){
                    if(boxArray[i][j]=='A'){

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE);
                        printf("   ");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED| FOREGROUND_INTENSITY);

                    }else if(boxArray[i][j]=='B'){

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED);
                        printf("   ");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED| FOREGROUND_INTENSITY );

                    }else{
                       printf("%c ",boxArray[i][j]);
                    }
                }
            }
        printf("\n\t\t\t\t");

    }
    printf("\n");
}



 void box(char user_1[] , char user_2[] , int size_r , int size_c , int AI_v , int file_number , int  load_checker , int total_lines){
     int count_box_r , row;
     int count_box_c , col;
     int check=0 ;
     char boxArray[size_r][size_c], mainArray[size_r][size_c] , movesPlayed[size_r+1][size_c+1] ;
     int i , j , player_turn=1 ,invalid=0 ;
     int game_on=1 , noofmoves=0   ;
     int grid_history[total_lines][7] ;

     char h=205 ,v=186 ,dot=254 ,sp=' ' ;  // dot=254 ,h=205 ,v=186 ; //h=61 ,v=124 ,dot=79 ;

     for(i=0;i<(size_r+1);i++){
         for(j=0;j<(size_c+1);j++){
             movesPlayed[i][j]='0';
         }
     }

     for(i=0;i<total_lines;i++){
        for(j=0;j<7;j++){
          grid_history[i][j]=0;
       }
     }


 for(count_box_r=0;count_box_r<size_r;count_box_r++){
             if(count_box_r%2==0){
             for(count_box_c=0;count_box_c<size_c;count_box_c++){
                     if(count_box_c%2==0){
                             boxArray[count_box_r][count_box_c]=dot;
                     }else{
                             boxArray[count_box_r][count_box_c]=sp;
                     }
             }
             }else{
                 for(count_box_c=0;count_box_c<size_c;count_box_c++){
                    boxArray[count_box_r][count_box_c]=sp;
             }
         }
     }
     printBox(size_r,size_c,boxArray,movesPlayed);

     for(count_box_r=0;count_box_r<size_r;count_box_r++){
             if(count_box_r%2==0){
             for(count_box_c=0;count_box_c<size_c;count_box_c++){
                     if(count_box_c%2==0){
                             mainArray[count_box_r][count_box_c]=dot;
                     }else{
                             mainArray[count_box_r][count_box_c]=h;
                     }
             }
             }else{
                 for(count_box_c=0;count_box_c<size_c;count_box_c++){
                     if(count_box_c%2==0){
                             mainArray[count_box_r][count_box_c]=v;
                     }else{
                             mainArray[count_box_r][count_box_c]=' ';
                     }
         }
     }
     }
     if(load_checker == 1){
       loading_function(&noofmoves , &player1Move , &player2Move , &score1 , &score2 , total_lines , &player_turn , size_r , size_c, movesPlayed ,  grid_history ,  boxArray,  user_1, user_2 , AI_v , file_number);
     }else{
     beginTime=time(NULL);
     while(game_on){
             check=0;
             invalid=0;
             time1=time(NULL);
             time1=time1-beginTime;
             minutes=time1/60;
             seconds=(time1%60);
     if(player_turn==1){
         blue();
         printf(" %s played moves : %d\t\t\t\t\t",user_1,player1Move);
         red();
         printf(" %s played moves : %d\n",user_2,player2Move);
         blue();
         printf(" score : %d \t\t\t\t\t\t\t", score1 );
         red();
         printf(" score : %d \n", score2 );
         default_color();
         printf("\t\t\t\tTime is --> %2d : %2d \n",minutes,seconds);
         printf("  Choose one of these\n");
         printf("your guide through game\nEnter --> (1,1) to undo the previous move\nEnter --> (2,2) to redo the move\nEnter --> (3,3) to exit the game\n");
         blue();
         printf("Enter The Row :");
         row=readInt()-1;  //Input Row
         printf("Enter The Col :");
         col=readInt()-1;  //Input Col
         default_color();
     }else if ((player_turn==2)&&(AI_v==0)){
         blue();
         printf(" %s played moves : %d\t\t\t\t\t",user_1,player1Move);
         red();
         printf(" %s played moves : %d\n",user_2,player2Move);
         blue();
         printf(" score : %d \t\t\t\t\t\t\t", score1 );
         red();
         printf(" score : %d \n", score2 );
         default_color();
         printf("\t\t\t\tTime is --> %2d : %2d \n",minutes,seconds);
         default_color();
         printf("  Choose one of these\n");
         printf("your guide through game\nEnter --> (1,1) to undo the previous move\nEnter --> (2,2) to redo the move\nEnter --> (3,3) to exit the game\n");
         red();
         printf("Enter The Row :");
         row=readInt()-1;  //Input Row
         printf("Enter The Col :");
         col=readInt()-1;  //Input Col
         default_color();
     }else if ((player_turn==2)&&(AI_v==1)){
         blue();
         printf(" %s played moves : %d\t\t\t\t\t",user_1,player1Move);
         red();
         printf(" %s played moves : %d\n",user_2,player2Move);
         blue();
         printf(" score : %d \t\t\t\t\t\t\t", score1 );
         red();
         printf(" score : %d \n", score2 );
         default_color();
         printf("\t\t\t\tTime is --> %2d : %2d \n",minutes,seconds);
         default_color();
         printf("  Choose one of these\n");
         printf("your guide through game\nEnter --> (1,1) to undo the previous move\nEnter --> (2,2) to redo the move\nEnter --> (3,3) to exit the game\n");

         AI_guide(&row ,&col, player_turn, noofmoves,total_lines , grid_history , size_r ,size_c ,boxArray,mainArray , movesPlayed  ,AI_v);

     }
     if((0<=row)&&(row<size_r)&&(0<=col)&&(col<size_c)){
         if((boxArray[row][col]==h)||(boxArray[row][col]==v)){
              system("cls");
              invalid=1;
              printBox(size_r,size_c,boxArray,movesPlayed);

              printf("Invalid Move \n");

         }else{
            if((row==0)&&(col==0)) {
                  if(noofmoves<=0){
                    invalid=1;
                    system("cls");
                    red();
                    printf("there is no available undo moves\n");
                    default_color();
                    system("pause");
                    printBox(size_r,size_c,boxArray,movesPlayed);
                  }else if ((noofmoves>0)&&(AI_v==0)){
                    system("cls");
                    invalid=1;
                    undo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed );
                    noofmoves--;
                    no_undo++;
                    printBox(size_r,size_c,boxArray,movesPlayed);
                   }else if((noofmoves>0)&&(AI_v==1)){

                    while(1){
                    if(grid_history[noofmoves-1][0]==1){
                    system("cls");
                    invalid=1;
                    undo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed );
                    noofmoves--;
                    no_undo++;
                    printBox(size_r,size_c,boxArray,movesPlayed);
                    break;
                    }else{
                    system("cls");
                    invalid=1;
                    undo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed );
                    noofmoves--;
                    no_undo++;
                    printBox(size_r,size_c,boxArray,movesPlayed);}
                    }
                   }

            }else if((row==1)&&(col==1)){
                 if((no_undo!=0)&&(AI_v==0)){
                     system("cls");
                     no_undo--;
                     redo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed ,mainArray,&check);
                     noofmoves++;
                     printBox(size_r,size_c,boxArray,movesPlayed);
                 }else if((no_undo!=0)&&(AI_v==1)){
                  while(1){
                    if(grid_history[noofmoves][0]==1){
                     system("cls");
                     redo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed ,mainArray,&check);
                     no_undo--;
                     noofmoves++;
                     printBox(size_r,size_c,boxArray,movesPlayed);
                     break;
                    }else{
                    system("cls");

                     redo(&player_turn ,noofmoves,total_lines ,grid_history , size_r , size_c , boxArray , movesPlayed ,mainArray,&check);
                     no_undo--;
                     noofmoves++;
                     printBox(size_r,size_c,boxArray,movesPlayed);
                    }

                    }
                 }else{
                    invalid=1;
                    system("cls");
                    red();
                    printf("there is no available redo moves\n");
                    default_color();
                    system("pause");
                    printBox(size_r,size_c,boxArray,movesPlayed);
                  }

          }else if((row==2)&&(col==2)){
               exit(0);
          } //next improvements to save the game and load it later
                 /*else if((row==3)&&(col==3)){
            int saving_number;
            printf("Enter the file number that you want to save in {1 , 2 or 3} :");
            while(1){
                saving_number = readInt();
                if (saving_number == 1 ||  saving_number == 2 || saving_number == 3){
                    FILE *filename ;
                    if(saving_number == 1){
                       filename = fopen("1.bin" , "wb");
                    }
                    if(saving_number == 2){
                       filename = fopen("2.bin" , "wb");
                    }
                    if(saving_number == 3){
                        filename = fopen("3.bin" , "wb");
                    }
                    fprintf(filename , "%d\n" , AI_v);
                    fprintf(filename , "%d\n" , size_r);
                    fprintf(filename , "%d\n" , size_c);
                    fprintf(filename , "%d\n" , noofmoves);
                    fprintf(filename , "%d\n" , player1Move);
                    fprintf(filename , "%d\n" , player2Move);
                    fprintf(filename , "%d\n" , score1);
                    fprintf(filename , "%d\n" , score2);
                    fprintf(filename , "%d\n" , player_turn);
                    for(i = 0 ; i < size_r+1 ; i ++){
                      for(j = 0 ; j < size_c+1 ; j ++){
                        fprintf(filename , "%d " , movesPlayed[i][j]);
                      }fprintf(filename , "\n");
                    }
                    for(i = 0 ; i < total_lines ; i ++){
                      for(j = 0 ; j < 7 ; j ++){
                        fprintf(filename , "%d " , grid_history[i][j]);
                      }fprintf(filename , "\n");
                    }for(i = 0 ; i < size_r ; i ++){
                      for(j = 0 ; j < size_c ; j ++){
                        fprintf(filename , "%c " , boxArray[i][j]);
                      }fprintf(filename , "\n");
                    }
                    fprintf(filename , "%s\n" , user_1);
                    fprintf(filename , "%s\n" , user_2);
                    fclose(filename);
                    printf("  game was saved to %d.bin\n", saving_number);
                    break;
                }else{
                    printf("is not existing file\n");
                    printf("Enter the file number that you want to save in {1 , 2 or 3} :");
              }
            }break ;
             exit(0);*/

          }else if((row%2==0)&&(col%2!=0)){
             system("cls");
             boxArray[row][col]=h;
             if(player_turn==1){
                 movesPlayed[row][col]='1';
                 player1Move++;
             }else{
                 movesPlayed[row][col]='2';
                 player2Move++;
             }
             checkBox(row,col,size_r,size_c,boxArray,player_turn,mainArray,&check,noofmoves,total_lines,grid_history);
             printBox(size_r,size_c,boxArray,movesPlayed);
             //player_turn++;
             grid_history[noofmoves][0]=player_turn;
             grid_history[noofmoves][1]=row;
             grid_history[noofmoves][2]=col;
             noofmoves++;
             no_undo=0;

        }else if((row%2!=0)&&(col%2==0)){
             system("cls");
             boxArray[row][col]=v;
             if(player_turn%2==1){
                 movesPlayed[row][col]='1';
                 player1Move++;
             }else{
                 movesPlayed[row][col]='2';
                 player2Move++;
             }
             checkBox(row,col,size_r,size_c,boxArray,player_turn,mainArray,&check,noofmoves,total_lines,grid_history);
             printBox(size_r,size_c,boxArray,movesPlayed);
             //player_turn++;
             grid_history[noofmoves][0]=player_turn;
             grid_history[noofmoves][1]=row;
             grid_history[noofmoves][2]=col;
             noofmoves++;
             no_undo=0;

        }else{
            system("cls");
            invalid=1;
            printBox(size_r,size_c,boxArray,movesPlayed);
            printf("Invalid\n");

        }

         }
     }else{
         system("cls");
         invalid=1;
         printBox(size_r,size_c,boxArray,movesPlayed);
         printf("Invalid input\n");

     }

     while(1){
        if(invalid==1){
                 break;
        }else if(player_turn==1){
             if(check>0){
                 player_turn=1;
                 break;
             }else{
                 player_turn=2;
                 break;
             }
         }else if(player_turn==2){
             if(check>0){
                 player_turn=2;
                 break;
             }else{
                 player_turn=1;
                 break;
             }
         }



     }
      if(noofmoves==total_lines){
             game_on=0;
         }
    }

    //printf("%d\n",no_undo);
    if(total_lines == noofmoves){
       game_on = 0 ;
       if(score1 == score2){
         yellow();
         printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t    --> Oops , ...   IT'S A TIE\n");
         default_color();
         printf("\n\t\t\t\t\t\t\t\t\t  ");
         system("pause");
       }else if(score1 > score2){
         blue();
         printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t    --> %s WINS THE GAME\n" , user_1);
         default_color();
         printf("\n\t\t\t\t\t\t\t\t\t  ");
         system("pause");
       }else if(score2 > score1){
         red();
         printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t    --> %s WINS THE GAME\n" , user_2);
         default_color();
         printf("\n\t\t\t\t\t\t\t\t\t  ");
         system("pause");
       }
    }
  }
}

void input_main(int user_input){
    if(user_input == 1){
        int input_for2players ;
        system("cls") ;
        default_color();
        printf("\n\n\t\t 1) level#1 --> easy \n"
               "\t\t 2) level#2 --> normal \n"
               "\t\t 3) level#3 --> hard \n");
        input_for2players=readInt();
        while(1){
          if (input_for2players == 1){
            AI_v = 0 ;
            system("cls") ;
            size_r = 5 ;
            size_c = 5 ;
            blue();
            printf("What is your name player1 : " );
            gets(user_1);
            red();
            printf("What is your name player2 : ");
            gets(user_2);
            default_color();
            system("cls");
            total_lines = 12;
            box( user_1 , user_2 , size_r , size_c , AI_v , file_number, load_checker , total_lines);
            break ;
          }else if (input_for2players == 2){
            system("cls") ;
            size_r = 9 ;
            size_c = 9 ;
            blue();
            printf("What is your name player1 : " );
            gets(user_1);
            red();
            printf("What is your name player2 : ");
            gets(user_2);
            default_color();
            system("cls");
            total_lines = 40 ;
            box(user_1 , user_2 , size_r , size_c , AI_v , file_number, load_checker , total_lines);
            break ;
          }else if(input_for2players == 3){
            system("cls") ;
            size_r = 15 ;
            size_c = 15 ;
            blue();
            printf("What is your name player1 : " );
            gets(user_1);
            red();
            printf("What is your name player2 : ");
            gets(user_2);
            default_color();
            system("cls");
            total_lines = 98 ;
            box(user_1 , user_2 , size_r , size_c, AI_v , file_number, load_checker , total_lines);
            break ;
          }else {
            printf("invalid input \n");
            system("cls");
            printf("enter valid input please :) \n");
            input_for2players=readInt();
          }
        }
      }else if(user_input == 2){
            AI_v = 1 ;
            int input_vscomputer ;
            system("cls") ;
            default_color();
            printf("\n\n\t\t 1) level#1 --> easy \n"
                   "\t\t 2) level#2 --> normal \n"
                   "\t\t 3) level#3 --> hard \n");
            input_vscomputer=readInt();
            while(1){
              if (input_vscomputer == 1){
                size_r = 5 ;
                size_c = 5 ;
                blue();
                printf("What is your name : " );
                gets(user_1);
                strcpy(user_2 , "computer");
                default_color();
                total_lines = 12 ;
                box( user_1 , user_2 ,  size_r , size_c , AI_v , file_number , load_checker , total_lines);
                break ;
              }else if (input_vscomputer == 2){
                size_r = 9 ;
                size_c = 9 ;
                blue();
                printf("What is your name : " );
                gets(user_1);
                strcpy(user_2 , "computer");
                default_color();
                total_lines = 40 ;
                box(user_1 ,user_2 , size_r , size_c ,AI_v , file_number , load_checker , total_lines);
                break ;
              }else if(input_vscomputer== 3){;
                size_r = 15 ;
                size_c = 15 ;
                blue();
                printf("What is your name : " );
                gets(user_1);
                strcpy(user_2 , "computer");
                default_color();
                total_lines = 98 ;
                box(user_1 , user_2 , size_r , size_c , AI_v , file_number , load_checker , total_lines);
                break ;
              }
               else {
                printf("invalid input \n");
                system("cls");
                printf("enter valid input please :) \n");
                input_vscomputer=readInt();

              }
            }
          }else if(user_input == 3){
             int file_number;
             printf("please enter the number of file you want to open from saves {choose 1 , 2 or 3} : ");
             file_number = readInt();
             load_checker = 1 ;
             box(user_1 , user_2 , size_r , size_c , AI_v , file_number , load_checker , total_lines);
    }else if(user_input == 5){
         default_color();
         system("exit");
    }
}
