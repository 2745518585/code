#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,a[N],rt1[N],rt2[N],tot;
vector<int> b[N];
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
    if(x==0||l>r) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[a[i]].push_back(i);
    }
    for(int i=1;i<=200000;++i)
    {
        for(auto j:b[i])
        {
            if(j%2==1) add(rt1[i],1,n,j,1);
            else add(rt2[i],1,n,j,1);
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        // printf("%d %d %d\n",i,max(i,1+k-i),min(i+k,n+(n-k+1)-i));
        if(i%2==1)
        {
            s+=sum(rt1[a[i]],1,n,max(i,1+k-i),min(i+k,n+(n-k+1)-i));
        }
        else
        {
            s+=sum(rt2[a[i]],1,n,max(i,1+k-i),min(i+k,n+(n-k+1)-i));
        }
    }
    // printf("%lld\n",s);
    printf("%lld",(ll)(n-k+1)*(k/2+1)-s);
    return 0;
}