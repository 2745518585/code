#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int m,n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m+n-1;++i) a[i]=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                int x;
                scanf("%d",&x);
                a[i+j-1]^=x;
            }
        }
        bool u=true;
        for(int i=1;i<=m+n-1;++i)
        {
            if(a[i]!=0)
            {
                u=false;
                break;
            }
        }
        if(u) printf("Jeel\n");
        else printf("Ashish\n");
    }
    return 0;
}