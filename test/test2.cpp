#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,q,b[N];
char a[N],d[N];
struct tree
{
    int l,r,s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s1=T[x].s2=b[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s1=T[x].s2=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum1(int x,int k)
{
    if(T[x].l==T[x].r) return T[x].l;
    int z=T[x].l+T[x].r>>1;
    if(T[x<<1].s1<k) return sum1(x<<1,k);
    else return sum1(x<<1|1,k);
}
int sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s2;
    int z=T[x].l+T[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%s",&n,a+1);
    for(int i=1;i<=n;++i)
    {
        b[i]=b[i-1];
        if(a[i]=='(') ++b[i];
        else --b[i];
    }
    b[n+1]=-1e9;
    build(1,1,n+1);
    for(int i=1;i<=n;++i)
    {
        if(a[i]==')')
        {
            add(1,i,1e9);
            d[++q]=')';
            continue;
        }
        int x=sum1(1,b[i-1])-1;
        int p=sum2(1,i,x);
        for(int j=b[i];j<=p;++j) d[++q]='(';
        int o=i;
        while(b[i]<p)
        {
            add(1,i,1e9);
            ++i;
        }
        add(1,i,1e9);
    }
    for(int i=1;i<=q;++i) printf("%c",d[i]);
    return 0;
}