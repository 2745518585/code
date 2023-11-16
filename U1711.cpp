#include<bits/stdc++.h>
using namespace std;
const int N=100001,M=1000001;
struct str
{
    int m,q;
}a[M];
stack<int> S;
int n,m,p=0,q=0,s=0,t[N],d[N],b[N],c[N],r[N],l[N],f[N],fa[N];
bool h[N];
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
    b[x]=c[x]=++q;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(b[a[i].m]==0)
        {
            dfs(a[i].m);
            c[x]=min(c[x],c[a[i].m]);
        }
        else if(h[a[i].m]==false)
        {
            c[x]=min(c[x],c[a[i].m]);
        }
    }
    if(b[x]==c[x])
    {
        ++s;
        while(S.top()!=x)
        {
            h[S.top()]=true;
            r[S.top()]=s;
            ++f[s];
            S.pop();
        }
        h[x]=true;
        r[x]=s;
        ++f[s];
        S.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        if(find(x)!=find(y)) fa[find(x)]=find(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)!=find(1))
        {
            printf("0");
            return 0;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0) dfs(i);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q)
        {
            if(r[i]!=r[a[j].m])
            {
                ++l[r[i]];
            }
        }
    }
    int u=0;
    for(int i=1;i<=s;++i)
    {
        if(l[i]==0) ++u;
    }
    if(u!=1)
    {
        printf("0");
        return 0;
    }
    for(int i=1;i<=s;++i)
    {
        if(l[i]==0)
        {
            printf("%d",f[i]);
            return 0;
        }
    }
    return 0;
}