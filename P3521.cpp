#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001,M=100000;
int n,m,rt[N],tot,p=1,t[N];
ll s1,s2,s;
struct tree
{
    int l,r;
    ll s;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void add(int &x,int l,int r,int q,ll k)
{
    if(x==0) x=++tot;
    if(l==r)
    {
        T[x].s+=k;
        return;
    }
    int z=l+r>>1;
    if(q<=z) add(T[x].l,l,z,q,k);
    else add(T[x].r,z+1,r,q,k);
    pushup(x);
}
int merge(int x1,int x2,int l,int r)
{
    if(x1==0) return x2;
    if(x2==0) return x1;
    if(l==r)
    {
        T[x1].s+=T[x2].s;
        return x1;
    }
    s1+=T[T[x1].r].s*T[T[x2].l].s;
    s2+=T[T[x1].l].s*T[T[x2].r].s;
    int z=l+r>>1;
    T[x1].l=merge(T[x1].l,T[x2].l,l,z);
    T[x1].r=merge(T[x1].r,T[x2].r,z+1,r);
    pushup(x1);
    return x1;
}
int dfs()
{
    int k;
    scanf("%d",&k);
    if(k!=0)
    {
        add(rt[k],1,n,k,1);
        return k;
    }
    int x=dfs(),y=dfs();
    s1=s2=0;
    merge(rt[x],rt[y],1,n);
    s+=min(s1,s2);
    return x;
}
int main()
{
    scanf("%d",&n);
    dfs();
    printf("%lld",s);
    return 0;
}