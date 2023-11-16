#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=2000001,M=26;
int n,m,tot=1,a[N][M],f[N],g[N],h[N];
char b[N];
struct Segment_tree
{
    struct tree
    {
        int l,r,s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s=1e9;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k)
    {
        if(T[x].l==T[x].r)
        {
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(l>r) return 1e9;
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}T;
void build(char x[],int t)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++tot;
        k=a[k][x[i]-'a'];
    }
    g[t]=k;
    h[k]=strlen(x+1);
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=25;++i) a[0][i]=1;
    f[1]=0;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=25;++i)
        {
            if(a[k][i])
            {
                f[a[k][i]]=a[f[k]][i];
                h[a[k][i]]=max(h[a[k][i]],h[a[f[k]][i]]);
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f[k]][i];
        }
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n;++i)
    {
        char x[N];
        scanf("%s",x+1);
        build(x,i);
    }
    bfs();
    m=strlen(b+1);
    T.build(1,1,m+1);
    T.add(1,1,0);
    int x=1;
    for(int i=1;i<=m;++i)
    {
        x=a[x][b[i]-'a'];
        T.add(1,i+1,T.sum(1,i-h[x]+1,i)+1);
    }
    int z=T.sum(1,m+1,m+1);
    printf("%d",z>=1e9?-1:z);
    return 0;
}