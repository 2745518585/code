#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int x=0,s=1;
        for(int i=1;i<=n;++i)
        {
            if(s+x+(n-i)<=m) s+=x,++x;
            else ++s;
            printf("%d ",s);
        }
        printf("\n");
    }
    return 0;
}