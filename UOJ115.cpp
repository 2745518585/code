#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,v,b[N],c[N],d[N],d2[N],f[N];
bool h[N],h2[N],g[N];
vector<int> a[N];
void dfs0(int x)
{
    h[x]=true;
    for(auto i:a[x])
    {
        if(h[i]) continue;
        dfs0(i);
    }
}
void dfs(int x,int fa,int t)
{
    ++f[x];
    bool u=false;
    for(auto i:a[x])
    {
        if(i==fa||g[i]) continue;
        f[i]=f[x];
        if(!u) d[x]=i,dfs(i,x,t),u=true;
        else dfs(i,x,i);
    }
    if(!u)
    {
        d[v]=t;
        v=x;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        b[i]=x;
        a[x].push_back(i);
        a[i].push_back(x);
    }
    for(int i=1;i<=n;++i)
    {
        if(!h[i])
        {
            int x=i;
            while(!h2[x])
            {
                h2[x]=true;
                x=b[x];
            }
            int y=b[x],t=1;
            while(y!=x) g[y]=true,y=b[y],++t;
            g[x]=true;
            y=b[x];
            while(y!=x) f[y]=t-1,y=b[y];
            f[x]=t-1;
            dfs0(i);
        }
    }
    for(int i=1;i<=n;++i) h[i]=false;
    for(int i=1;i<=n;++i)
    {
        if(g[i]&&!h[i])
        {
            q=0;
            int x=b[i];
            while(x!=i) c[++q]=x,h[x]=true,x=b[x];
            c[++q]=i;
            h[i]=true;
            for(int i=1;i<=q/2;++i) swap(c[i],c[q-i+1]);
            v=0;
            for(int i=1;i<=q;++i)
            {
                dfs(c[i],0,c[i]);
            }
            d[v]=c[1];
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i) s+=f[i],d2[d[i]]=i;
    ll s2=0;
    for(int i=1;i<=n;++i)
    {
        if(g[d[i]]&&g[i]) s2+=f[i]-2;
        else if(a[i].size()!=1) s2+=f[i]-1;
    }
    printf("%lld\n",s-s2);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",d2[i]);
    }
    printf("\n");
    printf("%lld\n",s);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",d[i]);
    }
    printf("\n");
    return 0;
}