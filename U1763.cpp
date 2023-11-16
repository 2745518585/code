#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int m,rt1,rt2,q=0;
struct splay
{
    int x,a[2],f,s,t;
}T[N];
void pushup(int x)
{
    T[x].s=T[T[x].a[0]].s+T[T[x].a[1]].s+T[x].t;
}
void rotate(int x)
{
    int y=T[x].f,z=T[y].f,k=T[y].a[1]==x;
    T[z].a[T[z].a[1]==y]=x;
    T[x].f=z;
    T[y].a[k]=T[x].a[k^1];
    T[T[x].a[k^1]].f=y;
    T[x].a[k^1]=y;
    T[y].f=x;
    pushup(y);
    pushup(x);
}
void splay(int &rt,int x,int k)
{
    while(T[x].f!=k)
    {
        int y=T[x].f,z=T[T[x].f].f;
        if(z!=k)
        {
            if((T[y].a[0]==x)^(T[z].a[0]==y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(k==0) rt=x;
}
void add(int &rt,int &x,int f,int k)
{
    if(x==0)
    {
        x=++q;
        T[x].x=k;
        T[x].t=T[x].s=1;
        T[x].f=f;
        splay(rt,x,0);
        return;
    }
    if(T[x].x==k)
    {
        ++T[x].t;
        ++T[x].s;
        splay(rt,x,0);
        return;
    }
    else if(k<T[x].x) add(rt,T[x].a[0],x,k);
    else add(rt,T[x].a[1],x,k);
}
void build(int &rt)
{
    add(rt,rt,0,1e9);
    add(rt,rt,0,-1e9);
}
int find(int &rt,int x,int f,int k)
{
    if(x==0)
    {
        splay(rt,f,0);
        return -1;
    }
    if(k==T[x].x) return x;
    if(k<T[x].x) return find(rt,T[x].a[0],x,k);
    return find(rt,T[x].a[1],x,k);
}
int find_f(int &rt,int x,int f,int k)
{
    if(x==0)
    {
        splay(rt,f,0);
        return 0;
    }
    if(k<=T[x].x) return find_f(rt,T[x].a[0],x,k);
    int p=find_f(rt,T[x].a[1],x,k);
    if(p==0) return x;
    return p;
}
int find_b(int &rt,int x,int f,int k)
{
    if(x==0)
    {
        splay(rt,f,0);
        return 0;
    }
    if(k>=T[x].x) return find_b(rt,T[x].a[1],x,k);
    int p=find_b(rt,T[x].a[0],x,k);
    if(p==0) return x;
    return p;
}
void remove(int &rt,int k)
{
    int x=find_f(rt,rt,0,k),y=find_b(rt,rt,0,k);
    splay(rt,x,0);
    splay(rt,y,x);
    --T[T[y].a[0]].t;
    --T[T[y].a[0]].s;
    if(T[T[y].a[0]].t==0)
    {
        T[T[y].a[0]].x=0;
        T[y].a[0]=0;
    }
    splay(rt,y,0);
}
int sum(int &rt,int x,int k)
{
    if(x==0) return 0;
    if(k<T[T[x].a[0]].s+1) return sum(rt,T[x].a[0],k);
    if(k<=T[T[x].a[0]].s+T[x].t)
    {
        splay(rt,x,0);
        return x;
    }
    return sum(rt,T[x].a[1],k-T[T[x].a[0]].s-T[x].t);
}
int num(int &rt,int k)
{
    splay(rt,find_f(rt,rt,rt,k),0);
    return T[T[rt].a[0]].s+T[rt].t;
}
int main()
{
    build(rt1);
    build(rt2);
    scanf("%d",&m);
    int s=0;
    for(int i=1;i<=m;++i)
    {
        int z,k;
        scanf("%d%d",&z,&k);
        if(z==0)
        {
            if(T[rt2].s-2!=0)
            {
                if(find(rt2,rt2,0,k)!=-1)
                {
                    remove(rt2,T[find(rt2,rt2,0,k)].x);
                    continue;
                }
                int x=T[find_f(rt2,rt2,0,k)].x,y=T[find_b(rt2,rt2,0,k)].x;
                if(abs(k-x)<=abs(k-y))
                {
                    s+=abs(k-x);
                    remove(rt2,x);
                }
                else
                {
                    s+=abs(k-y);
                    remove(rt2,y);
                }
            }
            else
            {
                add(rt1,rt1,0,k);
            }
        }
        else if(z==1)
        {
            if(T[rt1].s-2!=0)
            {
                if(find(rt1,rt1,0,k)!=-1)
                {
                    remove(rt1,T[find(rt1,rt1,0,k)].x);
                    continue;
                }
                int x=T[find_f(rt1,rt1,0,k)].x,y=T[find_b(rt1,rt1,0,k)].x;
                if(abs(k-x)<=abs(k-y))
                {
                    s+=abs(k-x);
                    remove(rt1,x);
                }
                else
                {
                    s+=abs(k-y);
                    remove(rt1,y);
                }
            }
            else
            {
                add(rt2,rt2,0,k);
            }
        }
        s%=1000000;
    }
    printf("%d",s);
    return 0;
}