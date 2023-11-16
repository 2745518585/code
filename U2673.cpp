#include<cstdio>
#include<algorithm>
using namespace std;
const int N=400001;
int n,m,k,q,tp,s,b[N];
struct str
{
    int x,y;
}a[N];
struct splay
{
    int x,a[2],f,s,t,k,h,w;
}T[N];
void pushup(int x)
{
    T[x].w=min(T[x].h,min(T[T[x].a[0]].w,T[T[x].a[1]].w));
}
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
    pushup(y);
    pushup(x);
}
void splay(int x)
{
    int p[N],t=0,d=x;
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
    pushup(x);
}
void access(int x)
{
    int y=0;
    while(x!=0)
    {
        splay(x);
        T[x].a[1]=y;
        pushup(x);
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
    ++s;
}
void cut(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x&&T[y].f==x&&T[y].a[0]==0)
    {
        --s;
        T[x].a[1]=T[y].f=0;
        pushup(x);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&tp);
    k=n-k;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    for(int i=0;i<=n;++i) T[i].h=T[i].w=1e9;
    for(int i=1;i<=m;++i) T[n+i].h=T[n+i].w=i;
    int x=0;
    for(int i=1;i<=m;++i)
    {
        while(x<m&&s<k*2)
        {
            ++x;
            if(a[x].x!=a[x].y)
            {
                if(findroot(a[x].x)==findroot(a[x].y))
                {
                    get(a[x].x,a[x].y);
                    int z=T[a[x].x].w;
                    cut(a[z].x,n+z);
                    cut(a[z].y,n+z);
                }
                add(a[x].x,n+x);
                add(a[x].y,n+x);
            }
        }
        if(s*2>=k) b[i]=x;
        else b[i]=1e9;
        cut(a[i].x,n+i);
        cut(a[i].y,n+i);
    }
    scanf("%d",&q);
    unsigned las=0;
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(tp==1)
        {
            x=(x+las)%m+1;
            y=(y+las)%m+1;
            if(x>y) swap(x,y);
        }
        las<<=1;
        if(y>=b[x]) 
        {
            ++las;
            printf("Yes\n");
        }
        else printf("No\n");
    }
    return 0;
}