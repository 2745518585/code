#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int n,m,p=1,t[N],fa[N],c[N];
struct road
{
    int m,q;
}a[N];
struct str
{
    int x,t;
};
vector<str> b[N];
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
void dfs(int x)
{
    for(int i=0;i<b[x].size();++i)
    {
        if(fa[b[x][i].x]!=0)
        {
            c[b[x][i].t]=find(b[x][i].x);
        }
    }
    fa[x]=x;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        dfs(a[i].m);
        fa[find(a[i].m)]=find(x);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int z;
        scanf("%d",&z);
        for(int j=1;j<=z;++j)
        {
            int x;
            scanf("%d",&x);
            road(i,x);
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y)
        {
            c[i]=x;
            continue;
        }
        b[x].push_back((str){y,i});
        b[y].push_back((str){x,i});
    }
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}