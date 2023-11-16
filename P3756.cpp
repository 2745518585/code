#include<cstdio>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int N=5000001;
int n,m,q,p=1,s1,s2,t[N],t0[N],f[N];
map<pair<int,int>,pair<int,int> > Map;
struct road
{
    int m,q;
    ll r;
}a[N];
void road(int x,int y,ll r)
{
    // printf("%d->%d:%lld\n",x,y,r);
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
int main()
{
    scanf("%*d%*d%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        Map[make_pair(x,y)]=make_pair(++q,w);
    }
    s1=q+1,s2=q+2;
    for(auto p=Map.begin();p!=Map.end();++p)
    {
        int x=(*p).first.first,y=(*p).first.second,z=(*p).second.first,w=(*p).second.second;
        if((x%4==1&&y%2==0)||(x%4==0&&y%2==1)) road(s1,z,w);
        else if((x%4==2&&y%2==0)||(x%4==3&&y%2==1)) road(z,s2,w);
        else if((x%4==1&&y%2==1)||(x%4==0&&y%2==0))
        {
            if(Map.count(make_pair(x,y-1))) road(Map[make_pair(x,y-1)].first,z,1e18);
            if(Map.count(make_pair(x,y+1))) road(Map[make_pair(x,y+1)].first,z,1e18);
            if(x%2==1)
            {
                if(Map.count(make_pair(x-1,y))) road(Map[make_pair(x-1,y)].first,z,1e18);
                if(Map.count(make_pair(x+1,y))) road(z,Map[make_pair(x+1,y)].first,min(w,Map[make_pair(x+1,y)].second));
            }
            else
            {
                if(Map.count(make_pair(x+1,y))) road(Map[make_pair(x+1,y)].first,z,1e18);
                if(Map.count(make_pair(x-1,y))) road(z,Map[make_pair(x-1,y)].first,min(w,Map[make_pair(x-1,y)].second));
            }
        }
        else if((x%4==2&&y%2==1)||(x%4==3&&y%2==0))
        {
            if(Map.count(make_pair(x,y-1))) road(z,Map[make_pair(x,y-1)].first,1e18);
            if(Map.count(make_pair(x,y+1))) road(z,Map[make_pair(x,y+1)].first,1e18);
            if(x%2==1)
            {
                if(Map.count(make_pair(x-1,y))) road(z,Map[make_pair(x-1,y)].first,1e18);
            }
            else
            {
                if(Map.count(make_pair(x+1,y))) road(z,Map[make_pair(x+1,y)].first,1e18);
            }
        }
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%lld",r);
    return 0;
}