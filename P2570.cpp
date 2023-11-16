#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long double ld;
const int N=1000001;
int p=1,s1,s2,t[N],t0[N],f[N];
struct road
{
    int m,q;
    ld r;
}a[N];
void road(int x,int y,ld r)
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
ld dfs(int x,ld r)
{
    if(x==s2) return r;
    ld s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[a[i].m]==f[x]+1&&a[i].r!=0)
        {
            ld z=dfs(a[i].m,min(r,a[i].r));
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
int m,n,q,d[N];
ld c[N];
struct str
{
    int x,y,w;
}b[N];
int sum(int x,int y)
{
    return (x-1)*(q-1)+y;
}
bool check(ld x)
{
    q=0;
    for(int i=1;i<=n;++i)
    {
        c[++q]=b[i].x;
        c[++q]=b[i].y+x;
    }
    sort(c+1,c+q+1);
    q=unique(c+1,c+q+1)-c-1;
    s1=n+m*(q-1)+1,s2=n+m*(q-1)+2;
    p=1;
    for(int i=1;i<=s2;++i) t[i]=0;
    for(int i=1;i<=n;++i)
    {
        road(s1,i,b[i].w);
        road(i,s1,0);
        for(int j=1;j<=m;++j)
        {
            for(int k=1;k<=q-1;++k)
            {
                if(c[k]>=b[i].x&&c[k+1]<=b[i].y+x)
                {
                    road(i,n+sum(j,k),(c[k+1]-c[k])*(d[j]-d[j-1]));
                    road(n+sum(j,k),i,0);
                }
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=q-1;++j)
        {
            road(n+sum(i,j),s2,(c[j+1]-c[j])*(d[i]-d[i-1])*(m-i+1));
            road(s2,sum(i,j),0);
        }
    }
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        dfs(s1,1e18);
    }
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r!=0) return false;
    }
    return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&b[i].w,&b[i].x,&b[i].y);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&d[i]);
        }
        sort(d+1,d+m+1);
        ld l=0,r=1e9;
        while(r-l>1e-12)
        {
            ld z=(l+r)/2;
            if(check(z)) r=z;
            else l=z;
        }
        printf("%.12Lf\n",r);
    }
    return 0;
}