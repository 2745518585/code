#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,b[N],d[N];
vector<int> a[N];
namespace sgt1
{
    int tot,rt[N];
    struct tree
    {
        int l,r,s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,int k)
    {
        T[++tot]=T[x];
        x=tot;
        if(ls==rs)
        {
            T[x].s+=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k);
        else add(T[x].r,z+1,rs,q,k);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s;
        }
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
    int merge(int x1,int x2,int ls,int rs)
    {
        if(x1==0||x2==0) return x1+x2;
        int x=++tot;
        if(ls==rs)
        {
            T[x].s=T[x1].s+T[x2].s;
            return x;
        }
        int z=ls+rs>>1;
        T[x].l=merge(T[x1].l,T[x2].l,ls,z);
        T[x].r=merge(T[x1].r,T[x2].r,z+1,rs);
        pushup(x);
        return x;
    }
}
namespace sgt2
{
    int tot,rt[N];
    struct tree
    {
        int l,r,s;
    }T[N<<4];
    void add(int &x,int ls,int rs,int q,int k,int dx)
    {
        if(x==0) x=++tot,T[x].l=T[x].r=0,T[x].s=1e9;
        if(ls==rs)
        {
            if(k<T[x].s)
            {
                if(T[x].s<=n) sgt1::add(sgt1::rt[dx],1,n,T[x].s,-1);
                sgt1::add(sgt1::rt[dx],1,n,k,1);
                T[x].s=k;
            }
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k,dx);
        else add(T[x].r,z+1,rs,q,k,dx);
    }
    int merge(int x1,int x2,int ls,int rs,int dx)
    {
        if(x1==0||x2==0) return x1+x2;
        if(ls==rs)
        {
            if(T[x1].s<T[x2].s)
            {
                sgt1::add(sgt1::rt[dx],1,n,T[x2].s,-1);
            }
            else
            {
                sgt1::add(sgt1::rt[dx],1,n,T[x1].s,-1);
                T[x1].s=T[x2].s;
            }
            return x1;
        }
        int z=ls+rs>>1;
        T[x1].l=merge(T[x1].l,T[x2].l,ls,z,dx);
        T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs,dx);
        return x1;
    }
}
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    sgt2::add(sgt2::rt[x],1,n,b[x],d[x],x);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        sgt1::rt[x]=sgt1::merge(sgt1::rt[x],sgt1::rt[i],1,n);
        sgt2::rt[x]=sgt2::merge(sgt2::rt[x],sgt2::rt[i],1,n,x);
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        sgt1::tot=sgt2::tot=0;
        for(int i=1;i<=n;++i) sgt1::rt[i]=sgt2::rt[i]=0,a[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=2;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            a[x].push_back(i);
        }
        dfs(1,0);
        int las=0;
        for(int i=1;i<=m;++i)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            x^=las,k^=las;
            printf("%d\n",las=sgt1::sum(sgt1::rt[x],1,n,d[x],d[x]+k));
        }
    }
    return 0;
}