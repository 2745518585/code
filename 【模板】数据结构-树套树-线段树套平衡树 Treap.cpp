#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=2000001;
int n,m,r=0,a[N];
struct Treap
{
    struct tree
    {
        int k,l,r,s,h,t; 
    };
    tree T[M];
    int q=0;
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
    int num(int x,int k)
    {
        if(x==0) return 1;
        if(k==T[x].k) return T[T[x].l].s+1;
        if(k<T[x].k) return num(T[x].l,k);
        return T[T[x].l].s+T[x].t+num(T[x].r,k);
    }
    int find_f(int x,int k)
    {
        if(x==0) return -2147483647;
        if(k<=T[x].k) return find_f(T[x].l,k);
        int p=find_f(T[x].r,k);
        if(p==-2147483647) return T[x].k;
        return p;
    }
    int find_b(int x,int k)
    {
        if(x==0) return 2147483647;
        if(k>=T[x].k) return find_b(T[x].r,k);
        int p=find_b(T[x].l,k);
        if(p==2147483647) return T[x].k;
        return p;
    }
}Treap;
struct Segment_tree
{
    struct tree
    {
        int ls,rs,l,r,rt;
    }T[N<<1];
    int q=0,r=0;
    void build(int &x,int l,int r)
    {
        if(x==0) x=++q;
        T[x].l=l;
        T[x].r=r;
        for(int i=l;i<=r;++i)
        {
            Treap.add(T[x].rt,a[i]);
        }
        if(l==r) return;
        int z=l+r>>1;
        build(T[x].ls,l,z);
        build(T[x].rs,z+1,r);
    }
    void change(int x,int q,int k)
    {
        Treap.remove(T[x].rt,a[q]);
        Treap.add(T[x].rt,k);
        if(T[x].l==T[x].r) return;
        int z=T[x].l+T[x].r>>1;
        if(q<=z) change(T[x].ls,q,k);
        else change(T[x].rs,q,k);
    }
    int num(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return Treap.num(T[x].rt,k)-1;
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s+=num(T[x].ls,l,r,k);
        if(r>z) s+=num(T[x].rs,l,r,k);
        return s;
    }
    int find_f(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return Treap.find_f(T[x].rt,k);
        }
        int z=T[x].l+T[x].r>>1,s=-2147483647;
        if(l<=z) s=max(s,find_f(T[x].ls,l,r,k));
        if(r>z) s=max(s,find_f(T[x].rs,l,r,k));
        return s;
    }
    int find_b(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return Treap.find_b(T[x].rt,k);
        }
        int z=T[x].l+T[x].r>>1,s=2147483647;
        if(l<=z) s=min(s,find_b(T[x].ls,l,r,k));
        if(r>z) s=min(s,find_b(T[x].rs,l,r,k));
        return s;
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    srand(n);
    Segment_tree T;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    T.build(T.r,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",T.num(1,x,y,k)+1);
        }
        else if(z==2)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            int l=0,r=100000000;
            while(l<r)
            {
                int z=l+r+1>>1,p=T.num(1,x,y,z);
                if(p<k) l=z;
                else r=z-1;
            }
            printf("%d\n",l);
        }
        else if(z==3)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            T.change(1,x,k);
            a[x]=k;
        }
        else if(z==4)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",T.find_f(1,x,y,k));
        }
        else if(z==5)
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",T.find_b(1,x,y,k));
        }
    }
    return 0;
}