#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300001,M=30;
int n,m,q,tot,t1,t2,rt,b[N];
ll a[N][31];
struct tree
{
    int l,r,s,k[31];
}T[N<<4];
void pushup(int x,int ts)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
    for(int i=0;i<=M;++i) T[x].k[i]=T[T[x].l].k[i]+T[T[x].r].k[i];
    T[x].k[ts]+=T[T[x].r].s;
}
void add(int &x,int ts,int q)
{
    if(x==0) x=++tot;
    if(ts==-1)
    {
        ++T[x].s;
        return;
    }
    if((q&(1<<ts))==0) add(T[x].l,ts-1,q);
    else add(T[x].r,ts-1,q);
    pushup(x,ts);
}
pair<int,ll> sum(int x,int ts,int k)
{
    if(ts==-1) return make_pair(k,0);
    int xl=T[x].l,xr=T[x].r;
    if(t1&(1<<ts)) swap(xl,xr);
    if(k<=T[xl].s)
    {
        pair<int,ll> z=sum(xl,ts-1,k);
        ll s=0;
        if((t1&(1<<ts))^(t2&(1<<ts))) s=(ll)z.first<<ts;
        return make_pair(z.first,z.second+s);
    }
    else
    {
        pair<int,ll> z=sum(xr,ts-1,k-T[xl].s);
        ll s=0;
        for(int i=0;i<=ts-1;++i)
        {
            if((t2&(1<<i))==0) s+=(ll)T[xl].k[i]<<i;
            else s+=(ll)(T[xl].s-T[xl].k[i])<<i;
        }
        if(((t1&(1<<ts))^(t2&(1<<ts)))==0) s+=(ll)z.first<<ts;
        else s+=(ll)T[xl].s<<ts;
        return make_pair(z.first+T[xl].s,z.second+s);
    }
}
int main()
{
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        scanf("%d",&b[i]);
        for(int j=0;j<=M;++j)
        {
            a[i][j]=a[i-1][j];
            if(b[i]&(1<<j)) ++a[i][j];
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x;
            scanf("%d",&x);
            x^=t2;
            b[++q]=x;
            for(int j=0;j<=M;++j)
            {
                a[q][j]=a[q-1][j];
                if(x&(1<<j)) ++a[q][j];
            }
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            ll s=0;
            if(l<=n)
            {
				// printf("%lld\n",sum(rt,M,min(r,n)).second);
                s+=sum(rt,M,min(r,n)).second-sum(rt,M,l-1).second;
            }
            if(r>n)
            {
                int x1=max(l-n,1),x2=r-n;
                for(int j=0;j<=M;++j)
                {
                    if(t2&(1<<j)) s+=(ll)((x2-x1+1)-(a[x2][j]-a[x1-1][j]))<<j;
                    else s+=(ll)(a[x2][j]-a[x1-1][j])<<j;
                }
            }
            printf("%lld\n",s);
        }
        else if(z==3)
        {
            int x;
            scanf("%d",&x);
            t2^=x;
        }
        else if(z==4)
        {
            for(int j=1;j<=q;++j)
            {
                add(rt,M,b[j]);
            }
            n+=q;
            q=0;
            t1=t2;
        }
    }
    return 0;
}