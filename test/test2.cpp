#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,tot,rt;
struct tree
{
    int l,r,w;
    ll s;
    tree() {}
    tree(int w):w(w) {}
}T[N<<2];
void pushup(tree &T,const tree &T1,const tree &T2)
{
    T.s=T2.s+(T1.s>>T2.w);
    T.w=T1.w+T2.w;
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(x==0) x=++tot,T[x].w=rs-ls+1;
    if(ls==rs)
    {
        T[x].s+=k;
        return;
    }
    int z=ls+rs>>1;
    if(T[x].l==0) T[x].l=++tot,T[T[x].l].w=z-ls+1;
    if(T[x].r==0) T[x].r=++tot,T[T[x].r].w=rs-z;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
tree sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return tree(min(rs,r)-max(ls,l)+1);
    if(ls>=l&&rs<=r) return T[x];
    int z=ls+rs>>1;
    tree s;
    if(r<=z) s=sum(T[x].l,ls,z,l,r);
    else if(l>z) s=sum(T[x].r,z+1,rs,l,r);
    else pushup(s,sum(T[x].l,ls,z,l,r),sum(T[x].r,z+1,rs,l,r));
    return s;
}
int main()
{
    scanf("%d%*d%*d%*d",&m);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(rt,0,30*(m+2),y,x);
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",sum(rt,0,30*(m+2),0,x).s&1);
        }
    }
    return 0;
}