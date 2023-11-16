#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1001,M=100001;
int n,m,k,p=1,t[N],a2[N][N],f[N],s;
bool h[N];
struct road
{
    int m,q,w;
}a[M<<1];
struct num
{
    int s,q,a[N];
    num(){}
    num(int s,int q):s(s),q(q){a[1]=1;}
    friend bool operator <(num a,num b)
    {
        if(a.s!=b.s) return a.s>b.s;
        for(int i=1;i<=min(a.q,b.q);++i)
        {
            if(a.a[i]!=b.a[i]) return a.a[i]>b.a[i];
        }
        return a.q>b.q;
    }
    num add(num a,int x,int s)
    {
        a.s+=s;
        a.a[++a.q]=x;
        return a;
    }
};
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs(int x,int w,int q)
{
    if(w>q) return;
    if(x==n)
    {
        ++s;
        return;
    }
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]) continue;
        dfs(a[i].m,w+a[i].w,q);
        if(s>=k) return;
    }
    h[x]=false;
}
void dfs2(int x,num w,int q)
{
    if(w.s+f[x]>q) return;
    if(x==n)
    {
        if(w.s!=q) return;
        ++s;
        if(s==k)
        {
            printf("%d\n",w.q);
            for(int i=1;i<=w.q;++i)
            {
                printf("%d ",w.a[i]);
            }
            exit(0);
        }
        return;
    }
    h[x]=true;
    for(int i=1;i<=n;++i)
    {
        if(h[i]||!a2[x][i]) continue;
        dfs2(i,w.add(w,i,a2[x][i]),q);
    }
    h[x]=false;
}
void SPFA()
{
    for(int i=1;i<=n;++i) f[i]=1e9,h[i]=false;
    f[n]=0;
    h[n]=true;
    queue<int> Q;
    Q.push(n);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=1;i<=n;++i)
        {
            if(f[k]+a2[i][k]<f[i])
            {
                f[i]=f[k]+a2[i][k];
                h[i]=true;
                Q.push(i);
            }
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
        a2[x][y]=w;
    }
    int l=1,r=N*M;
    while(l<r)
    {
        int z=l+r>>1;
        for(int i=1;i<=n;++i) h[i]=false;
        s=0;
        dfs(1,0,z);
        if(s>=k) r=z;
        else l=z+1;
    }
    if(r==N*M)
    {
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;++i) h[i]=false;
    s=0;
    dfs(1,0,l-1);
    SPFA();
    for(int i=1;i<=n;++i) h[i]=false;
    dfs2(1,num(0,1),l);
    return 0;
}