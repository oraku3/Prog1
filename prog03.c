#include <stdio.h>
#include <stdlib.h>

#define BLACK '1'
#define WHITE '0'

char **pbm_alloc(int, int);
void   pbm_free(char **,int, int);
char **pbm_read(int *, int *);
void   pbm_write(char **, int, int);
char **pbm_erode(char **, int , int);  /* エロージョンを行う関数 */
char **pbm_dilate(char **, int , int ); /* ダイレーションを行う関数 */

char *odata;

int main(){
  char **pbm1, **pbm2;
  int ix,iy;
  
  pbm1 = pbm_read(&ix,&iy);
  if(pbm1==NULL){
    fprintf(stderr,"Invlid image format.");
    exit(1);
  }
  
#ifdef ERODE
  pbm2=pbm_erode(pbm1,ix,iy);
  pbm_free(pbm1,ix,iy);
#elif DILATE
  pbm2=pbm_dilate(pbm1,ix,iy);
  pbm_free(pbm1,ix,iy);
#else
  pbm2=pbm1;
#endif
  
  /* 画像を書きだす */
  pbm_write(pbm2,ix,iy);
  /* 画像領域の解放 */
  pbm_free(pbm2,ix,iy);
  return 0;
}

char **pbm_alloc(int x, int y) {
  char **data;
  
  /* ２次元配列の作成 */
  data = (char **)malloc(y*sizeof(char *));
  odata = (char *)malloc(x*y*sizeof(char));
  if(odata == NULL){
    free(data);
    return NULL;
  }
  return data;
}

void  pbm_free(char **pbm, int x, int y) {
  int i;
  for (i = 0; i<y; i++)
    free(pbm[i]);
  free(pbm);
}

char **pbm_read(int *x, int *y){
  int i,j,x_size,y_size; 
  char **data;
  getchar();
  getchar();
  scanf("%d", &x_size);
  scanf("%d", &y_size);
  data = pbm_alloc(x_size,y_size);
  for(i = 0; i < y_size; i++){
    data[i] = odata + i*x_size;
  }
  for(i = 0; i < y_size; i++){
    for(j = 0; j < x_size; j++){
      if(scanf(" %c",&data[i][j]) != 1) break;
      if(data[i][j] != BLACK && data[i][j] != WHITE){
        free(data);
        return NULL;
      }
    }
  }
  *x = x_size;
  *y = y_size;
  return data;
}

void   pbm_write(char **pbm, int x, int y) {
  int i, j;
  /* 最初にP1とx,yの画素数を出力 */
  printf("P1\n");
  printf("%d %d\n", x, y);
  /* 実際のデータ出力 */
  for (i = 0; i < y; i++) {
    for (j = 0; j < x; j++) {
      printf("%c ", pbm[i][j]);
    }
    printf("\n");
  }
}

char **pbm_erode(char **pbm,int x,int y){
  char **data;
  char right,left,top,under;
  int i,j;  
  
  right = pbm[i][j+1];
  left = pbm[i][j-1];
  top = pbm[i-1][j];
  under = pbm[i+1][j];
  
  
  /*左端の時*/
  /*左上端の時*/
  for(i = 0; i < y; i++){
    for(j = 0; j < x; j++){
      if(j == 0){
        if(i == 0){
          if(pbm[i][j] == BLACK && right == BLACK && under == BLACK) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
        /*左下端の時*/
        else if(i == y-1){
          if(pbm[i][j] == BLACK && top == BLACK && right == BLACK) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
        else {
          if(pbm[i][j] == BLACK && top == BLACK && right == BLACK && under == BLACK) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
      }
      /*右端の時*/
      else if(j == x-1){
        /*右上端の時*/
        if(i == 0){
          if((pbm[i][j] == BLACK) && (left == BLACK) && (under==BLACK)) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
        /*右下端の時*/
        else if(i == y-1){
          if((pbm[i][j] == BLACK) && (top == BLACK) && (left==BLACK)) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
        else {
          if((pbm[i][j] == BLACK) && (top == BLACK) && (left == BLACK) && (under == BLACK)) data[i][j] = BLACK;
          else data[i][j] = WHITE;
        }
      }
      /*最上端の時*/
      else if((i == 0) && (j != 0) && (j != x-1)){
        if((pbm[i][j] == BLACK) && (left == BLACK) && (right==BLACK) && (under == BLACK)) data[i][j] = BLACK;
        else data[i][j] = WHITE;
      }
      /*最下端の時*/
      else if((i == y-1) && (j != x-1) && (j != 0)){
        if((pbm[i][j] == BLACK) && (left == BLACK) && (top==BLACK) && (right == BLACK)) data[i][j] = BLACK;
        else data[i][j] = WHITE;
      }
      /*それ以外の時*/
      else {
        if((pbm[i][j] == BLACK) && (left == BLACK) && (top==BLACK) && (right == BLACK) && (under == BLACK)) data[i][j] = BLACK;
        else data[i][j] = WHITE;
      }
    }
  }
  return data;
}

char **pbm_dilate(char **pbm,int x,int y){
  char **data;
  char right,left,top,under;
  int i,j;
  
  data = pbm_alloc(x,y);
  
  right = pbm[i][j+1];
  left = pbm[i][j-1];
  top = pbm[i-1][j];
  under = pbm[i+1][j];
  
  for(i = 0; i < y; i++){
    for(j = 0;j < x; j++){
      /*左端の時*/
      /*左上端の時*/
      if(j == 0){
        if(i == 0){
          if(pbm[i][j] == BLACK &&  (right == BLACK || under == BLACK)){
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
        /*左下端の時*/
        else if(i == y-1){
          if(pbm[i][j] == BLACK && (top == BLACK || right == BLACK)){
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
        else {
          if(pbm[i][j] == BLACK && (top == BLACK || right == BLACK || under == BLACK)) {
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
      }
      /*右端の時*/
      else if(j == x-1){
        /*右上端の時*/
        if(i == 0){
          if((pbm[i][j] == BLACK) && (left == BLACK || under==BLACK)){
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
        /*右下端の時*/
        else if(i == y-1){
          if((pbm[i][j] == BLACK) && (top == BLACK || left==BLACK)){
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
        else {
          if((pbm[i][j] == BLACK) && (top == BLACK || left == BLACK || under == BLACK)){
            data[i][j] = BLACK;
          }
          else data[i][j] = WHITE;
        }
      }
      /*最上端の時*/
      else if((i == 0) && (j != 0) && (j != x-1)){
        if((pbm[i][j] == BLACK) && (left == BLACK || right==BLACK || under == BLACK)){
          data[i][j] = BLACK;
        }
        else data[i][j] = WHITE;
      }
      /*最下端の時*/
      else if((i == y-1) && (j != x-1) && (j != 0)){
        if((pbm[i][j] == BLACK) && (left == BLACK || top==BLACK || right == BLACK)){
          data[i][j] = BLACK;
          data[i][j] = WHITE;
        }
      }
      /*それ以外の時*/
      else{
        if((pbm[i][j] == BLACK) && (left == BLACK || top==BLACK || right == BLACK || under == BLACK)) {
          data[i][j] = BLACK;
        }
        data[i][j] = WHITE;
      }
    }
  }
  return data;
}
