#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n,h,a,b,c,d;
        scanf("%d%d%d%d%d%d%d",&m,&n,&h,&a,&b,&c,&d);
        printf("%d\n",min(min(a+c+abs(b-d),(m-a)+(m-c)+abs(b-d)),min(b+d+abs(a-c),(n-b)+(n-d)+abs(a-c)))+h);
    }
    return 0;
}