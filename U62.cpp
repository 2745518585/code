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
        printf("1\n");
        for(int i=1;i<=k;++i) printf("%d ",b[i]);
        exit(0);
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[i]) continue;
        h[i]=h[i^1]=true;
        dfs(a[i].m,k+1);
    }
}
int main()
{
    scanf("%d",&n);
    int x,y;
    while(~scanf("%d%d",&x,&y))
    {
        ++m;
        road(x,y);
        road(y,x);
        ++l[x],++l[y];
        if(find(x)!=find(y)) fa[find(x)]=find(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)!=find(1)||l[i]%2!=0)
        {
            printf("0");
            return 0;
        }
    }
    dfs(1,1);
    printf("0");
    return 0;
}