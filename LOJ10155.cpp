#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,p=1,s=0,b[N],t[N],f[N];
bool h[N];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    int q1=0,q2=-1e9;
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        dfs(a[i].m);
        f[x]=max(f[a[i].m]+1,f[x]);
        if(f[a[i].m]+1>q1)
        {
            q2=q1;
            q1=f[a[i].m]+1;
        }
        else if(f[a[i].m]+1>q2) q2=f[a[i].m]+1;
    }
    s=max(s,q1+q2);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=i*2;j<=n;j+=i) b[j]+=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i]<i)
        {
            road(i,b[i]);
            road(b[i],i);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(!h[i]) dfs(i);
    }
    printf("%d",s);
    return 0;
}