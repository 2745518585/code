#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=3001,inf=1e9,M=1e5;
int n,q,rt,a[N],f[N];
bool h[N];
vector<int> b[N];
ll query1(vector<pair<int,int>> x,vector<pair<int,int>> y,bool u=true)
{
    static int z[N];
    for(int i=1;i<=n-1;++i) z[i]=M;
    for(auto i:x) z[i.first]=i.second;
    for(auto i:y) z[i.first]=i.second;
    printf("? 1 ");
    for(int i=1;i<=n-1;++i) printf("%d ",z[i]);
    printf("\n");
    fflush(stdout);
    ll w;
    scanf("%lld",&w);
    return u?w%M:w;
}
int query2(int a,int b)
{
    printf("? 2 %d %d\n",a,b);
    fflush(stdout);
    int w;
    scanf("%d",&w);
    return w;
}
void solve0()
{
    bool u=true;
    a[b[0][0]]=n;
    for(int i=1;i<b[0].size();++i)
    {
        if(query1({{1,inf}},{{b[0][0],inf},{b[0][i],inf}},false)>=(ll)inf*3)
        {
            u=false;
            a[b[0][i]]=1;
        }
        else a[b[0][i]]=n;
    }
    if(u) rt=1;
}
void solve2(int t)
{
    vector<pair<int,int>> p;
    p.push_back(make_pair(rt,inf));
    for(auto i:b[t-1])
    {
        p.push_back(make_pair(i,i));
    }
    for(auto i:b[t])
    {
        a[i]=query1(p,{{i,inf}});
    }
}
void solve1(int t)
{
    vector<pair<int,int>> p;
    for(auto i:b[t-1])
    {
        p.push_back(make_pair(i,i));
    }
    for(int i=1;i<=n*2;++i) h[i]=false;
    for(int i=1;i<b[t].size();++i)
    {
        f[i]=query1(p,{{b[t][0],inf},{b[t][i],inf}});
        h[f[i]]=true;
    }
    int v=1;
    for(int i=1;i<=n*2;++i) v+=h[i];
    if(v>=3)
    {
        int x=1;
        while(f[x]==0) ++x;
        int y=x+1;
        while(f[x]==f[y]||f[y]==0) ++y;
        int z=(f[x]+f[y]-query1(p,{{b[t][x],inf},{b[t][y],inf}}))/2;
        for(int i=0;i<b[t].size();++i)
        {
            if(f[i]==0) a[b[t][i]]=z;
            else a[b[t][i]]=f[i]-z;
        }
        return;
    }
    else if(v==1)
    {
        if(b[t-1].size()<=2)
        {
            for(auto i:b[t]) a[i]=b[t-1][0];
            if(b[t-1].size()>1) rt=b[t-1][1];
        }
        else
        {
            int z[3],x;
            for(int i=0;i<=2;++i)
            {
                z[i]=query1(p,{{b[t][0],inf},{b[t-1][i],inf}});
            }
            if(z[0]==z[1]||z[0]==z[2]) x=z[0];
            else x=z[1];
            for(auto i:b[t]) a[i]=x;
            for(auto i:b[t-1])
            {
                if(i!=x)
                {
                    rt=i;
                    break;
                }
            }
        }
        return;
    }
    if(b[t-1].size()>=3)
    {
        int x=1;
        while(f[x]==0) ++x;
        ll z=query1(p,{{b[t][0],inf},{b[t][x],inf},{b[t-1][0],inf}},false);
        if(z>=(ll)inf*3)
        {
            z%=M;
            for(int i=1;i<b[t-1].size();++i)
            {
                if(b[t-1][i]!=z)
                {
                    rt=b[t-1][i];
                    break;
                }
            }
        }
        else rt=b[t-1][0];
        int y=query1(p,{{rt,inf},{b[t][0],inf}});
        for(int i=0;i<b[t].size();++i)
        {
            if(f[i]==0) a[b[t][i]]=y;
            else a[b[t][i]]=f[i]-y;
        }
    }
    else
    {
        for(int i=0;i<b[t].size();++i)
        {
            if(f[i]==0) a[b[t][i]]=b[t-1][0];
            else a[b[t][i]]=b[t-1][1];
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n-1;++i)
    {
        b[query2(1,i)].push_back(i);
    }
    solve0();
    for(int i=1;i<=n;++i)
    {
        if(b[i].size()==0) break;
        if(rt==0) solve1(i);
        else solve2(i);
    }
    printf("!\n");
    printf("%d %d\n",1,n);
    for(int i=2;i<=n-1;++i)
    {
        printf("%d %d\n",a[i],i);
    }
    fflush(stdout);
    return 0;
}