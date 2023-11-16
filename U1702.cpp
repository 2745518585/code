#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,m1,m2,p=1,t[N],f[N],g[N];
bool h[N];
struct road
{
    int m,q,w;
}a[N];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=m1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(min(x,y),max(x,y),w);
    }
    for(int i=1;i<=m2;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(max(x,y),min(x,y),-w);
    }
    for(int i=1;i<=n-1;++i)
    {
        road(i+1,i,0);
    }
    queue<int> Q;
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[1]=0;
    h[1]=true;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        ++g[k];
        if(g[k]>n)
        {
            printf("-1");
            return 0;
        }
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    printf("%d\n",f[n]==1e9?-2:f[n]);
    return 0;
}