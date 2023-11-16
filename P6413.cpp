#include<cstdio>
#include<queue>
using namespace std;
int n,m,t[1501],t2[1501],f[1501],g1[1501],g2[1501],l1[1501],l2[1501];
bool h[1501];
struct str
{
    int x,m,q,q2,w,s;
}a[5001];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].m,&a[i].w);
        a[i].q=t[a[i].x];
        t[a[i].x]=i;
        a[i].q2=t2[a[i].m];
        t2[a[i].m]=i;
    }
    for(int r=1;r<=n;++r)
    {
        for(int i=1;i<=n;++i)
        {
            f[i]=1e9;
            h[i]=false;
        }
        f[r]=0;
        h[r]=true;
        queue<int> q;
        q.push(r);
        while(!q.empty())
        {
            int k=q.front();
            q.pop();
            if(h[k]==false) continue;
            h[k]=false;
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[k]+a[i].w<f[a[i].m])
                {
                    f[a[i].m]=f[k]+a[i].w;
                    h[a[i].m]=true;
                    q.push(a[i].m);
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            g1[i]=0;
            g2[i]=1;
        }
        g1[r]=1;
        g2[r]=0;
        for(int i=1;i<=m;++i)
        {
            if(f[a[i].x]+a[i].w==f[a[i].m])
            {
                ++l1[a[i].m];
                ++l2[a[i].x];
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(l1[i]==0) q.push(i);
        }
        while(!q.empty())
        {
            int k=q.front();
            q.pop();
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[k]+a[i].w==f[a[i].m])
                {
                    g1[a[i].m]+=g1[k];
                    --l1[a[i].m];
                    if(l1[a[i].m]==0) q.push(a[i].m);
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(l2[i]==0&&f[i]!=1e9) q.push(i);
        }
        while(!q.empty())
        {
            int k=q.front();
            q.pop();
            for(int i=t2[k];i!=0;i=a[i].q2)
            {
                if(f[a[i].x]+a[i].w==f[k])
                {
                    g2[a[i].x]+=g2[k];
                    --l2[a[i].x];
                    if(l2[a[i].x]==0) q.push(a[i].x);
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            if(f[a[i].x]+a[i].w==f[a[i].m])
            {
                a[i].s=(a[i].s+g1[a[i].x]*g2[a[i].m])%1000000007;
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",a[i].s);
    }
    return 0;
}