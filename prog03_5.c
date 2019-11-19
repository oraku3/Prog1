#Include <stdio.h>
#include <math.h>
#if defined SWITCH
typedef struct{
  double x,y;
   } XY;

typedef struct{
  XY temp[3];
} TRY;
TRY TRY1,TRY2;
TRY InputShape(TRY);
double GetArea(TRY);
int main(){
  TRY1 = InputShape(TRY1);
  GetArea(TRY1);
  return 0;
}
TRY InputShape(TRY try){
  printf("vertex 1: ");
  scanf("%lf%lf",&try.temp[0].x,&try.temp[0].y);
  printf("vertex 2: ");
  scanf("%lf%lf",&try.temp[1].x,&try.temp[1].y);
  printf("vertex 3: ");
  scanf("%lf%lf",&try.temp[2].x,&try.temp[2].y);
  for(int i = 0; i < 3; i++){
    printf("\tV%d: (%f, %f)\n",i+1,try.temp[i].x,try.temp[i].y);
  }
  return try;
}

#endif
double GetArea(TRY try){
double area,len01,len12,len02,s;
printf("%f\n",try.temp[0].x);
len01 = sqrt((try.temp[0].x - try.temp[1].x)*(try.temp[0].x - try.temp[1].x) + (try.temp[0].y - try.temp[1].y)*(try.temp[0].y - try.temp[1].y));
len12 = sqrt((try.temp[1].x - try.temp[2].x)*(try.temp[1].x - try.temp[2].x) + (try.temp[1].y - try.temp[2].y)*(try.temp[1].y - try.temp[2].y));  
len02 = sqrt((try.temp[0].x - try.temp[2].x)*(try.temp[0].x - try.temp[2].x) + (try.temp[0].y - try.temp[2].y)*(try.temp[0].y - try.temp[2].y)); 
s = (len01 + len12 + len02)/2;
area = sqrt(s*(s - len01)*(s - len12)*(s - len02));
printf("len01 = %f\nlen12 = %f\nlen02 = %f\n",len01,len12,len02);
printf("area = %f\n",area);
return area;
}
