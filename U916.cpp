#pragma GCC optimize("O2")
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2101,M=4;
int n,m,s,p=1,s1,s2,t[N],b[N],c[N],d[M][N],e[M];
bool h[N];
struct road
{
    int m,q,w;
}a[N*N];
void road2(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int w,int q)
{
    if(w>q) return;
    if(x==s2)
    {
        ++s;
        return;
    }
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        dfs(a[i].m,w+a[i].w,q);
        if(s>=3) return;
    }
    h[x]=false;
}
void dfs2(int x,int w,int q)
{
    if(w>q) return;
    if(x==s2)
    {
        c[4]=w;
        for(int i=3;i>=1;--i)
        {
            if(c[i]>c[i+1]) swap(c[i],c[i+1]);
        }
        return;
    }
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        dfs2(a[i].m,w+a[i].w,q);
    }
    h[x]=false;
}
void dfs3(int x,int w,int k,int q)
{
    if(w>q) return;
    b[k]=x;
    if(x==s2)
    {
        for(int i=1;i<=3;++i)
        {
            if(c[i]==w)
            {
                e[i]=k;
                for(int j=1;j<=k;++j) d[i][j]=b[j];
                c[i]=1e9;
                break;
            }
        }
        return;
    }
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        dfs3(a[i].m,w+a[i].w,k+1,q);
        if(c[1]==1e9&&c[2]==1e9&&c[3]==1e9) return;
    }
    h[x]=false;
}
int main()
{
    // freopen("data.in","r",stdin);
    scanf("%d%d%d",&n,&s1,&s2);
    int x,y,w;
    while(~scanf("%d%d%d",&x,&y,&w)) road2(x,y,w),road2(y,x,w);
    int l=1,r=1e4;
    while(l<r)
    {
        int z=l+r>>1;
        for(int i=1;i<=n;++i) h[i]=false;
        s=0;
        dfs(s1,0,z);
        if(s>=3) r=z;
        else l=z+1;
    }
    for(int i=1;i<=n;++i) h[i]=false;
    for(int i=1;i<=3;++i) c[i]=1e9;
    dfs2(s1,0,l);
    int u=0;
    for(int i=1;i<=3;++i) if(c[i]!=1e9) ++u;
    printf("%d ",u);
    for(int i=1;i<=u;++i)
    {
        printf("%d ",c[i]);
    }
    printf("\n");
    for(int i=1;i<=n;++i) h[i]=false;
    s=0;
    dfs3(s1,0,1,l);
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=e[i];++j)
        {
            printf("%d ",d[i][j]);
        }
        printf("\n");
    }
    return 0;
}