#include<bits/stdc++.h>
using namespace std;
const int N=1000001,M=10000001;
struct str
{
    int m,q;
}a[M];
stack<int> S;
int n,m,p=0,q=0,s=0,t[N],d[N],b[N],c[N],r[N],l[N],l2[N],f[N],fa[N];
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
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        while(x!=0)
        {
            road(i,x);
            scanf("%d",&x);
        }
    }
    int k=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0)
        {
            dfs(i);
            ++k;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q)
        {
            if(r[i]!=r[a[j].m])
            {
                ++l[r[a[j].m]];
                ++l2[r[i]];
            }
        }
    }
    int w=0,w2=0;
    for(int i=1;i<=s;++i)
    {
        if(l[i]==0) ++w;
        if(l2[i]==0) ++w2;
    }
    printf("%d\n%d",w,s==1?0:max(w,w2));
    return 0;
}