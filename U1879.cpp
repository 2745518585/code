#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,tot,a[N],rt[N],f[N],g[N];
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int k,int t)
{
    T[++tot]=T[x];
    ++T[tot].s;
    x=tot;
    if(t==-1) return;
    if((k&(1<<t))==0) add(T[x].l,k,t-1);
    else add(T[x].r,k,t-1);
}
int sum(int x1,int x2,int q,int t)
{
    if(t==-1) return 0;
    if(g[t]==-1)
    {
        if(f[t]==0)
        {
            int k=T[T[x2].l].s-T[T[x1].l].s;
            if(q<=k) return sum(T[x1].l,T[x2].l,q,t-1);
            else return sum(T[x1].r,T[x2].r,q-k,t-1)+(1<<t);
        }
        else
        {
            int k=T[T[x2].r].s-T[T[x1].r].s;
            if(q<=k) return sum(T[x1].r,T[x2].r,q,t-1);
            else return sum(T[x1].l,T[x2].l,q-k,t-1)+(1<<t);
        }
    }
    if((g[t]^f[t])==0)
    {
        if(T[x2].l) return sum(T[x1].l,T[x2].l,q,t-1);
        else return sum(T[x1].r,T[x2].r,q,t-1);
    }
    else
    {
        if(T[x2].r) return sum(T[x1].r,T[x2].r,q,t-1)+(1<<t);
        else return sum(T[x1].l,T[x2].l,q,t-1)+(1<<t);
    }
}
void rebuild()
{
    tot=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=30;++j)
        {
            if(g[j]==0) a[i]=(a[i]|(1<<j))^(1<<j);
            else if(g[j]==1) a[i]|=(1<<j);
            if(f[j]==1) a[i]^=(1<<j);
        }
        rt[i]=rt[i-1];
        add(rt[i],a[i],30);
    }
    for(int j=0;j<=30;++j)
    {
        if(g[j]!=-1) g[j]^=f[j];
        f[j]=0;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        rt[i]=rt[i-1];
        add(rt[i],a[i],30);
    }
    for(int i=0;i<=30;++i) g[i]=-1;
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='X')
        {
            int x;
            scanf("%d",&x);
            for(int i=0;i<=30;++i) f[i]^=((x&(1<<i))!=0);
        }
        else if(z[0]=='A'&&z[1]=='n')
        {
            int x;
            scanf("%d",&x);
            bool u=false;
            for(int i=0;i<=30;++i)
            {
                if((x&(1<<i))==0)
                {
                    if(g[i]==-1) u=true;
                    f[i]=g[i]=0;
                }
            }
            if(u==true) rebuild();
        }
        else if(z[0]=='O')
        {
            int x;
            scanf("%d",&x);
            bool u=false;
            for(int i=0;i<=30;++i)
            {
                if((x&(1<<i))!=0)
                {
                    if(g[i]==-1) u=true;
                    g[i]=1,f[i]=0;
                }
            }
            if(u==true) rebuild();
        }
        else
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",sum(rt[x-1],rt[y],k,30));
        }
    }
    return 0;
}