#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,t,l[N],g[N<<3];
ll f[N<<3],c0[N<<1],*c[N];
char a[N<<3],b0[N<<1],*b[N];
namespace sgt
{
    struct tree
    {
        int s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int ls,int rs)
    {
        if(ls==rs)
        {
            T[x].s=ls-l[g[ls]]+1;
            return;
        }
        int z=ls+rs>>1;
        build(x<<1,ls,z);
        build(x<<1|1,z+1,rs);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r,int k)
    {
        if(T[x].s>k) return 0;
        if(ls==rs) return ls;
        int z=ls+rs>>1;
        if(r>z)
        {
            int p=sum(x<<1|1,z+1,rs,l,r,k);
            if(p) return p;
        }
        if(l<=z) return sum(x<<1,ls,z,l,r,k);
        return 0;
    }
}
struct AC
{
    int tot=1,a[N][26],fl[N],g[N],f[N];
    vector<int> d[N];
    void add(char *x,int t)
    {
        int q=1;
        for(int i=1;x[i];++i)
        {
            if(a[q][x[i]-'a']==0) a[q][x[i]-'a']=++tot;
            q=a[q][x[i]-'a'];
        }
        f[q]=1;
        g[q]=t;
    }
    void bfs()
    {
        queue<int> Q;
        for(int i=0;i<=25;++i) a[0][i]=1;
        fl[1]=0;
        Q.push(1);
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(int i=0;i<=25;++i)
            {
                if(a[k][i])
                {
                    fl[a[k][i]]=a[fl[k]][i];
                    Q.push(a[k][i]);
                }
                else a[k][i]=a[fl[k]][i];
            }
        }
    }
    void solve()
    {
        for(int i=2;i<=tot;++i)
        {
            d[fl[i]].push_back(i);
        }
        queue<int> Q;
        Q.push(1);
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(auto i:d[k])
            {
                f[i]+=f[fl[i]];
                if(l[g[fl[i]]]>l[g[i]]) g[i]=g[fl[i]];
                Q.push(i);
            }
        }
    }
}AC1,AC2;
int main()
{
    scanf("%d%d%s",&n,&m,a+1);
    t=strlen(a+1);
    b[0]=b0;
    c[0]=c0;
    for(int i=1;i<=n;++i)
    {
        b[i]=b[i-1]+l[i-1]+1;
        c[i]=c[i-1]+l[i-1]+1;
        scanf("%s",b[i]+1);
        l[i]=strlen(b[i]+1);
        AC1.add(b[i],i);
        for(int j=1;j<=l[i]/2;++j) swap(b[i][j],b[i][l[i]-j+1]);
        AC2.add(b[i],i);
        for(int j=1;j<=l[i]/2;++j) swap(b[i][j],b[i][l[i]-j+1]);
    }
    AC1.bfs();
    AC2.bfs();
    AC1.solve();
    AC2.solve();
    int x=1;
    for(int i=1;i<=t;++i)
    {
        x=AC1.a[x][a[i]-'a'];
        f[i]=f[i-1]+AC1.f[x];
        g[i]=AC1.g[x];
    }
    for(int i=1;i<=n;++i)
    {
        int x=1;
        for(int j=l[i];j>=1;--j)
        {
            x=AC2.a[x][b[i][j]-'a'];
            c[i][l[i]-j+1]=c[i][l[i]-j]+AC2.f[x];
        }
    }
    sgt::build(1,1,t);
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int x=sgt::sum(1,1,t,l,r,l);
        if(x==0)
        {
            printf("%lld ",f[r]-f[l-1]);
            continue;
        }
        printf("%lld ",f[r]-f[x]+c[g[x]][x-l+1]);
    }
    return 0;
}