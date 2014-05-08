#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include "2048.h"
//#include "board.c"


int line_vector_test(int i1,int i2,int i3,int i4,char *msg,
                int o1,int o2,int o3,int o4, int (*func)(int,int *))
{
  int list[4]={i1,i2,i3,i4};
  if (msg) printf("%s - ",msg); 
  else {
    printf("Tilting {%d,%d,%d,%d} left yields {%d,%d,%d,%d} - ",
             i1,i2,i3,i4,o1,o2,o3,o4);
  }
  fflush(stdout);
  func(4,list);
  if ((list[0]!=o1)||(list[1]!=o2)||(list[2]!=o3)||(list[3]!=o4))
    {
      printf("FAILED: {%d,%d,%d,%d} became {%d,%d,%d,%d} instead of"
             " {%d,%d,%d,%d}\n",
             i1,i2,i3,i4,list[0],list[1],list[2],list[3],
             o1,o2,o3,o4);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
  
}

int ttl_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_left);
}

int test_tilt_left()
{
  int e=0;
  e|=ttl_vector(0,0,0,0,"Empty list is empty after shift",0,0,0,0);
  e|=ttl_vector(1,0,0,0,"Value on left stays on left after shift",1,0,0,0);
  e|=ttl_vector(0,0,0,1,"Value on right shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector(0,0,1,0,"Value in middle shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttl_vector(1,1,1,1,"Combinations don't cascade",2,2,0,0);
  e|=ttl_vector(0,0,1,1,"1's in location 3 and 4 cascade",2,0,0,0);
  e|=ttl_vector(4,0,1,1,"Cascade stops at appropriate place",4,2,0,0);
  e|=ttl_vector(2,0,1,1,"Cascades only one step at a time",2,2,0,0);
  
  //my new tests pogs0004
  e|=ttl_vector(0,2,0,2,"Values cascade and combine",4,0,0,0);
  e|=ttl_vector(2,2,2,2,"All 2's combine",4,4,0,0);

  return e;
}


//2x2 board test ////////////////////

int board_vector_test(int i1,int i2,int i3,int i4,char *msg,
                      int o1,int o2,int o3,int o4, int (*func)(int,int **))
{
  int **board=alloca(2*sizeof(int*));
  board[0]=alloca(sizeof(int)*2);
  board[1]=alloca(sizeof(int)*2);
  board[0][0]=i1; board[1][0]=i2; board[0][1]=i3; board[1][1]=i4;

  if (msg) printf("%s - ",msg); 
  else {
    printf("Board operation on {{%d,%d},{%d,%d}} yields {{%d,%d},{%d,%d}} - ",
             i1,i2,i3,i4,o1,o2,o3,o4);
  }
  fflush(stdout);
  func(2,board);
  if ((board[0][0]!=o1)||(board[1][0]!=o2)
      ||(board[0][1]!=o3)||(board[1][1]!=o4))
    {
      printf("FAILED: {{%d,%d},{%d,%d}} became {{%d,%d},{%d,%d}} instead of"
             " {{%d,%d},{%d,%d}}\n",
             i1,i2,i3,i4,
             board[0][0],board[1][0],board[0][1],board[1][1],
             o1,o2,o3,o4);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

//3x3 board test ////////////////////

int board3_vector_test(int i1,int i2,int i3,int i4,int i5,
                       int i6,int i7,int i8,int i9,char *msg,
                       int o1,int o2,int o3,int o4,int o5,
                       int o6,int o7,int o8,int o9,
                       int (*func)(int,int **))
{
  int **board=alloca(3*sizeof(int*));
  board[0]=alloca(sizeof(int)*3);
  board[1]=alloca(sizeof(int)*3);
  board[2]=alloca(sizeof(int)*3);
  board[0][0]=i1; board[1][0]=i2; board[2][0]=i3;
  board[0][1]=i4; board[1][1]=i5; board[2][1]=i6;
  board[0][2]=i7; board[1][2]=i8; board[2][2]=i9;

  if (msg) printf("%s - ",msg); 
  else {
    printf("Board operation on {{%d,%d,%d},...} yields {{%d,%d,%d}...} - ",
             i1,i2,i3,o1,o2,o3);
  }
  fflush(stdout);
  func(3,board);
  if (
      (board[0][0]!=o1)||(board[1][0]!=o2)||(board[2][0]!=o3)||
      (board[0][1]!=o4)||(board[1][1]!=o5)||(board[2][1]!=o6)||
      (board[0][2]!=o7)||(board[1][2]!=o8)||(board[2][2]!=o9)
      )
    {
     printf("FAILED: {{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}} became {{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}} instead of"
             " {{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}}\n",
             i1,i2,i3,i4,i5,i6,i7,i8,i9,
             board[0][0],board[1][0],board[2][0],
             board[0][1],board[1][1],board[2][1],
             board[0][2],board[1][2],board[2][2],
             o1,o2,o3,o4,o5,o6,o7,o8,o9);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

int main(int argc,char **argv)
{
  int e=0;
  e|=test_tilt_left();

// 2x2 rotate 90 tests /////////////////////////////////////
  board_vector_test(1,2,3,4,"Rotate 2x2 board right (+90)",3,1,4,2,board_rotate_90);  

// 3x3 rotate 90 tests /////////////////////////////////////
  board3_vector_test(1,2,3,4,5,6,7,8,9,"Rotate 3x3 +90 R",7,4,1,8,5,2,9,6,3,board_rotate_90);
  return e;

}
