#if defined SWITCH
#include <stdio.h>
typedef struct{
  double x,y;
   } XY;

typedef struct{
  XY temp[3];
} TRY;
TRY TRY1,TRY2;

void InputShape(TRY);
int main(){
  TRY1 = InputShape(TRY1);
  TRY2 = InputShape(TRY2);
  return 0;
}
#endif
void InputShape(TRY try){
  printf("vertex 1: ");
  scanf("%lf%lf",&try.temp[0].x,&try.temp[0].y);
  printf("vertex 2: ");
  scanf("%lf%lf",&try.temp[1].x,&try.temp[1].y);
  printf("vertex 3: ");
  scanf("%lf%lf",&try.temp[2].x,&try.temp[2].y);
  return try;
}
