#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=10001,M=1000001;
int n,m,p=1,T,s1,s2,t1,t2,t[N],t0[N],f[N];
ll b[N];
struct road
{
    int m,q;
    ll r;
}a[M];
int sum(int x,int k)
{
    return x*2+k+4;
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
    for(int i=1;i<=T;++i) f[i]=0;
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
            int z=dfs(a[i].m,min(r,a[i].r));
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
void print()
{
    for(int i=1;i<=n;++i)
    {
        int x=1;
        while(true)
        {
            for(int i=t[x];i!=0;i=a[i].q)
            {
                if(a[i^1].r>0&&a[i].m>=6||a[i].m==t2)
                {
                    --a[i^1].r;
                    x=a[i].m;
                    break;
                }
            }
            if(x==t2) break;
            printf("%d ",(x-4)/2);
            ++x;
        }
        printf("\n");
    }
}
int main()
{
    scanf("%d",&n);
    t1=2,t2=3,s1=4,s2=5;
    road(t1,1,n);
    road(1,t1,0);
    road(t2,t1,1e18);
    road(t1,t2,0);
    for(int k=1;;++k)
    {
        T=sum(k,1);
        for(int i=1;i<=k-1;++i)
        {
            if(sqrt(k+i)==int(sqrt(k+i)))
            {
                road(sum(i,1),sum(k,0),1);
                road(sum(k,0),sum(i,1),0);
            }
        }
        road(1,sum(k,0),1);
        road(sum(k,0),1,0);
        road(sum(k,1),t2,1);
        road(t2,sum(k,1),0);
        road(sum(k,0),s2,1);
        road(s2,sum(k,0),0);
        road(s1,sum(k,1),1);
        road(sum(k,1),s1,0);
        while(bfs())
        {
            for(int i=1;i<=T;++i) t0[i]=t[i];
            dfs(s1,1e18);
        }
        for(int i=t[s1];i!=0;i=a[i].q)
        {
            if(a[i].r!=0)
            {
                printf("%d\n",k-1);
                print();
                return 0;
            }
        }
    }
    return 0;
}