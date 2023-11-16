#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i]=-1;
        for(int i=1;i<=n+m;++i) h[i]=false;
        int s=0;
        for(int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);
            if(h[x]==false)
            {
                a[++s]=i;
                h[x]=true;
            }
        }
        for(int i=1;i<=n;++i)
        {
            printf("%d ",a[n-i+1]);
        }
        printf("\n");
    }
    return 0;
}