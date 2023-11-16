#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=21;
int n,m,tot,b[N],c[N],d[N],fa[N][M],T[N];
vector<int> a[N];
void dfs(int x,int fa)
{
    b[x]=++tot;
    d[x]=d[fa]+1;
    for(auto i:a[x]) dfs(i,x);
    c[x]=tot;
}
void add(int x,int k)
{
    while(x<=n) T[x]+=k,x+=x&-x;
}
int sum(int x)
{
    int s=1;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
int find(int x,int y)
{
    int t=0;
    while(t>=0)
    {
        if(d[fa[x][t]]>d[y]) x=fa[x][t],++t;
        else --t;
    }
    if(fa[x][0]==y) return x;
    return 0;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        tot=0;
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=2;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            a[x].push_back(i);
            fa[i][0]=x;
        }
        fa[1][0]=0;
        for(int i=1;i<=20;++i)
        {
            for(int j=1;j<=n;++j) fa[j][i]=fa[fa[j][i-1]][i-1];
        }
        dfs(1,0);
        for(int i=1;i<=n;++i) T[i]=0;
        int x=1,y=0;
        add(b[1],1);
        for(int i=2;i<=n;++i)
        {
            add(b[i],1);
            int p=find(i,x);
            if(p==0)
            {
                int z=i-(sum(c[x])-sum(b[x]-1));
                if(z>i/2) x=fa[x][0],y=i-z;
                else y=max(y,z);
            }
            else
            {
                int z=sum(c[p])-sum(b[p]-1);
                if(z>i/2) x=p,y=i-z;
                else y=max(y,z);
            }
            printf("%d ",i-y*2);
        }
        printf("\n");
    }
    return 0;
}