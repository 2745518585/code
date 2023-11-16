#include<bits/stdc++.h>
using namespace std;
const int N=100001,M=1000001;
int n,m,p=1,q,tot,t[N],r[N];
bool h[N];
struct tree
{
    int b,c;
}T[N];
struct road
{
    int m,q;
}a[M];
stack<int> S;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m);
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
        else if(h[a[i].m]==false)
        {
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
    }
    if(T[x].b==T[x].c)
    {
        ++q;
        while(S.top()!=x)
        {
            h[S.top()]=true;
            r[S.top()]=q;
            S.pop();
        }
        h[x]=true;
        r[x]=q;
        S.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0) dfs(i);
    }
    printf("%d\n",q);
    for(int i=1;i<=q;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        if(h[r[i]]==true) continue;
        h[r[i]]=true;
        int w=0;
        for(int j=1;j<=n;++j)
        {
            if(r[j]==r[i]) ++w;
        }
        printf("%d ",w);
        for(int j=1;j<=n;++j)
        {
            if(r[j]==r[i]) printf("%d ",j);
        }
        printf("\n");
    }
    return 0;
}