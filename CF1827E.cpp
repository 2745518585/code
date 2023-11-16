#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,f1[N],f2[N];
vector<int> a[N];
struct str
{
    int x,y;
}b[N];
struct tree
{
    int f,s,d,t,z;
}T[N];
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    T[x].z=0;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int k)
{
    T[x].t=k;
    if(T[x].z) dfs2(T[x].z,k);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs2(i,i);
    }
}
int LCA(int x,int y)
{
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>T[T[y].t].d) x=T[T[x].t].f;
        else y=T[T[y].t].f;
    }
    if(T[x].d<T[y].d) return x;
    else return y;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear(),f1[i]=f2[i]=i;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&b[i].x,&b[i].y);
        }
        int p=1;
        while(p<n&&a[p].size()==1) ++p;
        T[p].f=0;
        dfs1(p);
        dfs2(p,p);
        for(int i=1;i<=m;++i)
        {
            int z=LCA(b[i].x,b[i].y);
            if(a[b[i].x].size()==1)
            {
                if(T[z].d<T[f1[b[i].x]].d) f1[b[i].x]=z;
            }
            if(a[b[i].y].size()==1)
            {
                if(T[z].d<T[f1[b[i].y]].d) f1[b[i].y]=z;
            }
        }
        int x=0,y=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i].size()==1)
            {
                if(T[f1[i]].d>T[x].d) x=f1[i],y=i;
            }
        }
        T[x].f=0;
        dfs1(x);
        dfs2(x,x);
        for(int i=1;i<=m;++i)
        {
            int z=LCA(b[i].x,b[i].y);
            if(a[b[i].x].size()==1)
            {
                if(T[z].d<T[f2[b[i].x]].d) f2[b[i].x]=z;
            }
            if(a[b[i].y].size()==1)
            {
                if(T[z].d<T[f2[b[i].y]].d) f2[b[i].y]=z;
            }
        }
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i].size()==1)
            {
                if(f2[i]!=x)
                {
                    u=false;
                    printf("NO\n%d %d\n",i,y);
                    break;
                }
            }
        }
        if(u) printf("YES\n");
    }
    return 0;
}