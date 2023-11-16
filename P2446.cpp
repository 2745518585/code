#include<cstdio>
#include<queue>
using namespace std;
const int N=1000001,M=10000001;
int p=1,p2=1,t[N],t2[N],f[N],g[N],l[N];
bool h[N];
struct road
{
    int m,q,w;
}a[M],a2[M];
struct str2
{
    int x,s;
    bool operator <(const str2& a)const
    {
        return a.s<s;
    }
};
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
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&l[i]);
        for(int j=1;j<=l[i];++j)
        {
            int x;
            scanf("%d",&x);
            road2(x,i,0);
        }
    }
    priority_queue<str2> q;
    q.push((str2){1,0});
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[1]=0;
    while(!q.empty())
    {
        int k=q.top().x;
        q.pop();
        if(h[k]==true) continue;
        h[k]=true;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(h[a[i].m]==false&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                if(l[a[i].m]==0)
                {
                    f[a[i].m]=max(f[a[i].m],g[a[i].m]);
                    q.push((str2){a[i].m,f[a[i].m]});
                }
            }
        }
        for(int i=t2[k];i!=0;i=a2[i].q)
        {
            --l[a2[i].m];
            g[a2[i].m]=max(g[a2[i].m],f[k]);
            if(l[a2[i].m]==0&&f[a2[i].m]<1e9)
            {
                f[a2[i].m]=max(f[a2[i].m],g[a2[i].m]);
                q.push((str2){a2[i].m,f[a2[i].m]});
            }
        }
    }
    printf("%d",max(f[n],g[n]));
    return 0;
}