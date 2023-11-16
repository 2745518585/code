#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=2001;
const int dx[8]={-1,0,1,0,-1,0,1,0},dy[8]={0,1,0,-1,0,1,0,-1};
int n,m,q,p=1,s1,s2,t[N],t0[N];
ll v,f[N];
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[N];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
    a[p].r=0;
    a[p].w=-w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=1e18;
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(h[a[i].m]==false&&a[i].r>0&&f[a[i].m]==f[x]+a[i].w)
        {
            h[a[i].m]=true;
            ll z=dfs(a[i].m,min(r,a[i].r));
            h[a[i].m]=false;
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
                v+=z*a[i].w;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
int sum(int x,int y)
{
    return (x-1)*n+y;
}
int check(int x,int y,int d)
{
    if(x+dx[d]>=1&&x+dx[d]<=m&&y+dy[d]>=1&&y+dy[d]<=n)
    {
        if(dx[d]!=0) return m*n*3+sum(x+max(dx[d],0),y+max(dy[d],0));
        else return m*n*4+sum(x+max(dx[d],0),y+max(dy[d],0));
    }
    return 0;
}
int main()
{
    scanf("%d%d",&m,&n);
    s1=m*n*5+1,s2=m*n*5+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            int u0=x%2,u1=x/2%2,u2=x/4%2,u3=x/8%2;
            q+=u0+u1+u2+u3;
            if((i+j)%2==0)
            {
                if(u0+u1+u2+u3==1)
                {
                    road(s1,sum(i,j),1,0);
                    int z=0;
                    if(u0) z=0;
                    if(u1) z=1;
                    if(u2) z=2;
                    if(u3) z=3;
                    if(check(i,j,z)!=0) road(sum(i,j),check(i,j,z),1,0);
                    if(check(i,j,z+1)!=0) road(sum(i,j),check(i,j,z+1),1,1);
                    if(check(i,j,z+2)!=0) road(sum(i,j),check(i,j,z+2),1,2);
                    if(check(i,j,z+3)!=0) road(sum(i,j),check(i,j,z+3),1,1);
                }
                else if(u0+u2==1&&u1+u3==1)
                {
                    road(s1,sum(i,j),2,0);
                    int z=0;
                    if(u0&&u1) z=0;
                    if(u1&&u2) z=1;
                    if(u2&&u3) z=2;
                    if(u3&&u0) z=3;
                    road(sum(i,j),m*n+sum(i,j),1,0);
                    road(sum(i,j),m*n*2+sum(i,j),1,0);
                    if(check(i,j,z)!=0) road(m*n+sum(i,j),check(i,j,z),1,0);
                    if(check(i,j,z+1)!=0) road(m*n*2+sum(i,j),check(i,j,z+1),1,0);
                    if(check(i,j,z+2)!=0) road(m*n+sum(i,j),check(i,j,z+2),1,1);
                    if(check(i,j,z+3)!=0) road(m*n*2+sum(i,j),check(i,j,z+3),1,1);
                }
                else if((u0+u2==2&&u1+u3==0)||(u0+u2==0&&u1+u3==2))
                {
                    road(s1,sum(i,j),2,0);
                    int z=0;
                    if(u0&&u2) z=0;
                    if(u1&&u3) z=1;
                    if(check(i,j,z)!=0) road(sum(i,j),check(i,j,z),1,0);
                    if(check(i,j,z+2)!=0) road(sum(i,j),check(i,j,z+2),1,0);
                }
                else if(u0+u1+u2+u3==3)
                {
                    road(s1,sum(i,j),2,0);
                    road(s1,sum(i,j),1,1);
                    int z=0;
                    if(u0&&u1&&u2) z=0;
                    if(u1&&u2&&u3) z=1;
                    if(u2&&u3&&u0) z=2;
                    if(u3&&u0&&u1) z=3;
                    if(check(i,j,z)!=0) road(sum(i,j),check(i,j,z),1,0);
                    if(check(i,j,z+1)!=0) road(sum(i,j),check(i,j,z+1),1,-1);
                    if(check(i,j,z+2)!=0) road(sum(i,j),check(i,j,z+2),1,0);
                    if(check(i,j,z+3)!=0) road(sum(i,j),check(i,j,z+3),1,1);
                }
                else if(u0+u1+u2+u3==4)
                {
                    road(s1,sum(i,j),4,0);
                    if(check(i,j,0)!=0) road(sum(i,j),check(i,j,0),1,0);
                    if(check(i,j,1)!=0) road(sum(i,j),check(i,j,1),1,0);
                    if(check(i,j,2)!=0) road(sum(i,j),check(i,j,2),1,0);
                    if(check(i,j,3)!=0) road(sum(i,j),check(i,j,3),1,0);
                }
            }
            else
            {
                if(u0+u1+u2+u3==1)
                {
                    road(sum(i,j),s2,1,0);
                    int z=0;
                    if(u0) z=0;
                    if(u1) z=1;
                    if(u2) z=2;
                    if(u3) z=3;
                    if(check(i,j,z)!=0) road(check(i,j,z),sum(i,j),1,0);
                    if(check(i,j,z+1)!=0) road(check(i,j,z+1),sum(i,j),1,1);
                    if(check(i,j,z+2)!=0) road(check(i,j,z+2),sum(i,j),1,2);
                    if(check(i,j,z+3)!=0) road(check(i,j,z+3),sum(i,j),1,1);
                }
                else if(u0+u2==1&&u1+u3==1)
                {
                    road(sum(i,j),s2,2,0);
                    int z=0;
                    if(u0&&u1) z=0;
                    if(u1&&u2) z=1;
                    if(u2&&u3) z=2;
                    if(u3&&u0) z=3;
                    road(m*n+sum(i,j),sum(i,j),1,0);
                    road(m*n*2+sum(i,j),sum(i,j),1,0);
                    if(check(i,j,z)!=0) road(check(i,j,z),m*n+sum(i,j),1,0);
                    if(check(i,j,z+1)!=0) road(check(i,j,z+1),m*n*2+sum(i,j),1,0);
                    if(check(i,j,z+2)!=0) road(check(i,j,z+2),m*n+sum(i,j),1,1);
                    if(check(i,j,z+3)!=0) road(check(i,j,z+3),m*n*2+sum(i,j),1,1);
                }
                else if((u0+u2==2&&u1+u3==0)||(u0+u2==0&&u1+u3==2))
                {
                    road(sum(i,j),s2,2,0);
                    int z=0;
                    if(u0&&u2) z=0;
                    if(u1&&u3) z=1;
                    if(check(i,j,z)!=0) road(check(i,j,z),sum(i,j),1,0);
                    if(check(i,j,z+2)!=0) road(check(i,j,z+2),sum(i,j),1,0);
                }
                else if(u0+u1+u2+u3==3)
                {
                    road(sum(i,j),s2,2,0);
                    road(sum(i,j),s2,1,1);
                    int z=0;
                    if(u0&&u1&&u2) z=0;
                    if(u1&&u2&&u3) z=1;
                    if(u2&&u3&&u0) z=2;
                    if(u3&&u0&&u1) z=3;
                    if(check(i,j,z)!=0) road(check(i,j,z),sum(i,j),1,0);
                    if(check(i,j,z+1)!=0) road(check(i,j,z+1),sum(i,j),1,-1);
                    if(check(i,j,z+2)!=0) road(check(i,j,z+2),sum(i,j),1,0);
                    if(check(i,j,z+3)!=0) road(check(i,j,z+3),sum(i,j),1,1);
                }
                else if(u0+u1+u2+u3==4)
                {
                    road(sum(i,j),s2,4,0);
                    if(check(i,j,0)!=0) road(check(i,j,0),sum(i,j),1,0);
                    if(check(i,j,1)!=0) road(check(i,j,1),sum(i,j),1,0);
                    if(check(i,j,2)!=0) road(check(i,j,2),sum(i,j),1,0);
                    if(check(i,j,3)!=0) road(check(i,j,3),sum(i,j),1,0);
                }
            }
        }
    }
    if(q%2!=0)
    {
        printf("-1");
        return 0;
    }
    q/=2;
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        r+=dfs(s1,1e18);
    }
    if(r!=q) printf("-1");
    else printf("%lld",v);
    return 0;
}