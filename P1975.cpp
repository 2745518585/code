#include<cstdio>
#include<algorithm>
using namespace std;
const int N=40001,M=2000001;
int n,m,r=0,q=0,a[N];
struct Treap
{
    struct tree
    {
        int k,l,r,s,h,t; 
    };
    tree T[M];
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
    void add(int &x,int k)
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
    void remove(int &x,int k)
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
    int num1(int x,int k)
    {
        if(x==0) return 0;
        if(k==T[x].k) return T[T[x].l].s;
        if(k<T[x].k) return num1(T[x].l,k);
        return T[T[x].l].s+T[x].t+num1(T[x].r,k);
    }
    int num2(int x,int k)
    {
        if(x==0) return 0;
        if(k==T[x].k) return T[T[x].r].s;
        if(k>T[x].k) return num2(T[x].r,k);
        return T[T[x].r].s+T[x].t+num2(T[x].l,k);
    }
}Treap;
struct Segment_tree
{
    struct tree
    {
        int l,r,rt;
    }T[N<<2];
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        for(int i=l;i<=r;++i)
        {
            Treap.add(T[x].rt,a[i]);
        }
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
    }
    void change(int x,int q,int k)
    {
        Treap.remove(T[x].rt,a[q]);
        Treap.add(T[x].rt,k);
        if(T[x].l==T[x].r) return;
        int z=T[x].l+T[x].r>>1;
        if(q<=z) change(x<<1,q,k);
        else change(x<<1|1,q,k);
    }
    int num1(int x,int l,int r,int k)
    {
        if(l>r) return 0;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return Treap.num1(T[x].rt,k);
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s+=num1(x<<1,l,r,k);
        if(r>z) s+=num1(x<<1|1,l,r,k);
        return s;
    }
    int num2(int x,int l,int r,int k)
    {
        if(l>r) return 0;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return Treap.num2(T[x].rt,k);
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s+=num2(x<<1,l,r,k);
        if(r>z) s+=num2(x<<1|1,l,r,k);
        return s;
    }
};
int main()
{
    scanf("%d",&n);
    srand(n);
    Segment_tree T;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    T.build(1,1,n);
    int s=0;
    for(int i=1;i<=n-1;++i)
    {
        s+=T.num1(1,i+1,n,a[i]);
    }
    printf("%d\n",s);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>y) swap(x,y);
        s+=T.num2(1,x+1,y-1,a[x])-T.num1(1,x+1,y-1,a[x]);
        s+=T.num1(1,x+1,y-1,a[y])-T.num2(1,x+1,y-1,a[y]);
        if(a[x]<a[y]) ++s;
        else if(a[x]>a[y]) --s;
        T.change(1,x,a[y]);
        T.change(1,y,a[x]);
        swap(a[x],a[y]);
        printf("%d\n",s);
    }
    return 0;
}