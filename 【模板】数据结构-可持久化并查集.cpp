#include<cstdio>
#include<algorithm>
using namespace std;
const int N=300001;
int n,m,tot=0,rt[N];
struct tree
{
    int l,r,s,s2;
}T[N<<5];
void build(int &x,int l,int r)
{
    x=++tot;
    if(l==r)
    {
        T[x].s=l;
        T[x].s2=1;
        return;
    }
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void add(int &x,int l,int r,int q,int k)
{
    T[++tot]=T[x];
    T[tot].s=k;
    x=tot;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) add(T[x].l,l,z,q,k);
    else add(T[x].r,z+1,r,q,k);
}
void add2(int &x,int l,int r,int q,int k)
{
    T[++tot]=T[x];
    T[tot].s2+=k;
    x=tot;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) add2(T[x].l,l,z,q,k);
    else add2(T[x].r,z+1,r,q,k);
}
int sum(int x,int l,int r,int q)
{
    if(l==r) return T[x].s;
    int z=l+r>>1;
    if(q<=z) return sum(T[x].l,l,z,q);
    else return sum(T[x].r,z+1,r,q);
}
int sum2(int x,int l,int r,int q)
{
    if(l==r) return T[x].s2;
    int z=l+r>>1;
    if(q<=z) return sum2(T[x].l,l,z,q);
    else return sum2(T[x].r,z+1,r,q);
}
int find(int x,int t)
{
    int z=sum(rt[t],1,n,x);
    if(z==x) return x;
    return find(z,t);
}
int main()
{
    scanf("%d%d",&n,&m);
    build(rt[0],1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            rt[i]=rt[i-1];
            int z1=find(x,i),z2=find(y,i);
            if(z1!=z2)
            {
                if(sum2(rt[i],1,n,z1)<sum2(rt[i],1,n,z2)) swap(z1,z2);
                add(rt[i],1,n,z2,z1);
                add2(rt[i],1,n,z1,sum2(rt[i],1,n,z2));
            }
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            rt[i]=rt[x];
        }
        else if(z==3)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            rt[i]=rt[i-1];
            if(find(x,i)==find(y,i)) printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}