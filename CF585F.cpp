#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2001,M=61;
const ll P=1e9+7;
int n,m,tot=1,a[N*M][10],fl[N*M],c[N];
ll f[M][N*M][2][2];
bool h[N*M];
char b[N],b1[N],b2[N];
void add(char *x)
{
    int q=1;
    for(int i=1;x[i]&&i<=m/2;++i)
    {
        if(a[q][x[i]-'0']==0) a[q][x[i]-'0']=++tot;
        q=a[q][x[i]-'0'];
    }
    h[q]=true;
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=9;++i) a[0][i]=1;
    fl[1]=0;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=9;++i)
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
ll dfs(int x,int t,bool u,bool v)
{
    if(x==m+1) return v;
    if(f[x][t][u][v]!=-1) return f[x][t][u][v];
    f[x][t][u][v]=0;
    int p=u?c[x]:9;
    for(int i=0;i<=p;++i)
    {
        f[x][t][u][v]=(f[x][t][u][v]+dfs(x+1,a[t][i],u&&i==p,v||h[a[t][i]]))%P;
    }
    return f[x][t][u][v];
}
int main()
{
    scanf("%s%s%s",b+1,b1+1,b2+1);
    n=strlen(b+1);
    m=strlen(b1+1);
    for(int i=1;i<=n-m/2+1;++i) add(b+i-1);
    bfs();
    for(int i=1;i<=m;++i) c[i]=b1[i]-'0';
    --c[m];
    for(int i=m;i>=1&&c[i]<0;++i) --c[i-1],c[i]+=10;
    memset(f,-1,sizeof(f));
    ll s1=dfs(1,1,true,false);
    for(int i=1;i<=m;++i) c[i]=b2[i]-'0';
    memset(f,-1,sizeof(f));
    ll s2=dfs(1,1,true,false);
    // printf("%lld %lld\n",s1,s2);
    printf("%lld\n",((s2-s1)%P+P)%P);
    return 0;
}