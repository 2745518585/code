#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int m,n;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        printf("%d\n",(m-n)*2);
        for(int i=n;i<=m;++i) printf("%d ",i);
        for(int i=m-1;i>=n+1;--i) printf("%d ",i);
        printf("\n");
    }
    return 0;
}