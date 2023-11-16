#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int N=10001,M=100001;
int n,m,k,p=1,s1,s2,t[N],t0[N],b[N][2],c[101][101];
ll v,f[N];
bool h[N];
map<string,int> Map;
struct road
{
    int m,q;
    ll r,w;
}a[M];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool check(int x,int y,int z)
{
    if(b[x][0]==b[y][0]) return b[z][0]==b[x][0]&&b[z][1]>=min(b[x][1],b[y][1])&&b[z][1]<=max(b[x][1],b[y][1]);
    if(b[x][0]>b[y][0]) swap(x,y);
    return b[z][0]>=b[x][0]&&b[z][0]<=b[y][0]&&(b[z][1]-b[x][1])*(b[y][0]-b[z][0])==(b[y][1]-b[z][1])*(b[z][0]-b[x][0]);
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=-1e18;
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
            if(a[i].r>0&&f[k]+a[i].w>f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=-1e18;
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
int main()
{
    scanf("%d%d",&k,&n);
    s1=n*2+1,s2=n*2+2;
    Map["End"]=0;
    for(int i=1;i<=n*2;++i)
    {
        string c;
        scanf("%d%d",&b[i][0],&b[i][1]);
        cin>>c;
        for(int i=0;i<c.size();++i) if(c[i]<='Z') c[i]+='a'-'A';
        Map[c]=i;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=n+1;j<=n*2;++j)
        {
            c[i][j]=1;
        }
    }
    while(true)
    {
        int x,y,k;
        string c1,c2;
        cin>>c1;
        for(int i=0;i<c1.size();++i) if(c1[i]<='Z') c1[i]+='a'-'A';
        x=Map[c1];
        if(x==0) break;
        cin>>c2;
        for(int i=0;i<c2.size();++i) if(c2[i]<='Z') c2[i]+='a'-'A';
        y=Map[c2];
        scanf("%d",&k);
        if(x>y) swap(x,y);
        c[x][y]=k;
    }
    for(int i=1;i<=n;++i)
    {
        road(s1,i,1,0);
        road(i,s1,0,0);
        road(n+i,s2,1,0);
        road(s2,n+i,0,0);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=n+1;j<=n*2;++j)
        {
            if((b[i][0]-b[j][0])*(b[i][0]-b[j][0])+(b[i][1]-b[j][1])*(b[i][1]-b[j][1])>k*k) continue;
            bool u=true;
            for(int k=1;k<=n*2;++k)
            {
                if(k==i||k==j) continue;
                if(check(i,j,k))
                {
                    u=false;
                    break;
                }
            }
            if(u==false) continue;
            road(i,j,1,c[i][j]);
            road(j,i,0,-c[i][j]);
        }
    }
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) 
        {
            t0[i]=t[i];
            h[i]=false;
        }
        dfs(s1,1e18);
    }
    printf("%lld",v);
    return 0;
}