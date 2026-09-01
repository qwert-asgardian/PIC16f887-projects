#include<stdio.h>
void main(){
    float pre = 128;
    float count = 0.0;
    float f_osc = 4000000;
    int i;

    for(i=0;i<256;i++){
    count = ((f_osc) / (4 * pre * (256-i)));//256 bcz 8 bit register
    printf("%d: %.6f\n",i,count);
    }
}
