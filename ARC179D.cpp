#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,d1[N],d2[N],f1[N],f2[N],g1[N],g2[N];
vector<int> a[N];
void dfs1(int x,int fa)
{
    d1[x]=0;
    int u=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        d1[x]=max(d1[x],d1[i]+1);
        if(d1[i]>d1[u]) u=i;
        g1[x]=max(g1[x]+max(f1[i],d1[i]+1),f1[x]+g1[i]+1);
        f1[x]+=max(f1[i],d1[i]+1);
    }
}
void dfs2(int x,int fa)
{
    int p1=0,p2=0,q1=0,q2=0,s=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(d1[i]+1>p1) p2=p1,p1=d1[i]+1;
        else if(d1[i]+1>p2) p2=d1[i]+1;
        int z=g1[i]+1-max(f1[i],d1[i]+1);
        if(z>q1) q2=q1,q1=z;
        else if(z>q2) q2=z;
        s+=max(f1[i],d1[i]+1);
    }
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(d1[i]+1==p1) d2[i]=max(d2[x],p2)+1;
        else d2[i]=max(d2[x],p1)+1;
        f2[i]=max(f2[x],d2[x])+s-max(f1[i],d1[i]+1);
        if(g1[i]+1-max(f1[i],d1[i]+1)==q1) g2[i]=f2[i]+max(q2,g2[x]-max(f2[x],d2[x]))+1;
        else g2[i]=f2[i]+max(q1,g2[x]-max(f2[x],d2[x]))+1;
        dfs2(i,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s=max(s,max(f1[i]+g2[i],g1[i]+max(f2[i],d2[i])));
    }
    printf("%d",(n-1)*2-s);
    return 0;
}