#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001,M=1000001;
int n,m,p=1,p2=1,s1,s2,t[N],t0[N],f[N],l[N];
ll q;
bool h[N];
struct road
{
    int m,q;
    ll r;
}a[M];
struct road2
{
    int x,y;
    ll r;
    road2(){}
    road2(int x0,int y0,ll r0){x=x0,y=y0,r=r0;}
}a2[M];
int sum(int x,int y)
{
    return (x-1)*n+y;
}
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
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
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==0&&a[i].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s2]!=0;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            ll z=dfs(a[i].m,min(r,a[i].r));
            if(z!=0)
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
void tpsort()
{
    queue<int> Q;
    for(int i=1;i<=s2;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        h[k]=true;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            --l[a[i].m];
            if(l[a[i].m]==0) Q.push(a[i].m);
        }
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    s1=m*n+1,s2=m*n+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            ll r;
            scanf("%lld",&r);
            if(r>0)
            {
                a2[++p2]=road2(s1,sum(i,j),r);
            }
            else if(r<0)
            {
                a2[++p2]=road2(sum(i,j),s2,-r);
            }
            int q;
            scanf("%d",&q);
            for(int k=1;k<=q;++k)
            {
                int x,y;
                scanf("%d%d",&x,&y);
                ++x,++y;
                ++l[sum(x,y)];
                a2[++p2]=road2(sum(x,y),sum(i,j),1e18);
                road(sum(i,j),sum(x,y),0);
            }
            if(j>1)
            {
                ++l[sum(i,j-1)];
                a2[++p2]=road2(sum(i,j-1),sum(i,j),1e18);
                road(sum(i,j),sum(i,j-1),0);
            }
        }
    }
    tpsort();
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=p2;++i)
    {
        if(h[a2[i].x]==true&&h[a2[i].y]==true)
        {
            road(a2[i].x,a2[i].y,a2[i].r);
            road(a2[i].y,a2[i].x,0);
        }
    }
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        q+=a[i].r;
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",q-r);
    return 0;
}