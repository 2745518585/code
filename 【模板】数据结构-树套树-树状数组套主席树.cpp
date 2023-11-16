#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int n,m,q,tot,a[N],b[N],a1[N],a2[N],t1,t2,rt[N];
struct str
{
    int z,l,r,k;
}d[N];
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void modify(int &x,int l,int r,int q,int k)
{
    if(x==0) x=++tot;
    if(l==r)
    {
        T[x].s+=k;
        return;
    }
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q,k);
    else modify(T[x].r,z+1,r,q,k);
    pushup(x);
}
int lowbit(int x)
{
    return x&-x;
}
void add(int x,int t,int k)
{
    modify(rt[x],1,q,t,k);
    while(x<=n)
    {
        x+=lowbit(x);
        modify(rt[x],1,q,t,k);
    }
}
int sum0(int l,int r,int k)
{
    if(l==r) return l;
    int z=l+r>>1,s=0;
    for(int i=1;i<=t2;++i) s+=T[T[a2[i]].l].s;
    for(int i=1;i<=t1;++i) s-=T[T[a1[i]].l].s;
    if(k<=s)
    {
        for(int i=1;i<=t2;++i) a2[i]=T[a2[i]].l;
        for(int i=1;i<=t1;++i) a1[i]=T[a1[i]].l;
        return sum0(l,z,k);
    }
    else
    {
        for(int i=1;i<=t2;++i) a2[i]=T[a2[i]].r;
        for(int i=1;i<=t1;++i) a1[i]=T[a1[i]].r;
        return sum0(z+1,r,k-s);
    }
}
int num0(int l,int r,int k)
{
    if(l==r) return 0;
    int z=l+r>>1,s=0;
    if(k<=z)
    {
        for(int i=1;i<=t2;++i) a2[i]=T[a2[i]].l;
        for(int i=1;i<=t1;++i) a1[i]=T[a1[i]].l;
        return num0(l,z,k);
    }
    else
    {
        for(int i=1;i<=t2;++i) s+=T[T[a2[i]].l].s,a2[i]=T[a2[i]].r;
        for(int i=1;i<=t1;++i) s-=T[T[a1[i]].l].s,a1[i]=T[a1[i]].r;
        return s+num0(z+1,r,k);
    }
}
void init(int x,int y)
{
    t1=t2=0;
    --x;
    a1[++t1]=rt[x];
    while(x>=1)
    {
        x-=lowbit(x);
        a1[++t1]=rt[x];
    }
    a2[++t2]=rt[y];
    while(y>=1)
    {
        y-=lowbit(y);
        a2[++t2]=rt[y];
    }
}
int sum(int l,int r,int k)
{
    init(l,r);
    return sum0(1,q,k);
}
int num(int l,int r,int k)
{
    init(l,r);
    return num0(1,q,k)+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[++q]=a[i];
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&d[i].z);
        if(d[i].z==3)
        {
            scanf("%d%d",&d[i].l,&d[i].k);
        }
        else scanf("%d%d%d",&d[i].l,&d[i].r,&d[i].k);
        if(d[i].z==3||d[i].z==4||d[i].z==5) b[++q]=d[i].k;
    }
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        add(i,a[i],1);
    }
    for(int i=1;i<=m;++i)
    {
        if(d[i].z!=2) d[i].k=lower_bound(b+1,b+q+1,d[i].k)-b;
        if(d[i].z==1)
        {
            printf("%d\n",num(d[i].l,d[i].r,d[i].k));
        }
        else if(d[i].z==2)
        {
            printf("%d\n",b[sum(d[i].l,d[i].r,d[i].k)]);
        }
        else if(d[i].z==3)
        {
            add(d[i].l,a[d[i].l],-1);
            a[d[i].l]=d[i].k;
            add(d[i].l,a[d[i].l],1);
        }
        else if(d[i].z==4)
        {
            int p=num(d[i].l,d[i].r,d[i].k);
            if(p==1) printf("-2147483647\n");
            else printf("%d\n",b[sum(d[i].l,d[i].r,p-1)]);
        }
        else if(d[i].z==5)
        {
            int p=num(d[i].l,d[i].r,d[i].k+1);
            if(p>d[i].r-d[i].l+1) printf("2147483647\n");
            else printf("%d\n",b[sum(d[i].l,d[i].r,p)]);
        }
    }
    return 0;
}