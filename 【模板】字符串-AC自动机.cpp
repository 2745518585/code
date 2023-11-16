#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=2000001,M=26;
int n,m,tot=1,a[N][M],f[N],g[N],h[N],l[N];
char b[N];
void build(char x[],int t)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++tot;
        k=a[k][x[i]-'a'];
    }
    g[t]=k;
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
                ++l[a[f[k]][i]];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f[k]][i];
        }
    }
}
void tpsort()
{
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        h[f[k]]+=h[k];
        --l[f[k]];
        if(l[f[k]]==0) Q.push(f[k]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        char x[N];
        scanf("%s",x+1);
        build(x,i);
    }
    bfs();
    scanf("%s",b+1);
    m=strlen(b+1);
    int x=1;
    for(int i=1;i<=m;++i)
    {
        x=a[x][b[i]-'a'];
        ++h[x];
    }
    tpsort();
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",h[g[i]]);
    }
    return 0;
}