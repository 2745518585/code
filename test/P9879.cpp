#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001,M=201;
const short dx[9]={-1,-1,-1,0,0,0,1,1,1},dy[9]={-1,0,1,-1,0,1,-1,0,1};
int m,n,p=1,s1,s2,t[N],t0[N],f[N];
char b[M][M];
struct road
{
    int m,q,r;
}a[N<<1];
void road(int x,int y,int r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i) f[i]=0;
    f[s1]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
int dfs(int x,int r)
{
    if(x==s2) return r;
    int s=0;
    for(int i=t0[x];i;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r)
        {
            int z=dfs(a[i].m,min(r,a[i].r));
            if(z)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
inline int sum(int x,int y)
{
    return (x-1)*(n-1)+y;
}
inline bool check(int x,int y)
{
    return x>=1&&x<=m-1&&y>=1&&y<=n-1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;++i)
        {
            scanf("%s",b[i]+1);
            for(int j=1;j<=n;++j)
            {
                if((i+j)%2&&b[i][j]!='?') b[i][j]='W'+'B'-b[i][j];
            }
        }
        s1=(m-1)*(n-1)*2+1,s2=(m-1)*(n-1)*2+2;
        p=1;
        for(int i=1;i<=s2;++i) t[i]=0;
        int q=0;
        for(int i=1;i<=m-1;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                if(b[i][j]!='B'&&b[i+1][j]!='B'&&b[i][j+1]!='B'&&b[i+1][j+1]!='B')
                {
                    road(s1,sum(i,j),1);
                    ++q;
                }
                if(b[i][j]!='W'&&b[i+1][j]!='W'&&b[i][j+1]!='W'&&b[i+1][j+1]!='W')
                {
                    road(sum(i,j)+(m-1)*(n-1),s2,1);
                    ++q;
                }
                for(int k=0;k<9;++k)
                {
                    if(check(i+dx[k],j+dy[k])) road(sum(i,j),sum(i+dx[k],j+dy[k])+(m-1)*(n-1),1e9);
                }
            }
        }
        int r=0;
        while(bfs())
        {
            for(int i=1;i<=s2;++i) t0[i]=t[i];
            r+=dfs(s1,1e9);
        }
        printf("%d\n",q-r);
        for(int i=1;i<=m-1;++i)
        {
            for(int j=1;j<=n-1;++j)
            {
                if((f[sum(i,j)]!=0)==(f[s1]!=0))
                {
                    for(int k=t[sum(i,j)];k!=0;k=a[k].q)
                    {
                        if(a[k].m==s1)
                        {
                            b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]='W';
                        }
                    }
                }
                if((f[sum(i,j)+(m-1)*(n-1)]!=0)==(f[s2]!=0))
                {
                    for(int k=t[sum(i,j)+(m-1)*(n-1)];k!=0;k=a[k].q)
                    {
                        if(a[k].m==s2)
                        {
                            b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]='B';
                        }
                    }
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(b[i][j]=='?') b[i][j]='W';
                if((i+j)%2) printf("%c",'W'+'B'-b[i][j]);
                else printf("%c",b[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}