#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef unsigned long long ull;
const int N=2000001;
int n,m,l[N],h[N];
ull b1[N],b2[N],f1[N],f2[N],g1[N],g2[N];
char a[N];
vector<int> d[N];
struct SAM
{
    int las=1,tot=1,b[N],fa[N][21];
    struct tree
    {
        int s[26],l,f;
    }a[N];
    int add(int c)
    {
        int x=las,nx=las=++tot;
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
        return nx;
    }
    void init()
    {
        for(int i=1;i<=tot;++i) fa[i][0]=a[i].f;
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=tot;++j)
            {
                fa[j][i]=fa[fa[j][i-1]][i-1];
            }
        }
    }
    int find(int p,int l)
    {
        int x=b[p],t=0;
        while(t>=0)
        {
            if(fa[x][t]!=0&&a[fa[x][t]].l>=l) x=fa[x][t],++t;
            else --t;
        }
        return x;
    }
}S1,S2;
void dfs(int x)
{
    for(auto i:d[x])
    {
        g1[i]+=g1[x];
        dfs(i);
    }
}
int main()
{
    scanf("%d%d%s",&n,&m,a+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%llu",&b1[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%llu",&b2[i]);
    }
    for(int i=1;i<=n;++i) S1.b[i]=S1.add(a[i]-'A');
    for(int i=n;i>=1;--i) S2.b[i]=S2.add(a[i]-'A');
    S1.init();
    for(int i=1;i<=n;++i) b2[i]+=b2[i-1];
    for(int i=1;i<=n;++i)
    {
        f1[S1.b[i]]=b2[i];
        f2[S1.b[i]]=b2[i-1];
    }
    queue<int> Q;
    for(int i=2;i<=S1.tot;++i) ++l[S1.a[i].f];
    for(int i=1;i<=S1.tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        f1[S1.a[k].f]+=f1[k];
        f2[S1.a[k].f]+=f2[k];
        --l[S1.a[k].f];
        if(l[S1.a[k].f]==0) Q.push(S1.a[k].f);
    }
    for(int i=1;i<=n;++i)
    {
        int x=S2.b[i];
        while(x&&!h[x])
        {
            h[x]=i;
            x=S2.a[x].f;
        }
    }
    for(int i=2;i<=S2.tot;++i)
    {
        int x=S1.find(h[i]+S2.a[i].l-1,S2.a[i].l);
        g1[i]+=f1[x];
        x=S1.find(h[i]+S2.a[S2.a[i].f].l,S2.a[S2.a[i].f].l+1);
        g1[i]-=f2[x];
    }
    for(int i=1;i<=n;++i) ++g2[S2.b[i]];
    for(int i=2;i<=S2.tot;++i) ++l[S2.a[i].f];
    for(int i=1;i<=S2.tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        g2[S2.a[k].f]+=g2[k];
        --l[S2.a[k].f];
        if(l[S2.a[k].f]==0) Q.push(S2.a[k].f);
    }
    for(int i=1;i<=S2.tot;++i) g1[i]*=g2[i];
    for(int i=2;i<=S2.tot;++i)
    {
        d[S2.a[i].f].push_back(i);
    }
    dfs(1);
    ull s=0;
    for(int i=1;i<=n;++i)
    {
        s+=b1[i]*g1[S2.b[i]];
    }
    printf("%llu\n",s);
    for(int i=1;i<=m;++i)
    {
        int x;
        ull k;
        scanf("%d%llu",&x,&k);
        s+=(k-b1[x])*g1[S2.b[x]];
        b1[x]=k;
        printf("%llu\n",s);
    }
    return 0;
}