#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define lb(x) (x&(-x))
using namespace std;
const int N=(1<<22),M=22,mod=1e18;

int md(int x)
{
    return x>=mod?x-mod:x;
}

struct node
{
    int w,s;

    node operator+(node b)
    {
        return w==b.w?(node){w,md(s+b.s)}:w<b.w?(node){w,s}:b;
    }
    
    node operator*(node b)
    {
        return (node){w+b.w,(int)(1ll*s*b.s%mod)};
    }
}f[N],g[N];

struct poi
{
    int c,w;

    friend bool operator<(poi a,poi b)
    {
        return a.c<b.c;
    }
}a[M];

int n,m,sum[N],w,mx[N],mb[N],A[N],top,cc[N];
int *B[1<<11];

int cmp1(int a,int b)
{
    return sum[a]>sum[b];
}

int cmp2(int a,int b)
{
    return sum[a]<sum[b];
}

void solve(int m,int d)
{
    for(int i=1;i<(1<<m);i++)
    {
        int t=i<<d;
        if(sum[t]<=w)
        {
            f[t]=(node){mx[t],1};
            continue;
        }
        f[t].w=2e9;
        int p=t^lb(t);
        for(int s=p;s;s=(s-1)&p)f[t]=f[t]+(f[s]*f[t^s]);
    }
}

void mul(node&f,node a,int b)
{
    a.w+=b;
    f=(f.w==a.w?(node){f.w,md(f.s+a.s)}:(f.w<a.w?f:a));
}

int main()
{
    // freopen("in","r",stdin);
    // freopen("out","w",stdout);
    cin>>n>>w;m=n/2;
    for(int i=0;i<n;i++)cin>>a[i].w>>a[i].c;
    sort(a,a+n);
    for(int i=0;i<n;i++)sum[1<<i]=a[i].w,mx[1<<i]=a[i].c,mb[1<<i]=(1<<i);
    for(int i=1;i<(1<<n);i++)if(lb(i)^i)sum[i]=sum[i^lb(i)]+sum[lb(i)],mx[i]=max(mx[i^lb(i)],mx[lb(i)]),mb[i]=mb[i-1];
    for(int i=0;i<(1<<n-m);i++)
    {
        for(int s=(i^mb[i]);s;s=(s-1)&(i^mb[i]))if(sum[(i^s)<<m]<=w)++cc[i];
        B[i]=new int[cc[i]+1];cc[i]=0;
        for(int s=(i^mb[i]);s;s=(s-1)&(i^mb[i]))if(sum[(i^s)<<m]<=w)B[i][cc[i]++]=(s<<m);
        B[i][cc[i]++]=0;sort(B[i],B[i]+cc[i],cmp2);
    }
    f[0]=(node){0,1};solve(m,0);solve(n-m,m);
    for(int i=1;i<(1<<m);i++)
    {
        top=0;
        for(int s=(i&(i-1));s;s=((s-1)&i))if(sum[s^i]<=w)A[top++]=s;A[top++]=0;
        sort(A,A+top,cmp1);
        for(int s=0;s<(1<<n-m);s++)
        {
            node now;now.w=2e9;
            for(int j=0;j<top;j++)g[(s<<m)|A[j]]=now=now+f[(s<<m)|A[j]];
        }
        for(int s=1;s<(1<<n-m);s++)
        {
            int pos=0,t=(s<<m)|i,rw=mx[s<<m];f[t].w=2e9;
            if(sum[t]<=w)
            {
                f[t]=(node){mx[t],1};
                continue;
            }
            for(int j=0;j<cc[s];j++)
            {
                int x=B[s][j];
                if(sum[(s<<m)^x]<=w)mul(f[t],f[i|x],rw);
                while(pos<top&&sum[t]-sum[A[pos]]-sum[x]<=w)pos++;
                if(pos)mul(f[t],g[A[pos-1]|x],rw);
            }
        }
    }
    cout<<f[(1<<n)-1].w<<' '<<f[(1<<n)-1].s<<'\n';
    cerr<<1.0*clock()/CLOCKS_PER_SEC;
}