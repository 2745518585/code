#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N=500001;
int m,n,rt,tot;
multiset<int> Set;
struct tree
{
    int l,r,s,s1,s2,s3,s4;
}T[N<<4];
void pushup(tree &T,tree T1,tree T2)
{
    T.s=max(T1.s,T2.s);
    if(T1.s1!=T2.s3) T.s=max(T.s,T1.s1+T2.s3);
    else T.s=max(T.s,max(T1.s1+T2.s4,T1.s2+T2.s3));
    if(T1.s1>T2.s1) T.s1=T1.s1,T.s2=max(T1.s2,T2.s1);
    else T.s1=T2.s1,T.s2=max(T1.s1,T2.s2);
    if(T1.s3>T2.s3) T.s3=T1.s3,T.s4=max(T1.s4,T2.s3);
    else T.s3=T2.s3,T.s4=max(T1.s3,T2.s4);
}
void add1(int &x,int ls,int rs,int q,int k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].l+=k;
        T[x].s=T[x].s1=T[x].s2=T[x].s3=T[x].s4=-1e9;
        if(T[x].l>=1) T[x].s1=ls;
        if(T[x].l>=2&&ls*2<n) T[x].s=max(T[x].s,ls*2);
        if(T[x].r>=1) T[x].s3=n-ls;
        if(T[x].r>=2&&(n-ls)*2<n) T[x].s=max(T[x].s,(n-ls)*2);
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add1(T[x].l,ls,z,q,k);
    else add1(T[x].r,z+1,rs,q,k);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
void add2(int &x,int ls,int rs,int q,int k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].r+=k;
        T[x].s=T[x].s1=T[x].s2=T[x].s3=T[x].s4=-1e9;
        if(T[x].l>=1) T[x].s1=ls;
        if(T[x].l>=2&&ls*2<n) T[x].s=max(T[x].s,ls*2);
        if(T[x].r>=1) T[x].s3=n-ls;
        if(T[x].r>=2&&(n-ls)*2<n) T[x].s=max(T[x].s,(n-ls)*2);
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add2(T[x].l,ls,z,q,k);
    else add2(T[x].r,z+1,rs,q,k);
    pushup(T[x],T[T[x].l],T[T[x].r]);
}
int main()
{
    T[0].s=T[0].s1=T[0].s2=T[0].s3=T[0].s4=-1e9;
    scanf("%d%d",&m,&n);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int z,x;
        scanf("%d%d",&z,&x);
        x^=las;
        x%=n;
        if(z==1)
        {
            add1(rt,0,n,x,1);
            add2(rt,0,n,n-x,1);
            Set.insert(x);
        }
        else
        {
            add1(rt,0,n,x,-1);
            add2(rt,0,n,n-x,-1);
            Set.erase(Set.find(x));
        }
        int p=-1e9;
        if(Set.size()>=2) p=(*(--Set.end())+*(----Set.end()))%n;
        p=max(p,T[1].s);
        if(p>=0) printf("%d\n",las=p);
        else printf("EE\n"),las=0;
    }
    return 0;
}