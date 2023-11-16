#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,a[N],b[N],c[N],e[N],g[N];
ll T[N];
struct str
{
    int z,x,y,k;
}d[N];
mt19937 rnd(time(0));
void add(int x,int k)
{
    while(x<=n)
    {
        T[x]+=k;
        x+=(x&-x);
    }
    return;
}
ll sum(int x)
{
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
signed main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        e[++q]=a[i];
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&d[i].z,&d[i].x,&d[i].y);
        c[i]=1;
        if(d[i].z==2) scanf("%d",&d[i].k);
        else e[++q]=d[i].y;
    }
    sort(e+1,e+q+1);
    q=unique(e+1,e+q+1)-e-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(e+1,e+q+1,a[i])-e;
    }
    for(int i=1;i<=m;++i)
    {
        if(d[i].z==1)
        {
            d[i].y=lower_bound(e+1,e+q+1,d[i].y)-e;
        }
    }
    for(int r=1;r<=30;r++)
    {
        for(int i=1;i<=n;++i) T[i]=0,b[i]=a[i];
        for(int i=1;i<=q;++i)
        {
            g[i]=rnd()>>1;
        }
        for(int i=1;i<=n;++i)
        {
            add(i,g[b[i]]);
        }
        for(int i=1;i<=m;++i)
        {
            if(d[i].z==1)
            {
                add(d[i].x,g[d[i].y]-g[b[d[i].x]]);
                b[d[i].x]=d[i].y;
            }
            else
            {
                if(c[i])
                {
                    if((d[i].y-d[i].x+1)%d[i].k)
                    {
                        c[i]=0;
                        continue;
                    }
                    if((sum(d[i].y)-sum(d[i].x-1))%d[i].k)
                    {
                        c[i]=0;
                        continue;
                    }
                }
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(d[i].z==2)
        {
            if(c[i]) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}