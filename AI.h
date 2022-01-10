#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void AI_guide(int *row , int *col, int player_turn, int noofmoves, int total_lines ,int grid_history[total_lines][7] ,int size_r ,int size_c , char boxArray[size_r][size_c] ,char mainArray[size_r][size_c] ,char movesPlayed[size_r+1][size_c+1] , int AI_v){//&row,&col,size_r,size_c,boxArray,movesPlayed
 int invalid=0 ,i=0 , j=0 , check=0 ,valid_move=0 ;
 char h=205 ,v=186 ,dot=254 ,sp=' ' ;  //mainArray  noofmoves , total_lines , grid_history
 printf("you are in AI mode");
 for(i=0;i<size_r;i++){
   for(j=0;j<size_c;j++){
           invalid=0;
           //TO CHOOSE RANDOME MOVE STARTING FROM (0,0) TO (5,5) :
           if(((i%2==1)&&(j%2==1))||(boxArray[i][j]==dot)||((boxArray[i][j]==h)||(boxArray[i][j]==v))){
                   invalid=1;
           }
           if(((i%2==0)&&(j%2!=0))&&(!invalid)){
                   valid_move=1;
                   break ;
           }else if(((i%2!=0)&&(j%2==0))&&(!invalid)){
                   valid_move=1;
                   break ;
           }
   }
   if(valid_move==1){
       break;
   }

 }
 *row=i;
 *col=j;

}
