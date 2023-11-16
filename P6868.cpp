#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200001;
int n,q1,q2,b[N][2],c1[N],c2[N],d[N],fa[N],g[N],g1[N],g2[N];
bool h[N];
struct str
{
    int x,y,t;
}a[N];
struct tree
{
    int l,r,s;
}T[N<<2];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=-1e9;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void change(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) change(x<<1,q,k);
    else change(x<<1|1,q,k);
    pushup(x);
}
int num(int x,int q)
{
    if(T[x].l==T[x].r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return num(x<<1,q);
    else return num(x<<1|1,q);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1,s=-1e9;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
bool cmp(str a,str b)
{
    return a.y<b.y;
}
void dfs(int x)
{
    if(x==n+1)
    {
        printf("DA\n");
        for(int i=1;i<=n;++i)
        {
            if(i<b[i][d[i]])
            {
                printf("%d %d\n",a[i].t,a[b[i][d[i]]].t);
            }
        }
        exit(0);
    }
    if(h[x]==true)
    {
        dfs(x+1);
        return;
    }
    if(b[x][0]!=0&&h[b[x][0]]==false&&g[find(x)]!=-1&&sum(1,min(a[x].x,a[b[x][0]].x),max(a[x].x,a[b[x][0]].x))<a[x].y)
    {
        int p=g[find(x)];
        g[find(x)]=1;
        d[x]=d[b[x][0]]=0;
        h[x]=h[b[x][0]]=true;
        dfs(x+1);
        h[x]=h[b[x][0]]=false;
        g[find(x)]=p;
    }
    if(b[x][1]!=0&&h[b[x][1]]==false&&g[find(x)]!=1)
    {
        int p=g[find(x)];
        g[find(x)]=-1;
        d[x]=d[b[x][1]]=1;
        h[x]=h[b[x][1]]=true;
        int z=num(1,a[x].x);
        if(max(a[x].y,a[b[x][1]].y)>z) change(1,a[x].x,max(a[x].y,a[b[x][1]].y));
        dfs(x+1);
        if(max(a[x].y,a[b[x][1]].y)>z) change(1,a[x].x,z);
        h[x]=h[b[x][1]]=false;
        g[find(x)]=p;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].t=i;
        c1[i]=a[i].x;
        c2[i]=a[i].y;
    }
    sort(c1+1,c1+n+1);
    sort(c2+1,c2+n+1);
    q1=unique(c1,c1+n+1)-c1-1;
    q2=unique(c2,c2+n+1)-c2-1;
    for(int i=1;i<=n;++i)
    {
        a[i].x=lower_bound(c1+1,c1+q1+1,a[i].x)-c1;
        a[i].y=lower_bound(c2+1,c2+q2+1,a[i].y)-c2;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        if(g1[a[i].y]!=0)
        {
            b[i][0]=g1[a[i].y];
            b[g1[a[i].y]][0]=i;
        }
        else g1[a[i].y]=i;
        if(g2[a[i].x]!=0)
        {
            b[i][1]=g2[a[i].x];
            b[g2[a[i].x]][1]=i;
        }
        else g2[a[i].x]=i;
    }
    queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(b[i][0]==0||b[i][1]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(b[k][0]==0&&b[k][1]==0)
        {
            printf("NE");
            return 0;
        }
        if(b[k][1]==0&&b[b[k][0]][1]!=0)
        {
            Q.push(b[b[k][0]][1]);
            b[b[b[k][0]][1]][1]=0;
            b[b[k][0]][1]=0;
        }
        else if(b[k][0]==0&&b[b[k][1]][0]!=0)
        {
            Q.push(b[b[k][1]][0]);
            b[b[b[k][1]][0]][0]=0;
            b[b[k][1]][0]=0;
        }
    }
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=n;++i)
    {
        if(b[i][0]!=0&&find(i)!=find(b[i][0]))
        {
            fa[find(i)]=find(b[i][0]);
        }
        if(b[i][1]!=0&&find(i)!=find(b[i][1]))
        {
            fa[find(i)]=find(b[i][1]);
        }
    }
    build(1,1,q1);
    dfs(1);
    printf("NE");
    return 0;
}