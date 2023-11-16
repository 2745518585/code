#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=1000001;
int n,m,tot,rt[N],fa[N],b[N],c[N];
deque<int> d[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
struct tree
{
    int l,r;
    ll s,k;
}T[N<<5];
void pushup(int x)
{
    T[x].s=max(T[T[x].l].s,T[T[x].r].s);
}
void pushdown(int x)
{
    if(T[x].k==0||T[x].k==1) return;
    if(T[x].l)
    {
        T[T[x].l].k*=T[x].k;
        T[T[x].l].s*=T[x].k;
    }
    if(T[x].r)
    {
        T[T[x].r].k*=T[x].k;
        T[T[x].r].s*=T[x].k;
    }
    T[x].k=1;
}
inline void newnode(int &x)
{
    if(x&&T[x].k==0)
    {
        T[++tot]=T[x];
        T[tot].k=1;
        x=tot;
    }
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(x==0)
    {
        x=++tot;
        T[x].l=T[x].r=T[x].s=T[x].k=0;
    }
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
ll sum0(int &x,int ls,int rs,int q)
{
    if(x==0) return 0;
    if(ls==rs)
    {
        return T[x].s;
    }
    newnode(T[x].l);
    newnode(T[x].r);
    pushdown(x);
    int z=ls+rs>>1;
    if(q<=z) return sum0(T[x].l,ls,z,q);
    else return sum0(T[x].r,z+1,rs,q);
}
int sum(int &x,int ls,int rs,ll k)
{
    if(x==0) return -1;
    if(ls==rs)
    {
        if(T[x].s>k/2) return ls;
        return -1;
    }
    newnode(T[x].l);
    newnode(T[x].r);
    pushdown(x);
    int z=ls+rs>>1;
    if(T[T[x].l].s>=T[T[x].r].s) return sum(T[x].l,ls,z,k);
    else return sum(T[x].r,z+1,rs,k);
}
int merge(int x1,int x2,int ls,int rs)
{
    if(x1==0||x2==0) return x1+x2;
    if(ls==rs)
    {
        T[x1].s=T[x1].s+T[x2].s;
        return x1;
    }
    pushdown(x1);
    pushdown(x2);
    int z=ls+rs>>1;
    T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
    T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
    pushup(x1);
    return x1;
}
int merge2(int x1,int x2,int ls,int rs,ll k)
{
    if(x1==0)
    {
        newnode(x2);
        T[x2].s*=k;
        T[x2].k*=k;
        return x2;
    }
    if(x2==0) return x1;
    if(ls==rs)
    {
        T[x1].s=T[x1].s+T[x2].s*k;
        return x1;
    }
    newnode(T[x1].l);
    newnode(T[x1].r);
    pushdown(x1);
    int z=ls+rs>>1;
    T[x1].l=merge2(T[x1].l,T[x2].l,ls,z,k);
    T[x1].r=merge2(T[x1].r,T[x2].r,z+1,rs,k);
    pushup(x1);
    return x1;
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i)
    {
        int k;
        read(k);
        for(int j=1;j<=k;++j)
        {
            int x;
            read(x);
            d[i].push_back(x);
            add(rt[i],1,n+m,x,1);
        }
    }
    for(int i=1;i<=n+m;++i) fa[i]=i;
    for(int o=1;o<=m;++o)
    {
        int z;
        read(z);
        if(z==1)
        {
            int x,k;
            read(x),read(k);
            x=find(x);
            d[x].push_back(k);
            add(rt[x],1,n+m,k,1);
        }
        else if(z==2)
        {
            int x;
            read(x);
            x=find(x);
            add(rt[x],1,n+m,d[x].back(),-1);
            d[x].pop_back();
        }
        else if(z==3)
        {
            int k;
            read(k);
            ll w=0;
            for(int i=1;i<=k;++i)
            {
                read(b[i]);
                b[i]=find(b[i]);
                c[b[i]]=0;
                w+=d[b[i]].size();
            }
            for(int i=1;i<=k;++i) ++c[b[i]];
            int z=tot;
            rt[0]=0;
            for(int i=1;i<=k;++i)
            {
                if(c[b[i]]!=0)
                {
                    int z1=rt[0];
                    newnode(z1);
                    rt[0]=merge2(z1,rt[b[i]],1,n+m,c[b[i]]);
                    c[b[i]]=0;
                }
            }
            int u=sum(rt[0],1,n+m,w);
            print(u);
            putchar('\n');
            tot=z;
        }
        else if(z==4)
        {
            int x1,x2,x3;
            read(x1),read(x2),read(x3);
            x1=find(x1);
            x2=find(x2);
            x3=find(x3);
            if(d[x1].size()>=d[x2].size())
            {
                while(!d[x2].empty()) d[x1].push_back(d[x2].front()),d[x2].pop_front();
                fa[x2]=fa[x3]=x1;
            }
            else
            {
                while(!d[x1].empty()) d[x2].push_front(d[x1].back()),d[x1].pop_back();
                fa[x1]=fa[x3]=x2;
                swap(x1,x2);
            }
            rt[x1]=merge(rt[x1],rt[x2],1,n+m);
        }
    }
    return 0;
}