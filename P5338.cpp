#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
const int N=1000001;
int n,m,q=0,rt=0;
typedef unsigned int ui ;
ui randNum( ui& seed , ui last , const ui m){ 
    seed = seed * 17 + last ; return seed % m + 1; 
}
struct str
{
    int s,t;
    friend bool operator <(str a,str b)
    {
        if(a.s!=b.s) return a.s>b.s;
        return a.t<b.t;
    }
    friend bool operator >(str a,str b)
    {
        if(a.s!=b.s) return a.s<b.s;
        return a.t>b.t;
    }
    friend bool operator ==(str a,str b)
    {
        return a.s==b.s&&a.t==b.t;
    }
};
struct Treap
{
    struct tree
    {
        str k;
        int l,r,s,h,t;
    };
    tree T[N];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
    }
    void rotate_l(int &x)
    {
        int p=T[x].r;
        T[x].r=T[p].l;
        T[p].l=x;
        T[p].s=T[x].s;
        x=p;
        pushup(x);
        pushup(T[x].l);
    }
    void rotate_r(int &x)
    {
        int p=T[x].l;
        T[x].l=T[p].r;
        T[p].r=x;
        T[p].s=T[x].s;
        x=p;
        pushup(x);
        pushup(T[x].r);
    }
    void add(int &x,str k)
    {
        if(x==0)
        {
            x=++q;
            T[x].l=T[x].r=0;
            T[x].s=T[x].t=1;
            T[x].k=k;
            T[x].h=rand()*rand()%1000000+1;
            return;
        }
        if(k==T[x].k) ++T[x].t;
        else if(k<T[x].k) add(T[x].l,k);
        else if(k>T[x].k) add(T[x].r,k);
        if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
        if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
        pushup(x);
    }
    void remove(int &x,str k)
    {
        if(x==0) return;
        if(k==T[x].k)
        {
            if(T[x].t>1)
            {
                --T[x].t;
                pushup(x);
                return;
            }
            if(T[x].l==0&&T[x].r==0)
            {
                x=0;
                return;
            }
            if(T[x].l!=0&&(T[x].r==0||T[T[x].l].h<T[T[x].r].h))
            {
                rotate_r(x);
                remove(T[x].r,k);
            }
            else
            {   
                rotate_l(x);
                remove(T[x].l,k);
            }
            pushup(x);
            return;
        }
        if(k<T[x].k) remove(T[x].l,k);
        else remove(T[x].r,k);
        pushup(x);
    }
    int num(int x,str k)
    {
        if(x==0) return 1;
        if(k==T[x].k) return T[T[x].l].s+1;
        if(k<T[x].k) return num(T[x].l,k);
        return T[T[x].l].s+T[x].t+num(T[x].r,k);
    }
};
str a[N];
int main()
{
    int K;
    scanf("%d",&K);
    ui seed,last=7;
    while(K--)
    {
        rt=q=0;
        scanf("%d%d%d",&n,&m,&seed);
        srand(m);
        Treap T;
        for(int i=1;i<=n;++i)
        {
            a[i]=(str){0,0};
            T.add(rt,a[i]);
        }
        for(int i=1;i<=m;++i)
        {
            int x=randNum(seed,last,n),k=randNum(seed,last,n);
            T.remove(rt,a[x]);
            ++a[x].s;
            a[x].t+=k;
            T.add(rt,a[x]);
            last=T.num(rt,a[x])-1;
            printf("%d\n",last);
        }
    }
    return 0;
}