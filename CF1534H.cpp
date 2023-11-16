#include<bits/stdc++.h>
using namespace std;
int set_limit(int x)
{
    printf("%d\n",x);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
int query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
void answer(int x1,int x2)
{
    printf("! %d %d\n",x1,x2);
    fflush(stdout);
}
namespace Solve
{
    const int N=1000001;
    int s,f[N],g[N],g1[N],g2[N];
    vector<int> a[N];
    bool cmp(int a,int b)
    {
        return f[a]>f[b];
    }
    void dfs1(int x,int fa)
    {
        for(int i=0;i<a[x].size();++i)
        {
            if(a[x][i]==fa) continue;
            dfs1(a[x][i],x);
        }
        sort(a[x].begin(),a[x].end(),cmp);
        int u=0;
        for(int i=0;i<a[x].size();++i)
        {
            if(a[x][i]==fa) continue;
            ++u;
            f[x]=max(f[x],f[a[x][i]]+(u-1));
        }
        f[x]=max(f[x],u);
    }
    void dfs2(int x,int fa)
    {
        sort(a[x].begin(),a[x].end(),cmp);
        for(int i=1;i<a[x].size();++i) s=max(s,f[a[x][0]]+f[a[x][i]]+(i-1));
        if(a[x].size()>=1) s=max(s,(int)max(f[a[x][0]]+(a[x].size()-1),a[x].size()));
        for(int i=0;i<a[x].size();++i)
        {
            g1[i]=f[a[x][i]]+i;
            if(i>0) g1[i]=max(g1[i],g1[i-1]);
        }
        for(int i=a[x].size()-1;i>=0;--i)
        {
            g2[i]=f[a[x][i]]+i;
            if(i<a[x].size()-1) g2[i]=max(g2[i],g2[i+1]);
        }
        for(int i=0;i<a[x].size();++i)
        {
            g[a[x][i]]=0;
            if(i>0) g[a[x][i]]=max(g[a[x][i]],g1[i-1]);
            if(i<a[x].size()-1) g[a[x][i]]=max(g[a[x][i]],g2[i+1]-1);
        }
        for(int i=0;i<a[x].size();++i)
        {
            if(a[x][i]==fa) continue;
            f[x]=max(g[a[x][i]],int(a[x].size()-1));
            dfs2(a[x][i],x);
        }
    }
    int dfs3(int x,int fa)
    {
        if(a[x].size()==1) return query(x);
        for(int i=0;i<a[x].size();++i)
        {
            if(a[x][i]==fa) continue;
            int z=dfs3(a[x][i],x);
            if(z!=x) return z;
        }
        return x;
    }
    void solve(int n,const vector<pair<int,int> > &a2)
    {
        for(int i=0;i<=n-2;++i)
        {
            a[a2[i].first].push_back(a2[i].second);
            a[a2[i].second].push_back(a2[i].first);
        }
        dfs1(1,0);
        dfs2(1,0);
        int x=set_limit(s);
        dfs1(x,0);
        int x1=x,x2=x;
        for(int i=0;i<a[x].size();++i)
        {
            int z=dfs3(a[x][i],x);
            if(z!=x)
            {
                if(x1==x) x1=z;
                else x2=z;
            }
            if(x2!=x) break;
        }
        answer(min(x1,x2),max(x1,x2));
    }
}
void solve(int n,const vector<pair<int,int> >&a2) {Solve::solve(n,a2);}
int main()
{
    int n;
    scanf("%d",&n);
    vector<pair<int,int> >a;
    for(int i=0;i<=n-2;++i)
    {
        a.push_back(make_pair(0,0));
        scanf("%d%d",&a[i].first,&a[i].second);
    }
    solve(n,a);
    return 0;
}