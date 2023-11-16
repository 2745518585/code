#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        double H,h,D;
        scanf("%lf%lf%lf",&H,&h,&D);
        double d=D-sqrt((H-h)*D);
        if(d<0) d=0;
        else if(d>D*h/H) d=D*h/H;
        printf("%.3lf\n",(h*D-H*D)/(D-d)+H+d+1e-10);
    }
    return 0;
}