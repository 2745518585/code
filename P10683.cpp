#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,q,op,tot,a1[N],a2[N],r[N],f[N],g[N],v[N],f2[N],g2[N],v2[N],fa[N];
bool h[N];
vector<pair<int,int>> a[N],b[N];
struct tree
{
    int b,c;
}T[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs1(int x,int fa)
{
    T[x].b=T[x].c=++tot;
    for(auto i:a[x])
    {
        if(T[i.first].b==0)
        {
            dfs1(i.first,i.second/2);
            T[x].c=min(T[x].c,T[i.first].c);
            if(T[i.first].c>T[x].b) h[i.second/2]=true;
        }
        if(i.second/2!=fa)
        {
            T[x].c=min(T[x].c,T[i.first].b);
        }
    }
}
void dfs2(int x)
{
    r[x]=q;
    if(x<=n) ++f[q];
    else --f[q];
    ++f2[q];
    for(auto i:a[x])
    {
        if(r[i.first]||h[i.second/2]) continue;
        dfs2(i.first);
    }
}
pair<int,int> dfs(int x,int fa,int w,int w2)
{
    int s=f[x],s2=f[x];
    for(auto i:b[x])
    {
        if(i.first==fa) continue;
        auto z=dfs(i.first,x,w,w2);
        g[i.second]=z.first;
        g[i.second^1]=w-z.first;
        g2[i.second]=z.second;
        g2[i.second^1]=w2-z.second;
        s+=z.first,s2+=z.second;
    }
    return make_pair(s,s2);
}
int main()
{
    int TOT;
    scanf("%d%d",&TOT,&op);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n*2+1;++i) a[i].clear(),r[i]=f[i]=g[i]=f2[i]=g2[i]=h[i]=T[i].b=T[i].c=0;
        tot=q=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a1[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a2[i]);
            a2[i]+=n;
        }
        for(int i=1;i<=n;++i)
        {
            a[a1[i]].push_back(make_pair(a2[i],i*2));
            a[a2[i]].push_back(make_pair(a1[i],i*2+1));
        }
        for(int i=1;i<=n*2;++i)
        {
            if(T[i].b==0) dfs1(i,0);
        }
        for(int i=1;i<=n*2;++i)
        {
            if(r[i]==0)
            {
                ++q;
                dfs2(i);
            }
        }
        for(int i=1;i<=q;++i) b[i].clear(),fa[i]=i,v[i]=v2[i]=0;
        for(int i=1;i<=n;++i)
        {
            if(r[a1[i]]!=r[a2[i]])
            {
                b[r[a1[i]]].push_back(make_pair(r[a2[i]],i*2));
                b[r[a2[i]]].push_back(make_pair(r[a1[i]],i*2+1));
                fa[find(r[a1[i]])]=find(r[a2[i]]);
            }
        }
        for(int i=1;i<=q;++i)
        {
            v[find(i)]+=f[i];
            v2[find(i)]+=f2[i];
        }
        for(int i=1;i<=q;++i)
        {
            if(find(i)!=i) continue;
            dfs(i,0,v[i],v2[i]);
        }
        if(op==0)
        {
            int s=0;
            for(int i=1;i<=q;++i)
            {
                if(find(i)==i) s+=abs(v[i]);
            }
            printf("%d\n",n-s/2);
        }
        else if(op==1)
        {
            int s=0,w=0;
            for(int i=1;i<=q;++i)
            {
                if(find(i)==i) w+=abs(v[i]);
            }
            s=w;
            int u=0;
            for(int i=1;i<=q;++i)
            {
                if(find(i)!=i) continue;
                if(abs(v[i])!=v2[i]) ++u;
            }
            for(int i=1;i<=n;++i)
            {
                if(!h[i]) continue;
                if(g2[i*2]>1||g2[i*2+1]>1) s=max(s,w-abs(g[i*2]+g[i*2+1])+abs(g[i*2])+abs(g[i*2+1]));
                else
                {
                    if(u>1) s=max(s,w+2);
                }
            }
            printf("%d\n",n-s/2);
        }
        else if(op==2)
        {
            int s=0,w=0;
            for(int i=1;i<=q;++i)
            {
                if(find(i)==i) w+=abs(v[i]);
            }
            s=w;
            int mx1=0,mx2=0,mn1=0,mn2=0;
            for(int i=1;i<=q;++i)
            {
                if(find(i)!=i) continue;
                if(v[i]>mx1) mx2=mx1,mx1=v[i];
                else if(v[i]>mx2) mx2=v[i];
                if(v[i]<mn1) mn2=mn1,mn1=v[i];
                else if(v[i]<mn2) mn2=v[i];
            }
            for(int i=1;i<=n;++i)
            {
                if(!h[i]) continue;
                int mx=(g[i*2]+g[i*2+1]==mx1?mx2:mx1),mn=(g[i*2]+g[i*2+1]==mn1?mn2:mn1);
                if(g[i*2]>=0) s=min(s,w-abs(g[i*2]+g[i*2+1])-abs(mn)+abs(g[i*2+1])+abs(g[i*2]+mn));
                if(g[i*2]<=0) s=min(s,w-abs(g[i*2]+g[i*2+1])-abs(mx)+abs(g[i*2+1])+abs(g[i*2]+mx));
                if(g[i*2+1]>=0) s=min(s,w-abs(g[i*2]+g[i*2+1])-abs(mn)+abs(g[i*2])+abs(g[i*2+1]+mn));
                if(g[i*2+1]<=0) s=min(s,w-abs(g[i*2]+g[i*2+1])-abs(mx)+abs(g[i*2])+abs(g[i*2+1]+mx));
            }
            for(int i=1;i<=q;++i)
            {
                if(f2[i]==1) continue;
                int x=find(i);
                int mx=(v[x]==mx1?mx2:mx1),mn=(v[x]==mn1?mn2:mn1);
                if(v[x]>=0) s=min(s,w-abs(v[x])-abs(mn)+abs(v[x]+mn));
                if(v[x]<=0) s=min(s,w-abs(v[x])-abs(mx)+abs(v[x]+mx));
            }
            printf("%d\n",n-s/2);
        }
    }
    return 0;
}