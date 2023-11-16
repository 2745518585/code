#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],f[N],tot,rt[N];
struct tree
{
    int l,r,s;
}T[N<<4];
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
}
int sum(int x,int ls,int rs,int q)
{
    if(x==0) return 0;
    if(ls==rs) return T[x].s;
    int z=ls+rs>>1;
    if(q<=z) return sum(T[x].l,ls,z,q);
    else return sum(T[x].r,z+1,rs,q);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        tot=0;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            rt[i]=rt[sum(rt[i-1],1,n,a[i])-1];
            add(rt[i],1,n,a[i],i);
            int z=sum(rt[i-1],1,n,a[i]);
            if(z!=0) f[i]=f[z-1]+1;
            else f[i]=0;
            s+=f[i];
        }
        printf("%lld\n",s);
    }
    return 0;
}