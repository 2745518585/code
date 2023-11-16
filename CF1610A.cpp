#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n;
        scanf("%d%d",&m,&n);
        if(m==1&&n==1) printf("0\n");
        else if(m==1||n==1) printf("1\n");
        else printf("2\n");
    }
    return 0;
}