#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
const int N=200001;
int n,m,q,tot,a[N],rt[N],rt2[N];
struct tree
{
    int l,r,s;
}T[N<<6];
map<string,int> Map;
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
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='s')
        {
            ++q;
            rt[q]=rt[q-1];
            rt2[q]=rt2[q-1];
            string z;
            cin>>z;
            int x=Map[z],k;
            if(x==0) x=Map[z]=++n;
            scanf("%d",&k);
            int p=sum(rt2[q],1,1e5,x,x);
            if(p!=0) add(rt[q],1,1e9,p,-1);
            add(rt[q],1,1e9,k,1);
            add(rt2[q],1,1e5,x,k-p);
        }
        else if(z[0]=='r')
        {
            ++q;
            rt[q]=rt[q-1];
            rt2[q]=rt2[q-1];
            string z;
            cin>>z;
            if(!Map.count(z)) continue;
            int x=Map[z],p=sum(rt2[q],1,1e5,x,x);
            if(p==0) continue;
            add(rt[q],1,1e9,p,-1);
            add(rt2[q],1,1e5,x,-p);
        }
        else if(z[0]=='q')
        {
            ++q;
            rt[q]=rt[q-1];
            rt2[q]=rt2[q-1];
            string z;
            cin>>z;
            if(!Map.count(z))
            {
                printf("-1\n");
                fflush(stdout);
                continue;
            }
            int x=Map[z],p=sum(rt2[q],1,1e5,x,x);
            if(p==0)
            {
                printf("-1\n");
                fflush(stdout);
                continue;
            }
            printf("%d\n",sum(rt[q],1,1e9,1,p-1));
            fflush(stdout);
        }
        else if(z[0]=='u')
        {
            ++q;
            rt[q]=rt[q-1];
            rt2[q]=rt2[q-1];
            int x;
            scanf("%d",&x);
            rt[q]=rt[q-x-1];
            rt2[q]=rt2[q-x-1];
        }
    }
    return 0;
}