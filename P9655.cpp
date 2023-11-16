#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,*f[N],s;
bool *g[N];
char b[N];
vector<int> a[N];
struct tree
{
    int f,md,z;
}T[N];
void dfs0(int x)
{
    T[x].md=1;
    T[x].z=0;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs0(i);
        T[x].md=max(T[x].md,T[i].md+1);
        if(T[i].md>T[T[x].z].md) T[x].z=i;
    }
}
void dfs(int x)
{
    int z=b[x]=='('?-1:1;
    if(T[x].z)
    {
        f[T[x].z]=f[x]+z;
        g[T[x].z]=g[x]+z;
        dfs(T[x].z);
    }
    if(z==1)
    {
        if(g[x][1]==false)
        {
            g[x][1]=true;
            f[x][1]=-T[x].md+1;
        }
    }
    // printf("%d:%d\n",x,f[x][1]);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        f[i]=(new int[T[i].md*2+20])+T[i].md+10;
        for(int j=-T[i].md;j<=T[i].md;++j) f[i][j]=0;
        g[i]=(new bool[T[i].md*2+20])+T[i].md+10;
        for(int j=-T[i].md;j<=T[i].md;++j) g[i][j]=0;
        dfs(i);
        for(int j=0;j<=T[i].md;++j)
        {
            if(g[i][j])
            {
                if(g[x][z+j]==false)
                {
                    f[x][z+j]+=f[i][j]+T[i].md-T[x].md+1;
                    g[x][z+j]=true;
                }
                else f[x][z+j]+=f[i][j]+T[i].md;
            }
        }
    }
    // printf("%d:\n",x);
    // for(int i=0;i<=T[x].md;++i) printf("%d ",g[x][i]?f[x][i]+T[x].md:-1);printf("\n");
    if(g[x][0]==true) s=max(s,f[x][0]+T[x].md);
    g[x][-1]=false,f[x][-1]=0;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",b+1);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs0(1);
    f[1]=new int[T[1].md*2+20]+T[1].md+10;
    for(int i=-T[1].md;i<=T[1].md;++i) f[1][i]=0;
    g[1]=new bool[T[1].md*2+20]+T[1].md+10;
    for(int i=-T[1].md;i<=T[1].md;++i) g[1][i]=0;
    dfs(1);
    printf("%d",s);
    return 0;
}