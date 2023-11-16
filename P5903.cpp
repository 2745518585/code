#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
#define ui unsigned int
ui S;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return S = x; 
}
const int N=500001;
int n,m,r,p=1,t[N],lg[N];
vector<int> fa1[N],fa2[N];
struct tree
{
    int f,l,d,t,z,fa[21];
}T[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x)
{
    T[x].l=1;
    T[x].d=T[T[x].f].d+1;
    T[x].fa[0]=T[x].f;
    for(int i=1;i<=20;++i)
    {
        T[x].fa[i]=T[T[x].fa[i-1]].fa[i-1];
    }
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        T[a[i].m].f=x;
        dfs1(a[i].m);
        if(T[a[i].m].l+1>T[x].l)
        {
            T[x].l=T[a[i].m].l+1;
            T[x].z=a[i].m;
        }
    }
}
void dfs2(int x,int k)
{
    fa2[k].push_back(x);
    T[x].t=k;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==T[x].f) continue;
        if(a[i].m==T[x].z) dfs2(a[i].m,k);
        else
        {
            fa1[a[i].m].push_back(a[i].m);
            for(int j=1;j<=T[a[i].m].l;++j)
            {
                fa1[a[i].m].push_back(T[fa1[a[i].m].back()].f);
            }
            dfs2(a[i].m,a[i].m);
        }
    }
}
int find_fa(int x,int k)
{
    if(k==0) return x;
    int q=T[x].d-k;
    x=T[T[x].fa[lg[k]]].t;
    if(T[x].d<q) return fa2[x][q-T[x].d];
    else return fa1[x][T[x].d-q];
    return x;
}
int main()
{
    scanf("%d%d%u",&n,&m,&S);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==0) r=i;
        else road(x,i);
    }
    dfs1(r);
    fa1[r].push_back(r);
    for(int i=1;i<=T[r].l;++i)
    {
        fa1[r].push_back(T[fa1[r].back()].f);
    }
    dfs2(r,r);
    for(int i=1;i<=n;++i) lg[i]=log2(i);
    int z=0;
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        int x=((get(S)^z)%n)+1,k=(get(S)^z)%T[x].d;
        z=find_fa(x,k);
        s^=ll(i)*z;
    }
    printf("%lld",s);
    return 0;
}