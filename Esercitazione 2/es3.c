#include <math.h>
#include <stdio.h>

#define abs(num) (num >= 0 ? num : -num)
#define mean(num, num2) ((num + num2)/2.0)

double function(double x, int p, int q, int r, int s, int t,int u);

double algoritmo(double epsilon, double x_1, double x_2, int p, int q, int r, int s, int t,int u);



int main(){

    int p,q,r,s,t,u;

    scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u);
    double result = algoritmo(0.0001,0,1,p,q,r,s,t,u);
    printf("Result is: %.4f\n",result);

    
}

double algoritmo(double epsilon, double x_1, double x_2, int p, int q, int r, int s, int t,int u){

    double y_1 = function(x_1, p, q, r, s, t, u);
    double y_2 = function(x_2, p, q, r, s, t, u);

    if ((y_1 < 0 && y_2 < 0) || (y_1 > 0 && y_2 > 0))
        return -1;
    
    double y_mean = function(mean(x_1,x_2), p, q, r, s, t, u);

    if (abs(y_mean - 0) <= epsilon)
        return mean(x_1,x_2);
    
    if (y_mean > 0)
        return algoritmo(epsilon, mean(x_1,x_2), x_2, p, q, r, s, t,u);

    else
        return algoritmo(epsilon, x_1, mean(x_1,x_2), p, q, r, s, t,u);

}

double function(double x, int p, int q, int r, int s, int t,int u){

    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*(x*x) + u;
}