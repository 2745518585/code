#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,p=0,a[1000001],b[1000001],rt[1000001];
bool h[1000001];
struct tree
{
    int l,r,s;
}T[150000001];
void build(int &x,int l,int r)
{
    x=++p;
    if(l==r) return;
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q)
{
    T[++p]=T[x];
    ++T[p].s;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q);
    else modify(T[x].r,z+1,r,q);
}
void modify2(int &x,int l,int r,int q,int k)
{
    T[++p]=T[x];
    T[p].s+=k;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify2(T[x].l,l,z,q,k);
    else modify2(T[x].r,z+1,r,q,k);
}
int sum(int x,int l,int r,int q)
{
    if(l==r) return T[x].s;
    int z=l+r>>1;
    if(q<=z) return sum(T[x].l,l,z,q);
    else return sum(T[x].r,z+1,r,q);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        h[a[i]]=true;
    }
    build(rt[0],1,n);
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        modify(rt[i],1,n,a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            if(h[k]==false)
            {
                printf("0\n");
                continue;
            }
            printf("%d\n",sum(rt[r],1,n,k)-sum(rt[l-1],1,n,k));
        }
        else
        {
            int q;
            scanf("%d",&q);
            modify2(rt[q],1,n,a[q],-1);
            modify2(rt[q],1,n,a[q+1],1);
            swap(a[q],a[q+1]);
        }
    }
    return 0;
}
