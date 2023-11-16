#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int n,m,p=1,t[N],g[N],l[N];
double f[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(y,x,w);
        ++g[x];
    }
    for(int i=1;i<=n;++i) l[i]=g[i];
    queue<int> Q;
    Q.push(n);
    f[n]=0;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            f[a[i].m]+=(f[k]+a[i].w)/(g[a[i].m]);
            --l[a[i].m];
            if(l[a[i].m]==0) Q.push(a[i].m);
        }
    }
    printf("%.2lf",f[1]);
    return 0;
}