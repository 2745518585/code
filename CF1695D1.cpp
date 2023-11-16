#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,p=1,t[N],f[N],f2[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    f[x]=0;
    int s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        if(f[a[i].m]==0) ++s;
        f[x]+=f[a[i].m];
    }
    f[x]+=max(s-1,0);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n==1)
        {
            printf("0\n");
            continue;
        }
        p=1;
        for(int i=1;i<=n;++i) t[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
            road(y,x);
        }
        int s=1e9;
        for(int i=1;i<=n;++i)
        {
            dfs(i,0);
            s=min(s,f[i]+1);
        }
        printf("%d\n",s);
    }
    return 0;
}