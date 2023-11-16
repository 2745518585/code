#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,m,p=1,t[N],l[N],b[N],fa[N];
bool h[N];
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
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x,int k)
{
    b[k]=x;
    if(k==m+1)
    {
        for(int i=1;i<=k-1;++i) printf("%d",(b[i]-1)>>(n-2));
        exit(0);
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[i]) continue;
        h[i]=true;
        dfs(a[i].m,k+1);
        h[i]=false;
    }
}
int main()
{
    scanf("%d",&n);
    m=1<<n;
    for(int i=0;i<=(1<<(n-1))-1;++i)
    {
        road(i+1,((i<<1)&((1<<(n-1))-1))+2);
        road(i+1,((i<<1)&((1<<(n-1))-1))+1);
    }
    printf("%d ",m);
    dfs(1,1);
    return 0;
}