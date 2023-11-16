#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f[N],S1[N],T1,S2[N],T2;
struct Tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].s=1e9;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(l>r) return 1e9;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}Tree1,Tree2;
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
        Tree1.build(1,1,n);
        Tree2.build(1,1,n);
        T1=T2=0;
        Tree1.add(1,1,0);
        Tree2.add(1,1,0);
        S1[++T1]=1;
        S2[++T2]=1;
        for(int i=2;i<=n;++i)
        {
            while(T1>=1&&a[S1[T1]]<=a[i])
            {
                Tree1.add(1,S1[T1],1e9);
                --T1;
            }
            while(T2>=1&&a[S2[T2]]>=a[i])
            {
                Tree2.add(1,S2[T2],1e9);
                --T2;
            }
            f[i]=min(Tree1.sum(1,S2[T2]+1,i-1),Tree2.sum(1,S1[T1]+1,i-1))+1;
            S1[++T1]=i;
            S2[++T2]=i;
            Tree1.add(1,i,f[i]);
            Tree2.add(1,i,f[i]);
        }
        printf("%d\n",f[n]);
    }
    return 0;
}