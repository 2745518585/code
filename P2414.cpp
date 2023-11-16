#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001,M=26;
int n,m,tot,a[N][M],a2[N][M],d[N],dm[N],fa[N],f1[N],f2[N],T[N],w[N];
char b[N];
vector<int> c[N];
vector<pair<int,int>> e[N];
void add(int x,int k)
{
    while(x<=tot) T[x]+=k,x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
void dfs(int x)
{
    d[x]=++tot;
    for(auto i:c[x]) dfs(i);
    dm[x]=tot;
}
void dfs2(int x)
{
    add(d[x],1);
    for(auto i:e[x])
    {
        w[i.second]=sum(dm[i.first])-sum(d[i.first]-1);
    }
    for(auto i=0;i<=25;++i)
    {
        if(a2[x][i]!=0) dfs2(a2[x][i]);
    }
    add(d[x],-1);
}
int main()
{
    scanf("%s",b+1);
    tot=1;
    fa[1]=0;
    int q=1,z=strlen(b+1);
    for(int i=1;i<=z;++i)
    {
        if(b[i]=='P') f2[++n]=q;
        else if(b[i]=='B') q=fa[q];
        else
        {
            if(a[q][b[i]-'a']==0) a[q][b[i]-'a']=++tot,fa[tot]=q;
            q=a[q][b[i]-'a'];
        }
    }
    for(int i=1;i<=tot;++i)
    {
        for(int j=0;j<=25;++j) a2[i][j]=a[i][j];
    }
    for(int i=0;i<=25;++i) a[0][i]=1;
    f1[1]=0;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=25;++i)
        {
            if(a[k][i]!=0)
            {
                f1[a[k][i]]=a[f1[k]][i];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f1[k]][i];
        }
    }
    for(int i=2;i<=tot;++i) c[f1[i]].push_back(i);
    tot=0;
    dfs(1);
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        e[f2[y]].push_back(make_pair(f2[x],i));
    }
    dfs2(1);
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",w[i]);
    }
    return 0;
}