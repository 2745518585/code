#include<cstdio>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        double a=1;
        for(int i=n-1;i>=1;--i) a+=(double)n/(n-i);
        printf("%.2lf\n",a);
    }
    return 0;
}