#include<cstdio>
#include<algorithm>
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
const int N=500001,M=3001;
const short dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int m,n,a[N][2],b[M][M];
bool h[M][M];
namespace LCT
{
    struct splay
    {
        int a[2],f,k;
    }T[N];
    bool check(int x)
    {
        return T[T[x].f].a[0]!=x&&T[T[x].f].a[1]!=x;
    }
    void turn(int x)
    {
        swap(T[x].a[0],T[x].a[1]);
        T[x].k^=1;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        if(T[x].a[0]) turn(T[x].a[0]);
        if(T[x].a[1]) turn(T[x].a[1]);
        T[x].k=0;
    }
    void rotate(int x)
    {
        int y=T[x].f,z=T[y].f,k=T[y].a[1]==x;
        if(!check(y)) T[z].a[T[z].a[1]==y]=x;
        T[x].f=z;
        T[y].a[k]=T[x].a[k^1];
        T[T[x].a[k^1]].f=y;
        T[x].a[k^1]=y;
        T[y].f=x;
    }
    void splay(int x)
    {
        static int p[N];
        int t=0,d=x;
        p[++t]=x;
        while(!check(d)) p[++t]=d=T[d].f;
        for(int i=t;i>=1;--i) pushdown(p[i]);
        while(!check(x))
        {
            int y=T[x].f,z=T[T[x].f].f;
            if(!check(y))
            {
                if(((T[y].a[0]==x)^(T[z].a[0]==y))==1) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
    void access(int x)
    {
        int y=0;
        while(x!=0)
        {
            splay(x);
            T[x].a[1]=y;
            y=x;
            x=T[x].f;
        }
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        turn(x);
    }
    int findroot(int x)
    {
        access(x);
        splay(x);
        while(T[x].a[0]!=0)
        {
            pushdown(x);
            x=T[x].a[0];
        }
        splay(x);
        return x;
    }
    void get(int x,int y)
    {
        makeroot(y);
        access(x);
        splay(x);
    }
    void add(int x,int y)
    {
        if(findroot(x)==findroot(y)) return;
        makeroot(x);
        T[x].f=y;
    }
    void cut(int x,int y)
    {
        makeroot(x);
        if(findroot(y)==x&&T[y].f==x&&T[y].a[0]==0)
        {
            T[x].a[1]=T[y].f=0;
        }
    }
}
namespace sgt
{
    struct tree
    {
        int l,r,s,t,k;
    }T[N<<2];
    void pushup(tree &T,tree T1,tree T2)
    {
        if(T1.s==T2.s) T.s=T1.s,T.t=T1.t+T2.t;
        else if(T1.s>T2.s) T.s=T1.s,T.t=T1.t;
        else T.s=T2.s,T.t=T2.t;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        if(l==r)
        {
            T[x].s=-l;
            T[x].t=1;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(T[x],T[x<<1],T[x<<1|1]);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(T[x],T[x<<1],T[x<<1|1]);
    }
    tree sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x];
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        tree s;
        if(r<=z) s=sum(x<<1,l,r);
        else if(l>z) s=sum(x<<1|1,l,r);
        else pushup(s,sum(x<<1,l,r),sum(x<<1|1,l,r));
        return s;
    }
}
int sum(int x,int y)
{
    return (x-1)*n+y;
}
bool check(int x,int y)
{
    int z[4];
    for(int i=0;i<=3;++i)
    {
        if(h[x+dx[i]][y+dy[i]]) z[i]=LCT::findroot(sum(x+dx[i],y+dy[i]));
        else z[i]=-i;
        for(int j=0;j<=i-1;++j) if(z[i]==z[j]) return false;
    }
    return true;
}
void add(int x,int y)
{
    h[x][y]=true;
    for(int i=0;i<=3;++i)
    {
        if(h[x+dx[i]][y+dy[i]]) LCT::add(sum(x,y),sum(x+dx[i],y+dy[i]));
        if(b[x+dx[i]][y+dy[i]]>b[x][y])
        {
            sgt::add(1,b[x+dx[i]][y+dy[i]],m*n,1);
            // printf("add %d\n",b[x+dx[i]][y+dy[i]]);
        }
    }
}
void del(int x,int y)
{
    h[x][y]=false;
    for(int i=0;i<=3;++i)
    {
        if(h[x+dx[i]][y+dy[i]]) LCT::cut(sum(x,y),sum(x+dx[i],y+dy[i]));
        if(b[x+dx[i]][y+dy[i]]>b[x][y])
        {
            sgt::add(1,b[x+dx[i]][y+dy[i]],m*n,-1);
            // printf("del %d\n",b[x+dx[i]][y+dy[i]]);
        }
    }
}
int main()
{
    read(m),read(n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            read(x);
            a[x][0]=i,a[x][1]=j;
            b[i][j]=x;
        }
    }
    sgt::build(1,1,m*n);
    int x=0;
    ll s=0;
    for(int i=1;i<=m*n;++i)
    {
        while(x+1<=m*n&&check(a[x+1][0],a[x+1][1]))
        {
            ++x;
            add(a[x][0],a[x][1]);
        }
        auto z=sgt::sum(1,i,x);
        if(z.s==-i) s+=z.t;
        // printf("%d %d %d %d\n",i,x,z.s,z.t);
        del(a[i][0],a[i][1]);
    }
    printf("%lld",s);
    return 0;
}