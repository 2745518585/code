#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001,M=10000001;
int n,m,s1,p=1,t[N],p2=1,t2[N],f[N],f2[N];
bool h[N];
struct str
{
    int m,q,w;
}a[M],a2[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void road2(int x,int y,int w)
{
    a2[++p2].m=y;
    a2[p2].q=t2[x];
    t2[x]=p2;
    a2[p2].w=w;
}
int main()
{
    scanf("%d%d%d",&n,&m,&s1);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        road2(y,x,w);
    }
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[s1]=0;
    h[s1]=true;
    queue<int> Q;
    Q.push(s1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
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
    for(int i=1;i<=n;++i) f2[i]=1e9,h[i]=false;
    f2[s1]=0;
    h[s1]=true;
    Q.push(s1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t2[k];i!=0;i=a2[i].q)
        {
            if(f2[k]+a2[i].w<f2[a2[i].m])
            {
                f2[a2[i].m]=f2[k]+a2[i].w;
                h[a2[i].m]=true;
                Q.push(a2[i].m);
            }
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s=max(s,f[i]+f2[i]);
    }
    printf("%d",s);
    return 0;
}