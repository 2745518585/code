#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001,P=998244353;
int n,m,tot;
struct tree
{
    int l,r;
    ll s;
}T[N<<6];
struct tree2
{
    int l,r,rt;
}T2[N<<2];
ll ksm(ll x,ll y){ll res = 1; for(;y;y >>= 1,x = x * x % P) if(y & 1) res = res * x % P; return res;}
ll mul(ll p,ll q){ll res = p * q % P; res = (res + (1 - p) * (1 - q) % P) % P; return (res + P) % P;}
void build(int x,int l,int r)
{
    T2[x].l=l;
    T2[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int &x,int ls,int rs,int l,int r,ll p)
{
	if(x==0)
    {
        x=++tot;
        T[x].s=1;
    }
	if(l<=ls&&r>=rs)
    {
        T[x].s=mul(T[x].s,p);
        return;
    }
	int z=ls+rs>>1;
	if(l<=z) add(T[x].l,ls,z,l,r,p);
	if(r>z) add(T[x].r,z + 1,rs,l,r,p);
}
void add2(int x,int ls,int rs,int l1,int r1,int l2,int r2,ll k)
{
	if(ls>=l1&&rs<=r1)
    {
        add(T2[x].rt,1,n,l2,r2,k);
        return;
    }
	int z=ls+rs>>1;
	if(l1<=z) add2(x<<1,ls,z,l1,r1,l2,r2,k);
	if(r1>z) add2(x<<1|1,z+1,rs,l1,r1,l2,r2,k);
}
ll sum(int x,int ls,int rs,int q)
{
	if(x==0) return 1;
	if(ls==rs) return T[x].s;
	int z=ls+rs>>1;
	if(q<=z) return mul(T[x].s,sum(T[x].l,ls,z,q));
	else return mul(T[x].s,sum(T[x].r,z + 1,rs,q));
}
ll sum1(int x,int l,int r,int q1,int q2)
{
	if(l==r) return sum(T2[x].rt,1,n,q2);
	int z=l+r>>1;
	if(q1<=z) return mul(sum1(x<<1,l,z,q1,q2),sum(T2[x].rt,1,n,q2));
	else return mul(sum1(x<<1|1,z+1,r,q1,q2),sum(T2[x].rt,1,n,q2));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
	{
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
		if(z==1)
		{
			ll w=ksm(y-x+1,P-2);
			if(x > 1) add2(1,0,n,1,x - 1,x,y,(1 - w + P) % P),add2(1,0,n,0,0,1,x - 1,0);
			if(y < n) add2(1,0,n,x,y,y + 1,n,(1 - w + P) % P),add2(1,0,n,0,0,y + 1,n,0);
			add2(1,0,n,x,y,x,y,(1 - 2ll * w + P) % P); add2(1,0,n,0,0,x,y,w);
		}
		else cout << sum1(1,0,n,x - 1,y) << "\n";
	}
	return 0;
}
