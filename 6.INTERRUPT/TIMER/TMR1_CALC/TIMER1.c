#include<stdio.h>
void main(){
    float pre = 8;
    float count = 0.0;
    float f_osc = 4000000;
    int i;

    for(i=0;i<3037;i++){
    count = ((f_osc) / (4 * pre * (65536-i)));
    printf("%d: %.6f\n",i,count);
    }
}
