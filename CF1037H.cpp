#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=1000001,M=30;
int n,m,las=1,tot=1,tot2,p=1,t[N],f[N],e[N][2],h[N];
char b[N],c[N];
struct str
{
    int l,r,t,k;
    char *x;
}d[N];
bool cmp(str a,str b)
{
    return a.r<b.r;
}
namespace Segment_tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=max(T[x].s,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s=max(s,sum(x<<1,l,r));
        if(r>z) s=max(s,sum(x<<1|1,l,r));
        return s;
    }
}
struct tree
{
    int s[M],l,f,b,bm;
}a[N];
struct road
{
    int m,q;
}a2[N];
void road(int x,int y)
{
    a2[++p].m=y;
    a2[p].q=t[x];
    t[x]=p;
}
void add(int c,int t)
{
    int x=las,nx=las=++tot;
    f[t]=nx;
    a[nx].l=a[x].l+1;
    while(x!=0&&a[x].s[c]==0)
    {
        a[x].s[c]=nx;
        x=a[x].f;
    }
    if(x==0) a[nx].f=1;
    else
    {
        int y=a[x].s[c];
        if(a[x].l+1==a[y].l) a[nx].f=y;
        else
        {
            int ny=++tot;
            a[ny]=a[y];
            a[ny].l=a[x].l+1;
            a[y].f=a[nx].f=ny;
            while(x!=0&&a[x].s[c]==y)
            {
                a[x].s[c]=ny;
                x=a[x].f;
            }
        }
    }
}
void dfs(int x,int fa)
{
    a[x].b=++tot2;
    for(int i=t[x];i!=0;i=a2[i].q)
    {
        if(a2[i].m==fa) continue;
        dfs(a2[i].m,x);
    }
    a[x].bm=tot2;
}
int check(int x)
{
    return Segment_tree::sum(1,a[x].b,a[x].bm);
}
bool solve(int x,int l,int t)
{
    if(l==d[t].t+1)
    {
        for(int i=0;i<=25;++i)
        {
            if(a[x].s[i]!=0&&check(a[x].s[i])-l+1>=d[t].l)
            {
                e[t][0]=l;
                e[t][1]=i;
                return true;
            }
        }
        return false;
    }
    if(a[x].s[d[t].x[l]-'a']!=0&&check(a[x].s[d[t].x[l]-'a'])-l+1>=d[t].l)
    {
        if(solve(a[x].s[d[t].x[l]-'a'],l+1,t)) return true;
    }
    for(int i=d[t].x[l]-'a'+1;i<=25;++i)
    {
        if(a[x].s[i]!=0&&check(a[x].s[i])-l+1>=d[t].l)
        {
            e[t][0]=l;
            e[t][1]=i;
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%s",b+1);
    n=strlen(b+1);
    for(int i=1;i<=n;++i) add(b[i]-'a',i);
    for(int i=2;i<=tot;++i) road(a[i].f,i);
    dfs(1,0);
    scanf("%d",&m);
    int z=0;
    for(int i=1;i<=m;++i)
    {
        d[i].x=c+z;
        scanf("%d%d%s",&d[i].l,&d[i].r,c+z+1);
        d[i].t=strlen(c+z+1);
        z+=d[i].t+1;
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    for(int i=1;i<=m;++i) h[d[i].k]=i;
    Segment_tree::build(1,1,tot);
    for(int i=1;i<=m;++i)
    {
        for(int j=d[i-1].r+1;j<=d[i].r;++j)
        {
            Segment_tree::add(1,a[f[j]].b,j);
        }
        if(!solve(1,1,i)) e[i][0]=-1;
    }
    for(int i=1;i<=m;++i)
    {
        if(e[h[i]][0]==-1)
        {
            printf("-1\n");
            continue;
        }
        for(int j=1;j<=e[h[i]][0]-1;++j) printf("%c",d[h[i]].x[j]);
        printf("%c\n",e[h[i]][1]+'a');
    }
    return 0;
}