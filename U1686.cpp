#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,p=1,t[N],b[N],c[N];
ll s=1e18;
bool h[N];
struct road
{
    int m,q,w;
}a[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int k,ll w,int r)
{
    if(w>s) return;
    h[x]=true;
    b[k]=x;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==r&&k>=3&&w+a[i].w<s)
        {
            s=w+a[i].w;
            for(int i=1;i<=k;++i) c[i]=b[i];
            for(int i=k+1;i<=n;++i) c[i]=0;
        }
        if(h[a[i].m]==true) continue;
        dfs(a[i].m,k+1,w+a[i].w,r);
    }
    h[x]=false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    for(int i=1;i<=n;++i) dfs(i,1,0,i);
    if(s==1e18)
    {
        printf("No solution.");
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        if(c[i]!=0) printf("%d ",c[i]);
    }
    return 0;
}