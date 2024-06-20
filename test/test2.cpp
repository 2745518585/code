#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+50;

struct poi
{
    int x,y;

    friend poi operator+(poi a,poi b)
    {
        return (poi){a.x+b.x,a.y+b.y};
    }

    friend poi operator-(poi a,poi b)
    {
        return (poi){a.x-b.x,a.y-b.y};
    }

    int operator^(poi b)
    {
        return x*b.y-y*b.x;
    }

    int len()
    {
        return x*x+y*y;
    }

    friend bool operator<(poi a,poi b)
    {
        int w=a^b;
        return w==0?a.len()>b.len():w<0;
    }
    
    int operator*(poi b)
    {
        return x*b.x+y*b.y;
    }
}a[N];

struct query
{
    poi x;int c,id,p;
    
    friend bool operator<(query a,query b)
    {
        return a.x<b.x;
    }
}Q[N];

int n,q,ans[N];
vector<poi>p[N];
poi st[N<<3];

#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define LS ls,l,mid
#define RS rs,mid+1,r

struct convex
{
    vector<poi>p;
    int pos;

    void merge1(convex a,convex b)// mink
    {
        vector<poi>().swap(p);
        p.resize(a.p.size()+b.p.size());
        int pos=0,cc=0;
        for(auto x:a.p)
        {
            while(pos<b.p.size()&&b.p[pos]<x)p[cc++]=b.p[pos++];
            p[cc++]=x;
        }
        while(pos<b.p.size())p[cc++]=b.p[pos++];
    }
    
    void merge2(convex a,convex b)// convex hull
    {
        vector<poi>().swap(p);
        int cc=0,pos=0;
        for(auto x:a.p)
        {
            while(pos<b.p.size()&&(x.x>b.p[pos].x||(x.x==b.p[pos].x&&x.y>b.p[pos].y)))st[cc++]=b.p[pos++];
            st[cc++]=x;
        }
        while(pos<b.p.size())st[cc++]=b.p[pos++];
        if(cc==0)return;
        int top=0;
        for(int i=1;i<cc;i++)
        {
            while(top&&((st[i]-st[top-1])^(st[top]-st[top-1]))<=0)top--;
            st[++top]=st[i];
        }
        p.resize(top+1);
        for(int i=0;i<=top;i++)p[i]=st[i];
    }

    void diff()
    {
        for(int i=p.size()-1;i>0;i--)p[i]=p[i]-p[i-1];
    }
    
    void integral()
    {
        for(int i=1;i<p.size();i++)p[i]=p[i]+p[i-1];
    }

    int find(poi x)
    {
        if(p.empty())return 0;
        int w=x*p[pos];
        while(pos+1<p.size()&&w<=x*p[pos+1])w=x*p[++pos];
        return w;
    }
}f[N],g[N],tmp;

void build(int x,int l,int r)
{
    if(l==r)
    {
        sort(p[l].begin(),p[l].end(),[&](poi a,poi b){return a.x==b.x?a.y<b.y:a.x<b.x;});
        f[x].merge2((convex){p[l]},(convex){});
        g[x]=f[x];
        for(auto&t:g[x].p)t=t+a[l];
        f[x].diff();
        return;
    }
    build(LS);build(RS);
    f[x].merge1(f[ls],f[rs]);
    tmp=g[ls];tmp.diff();
    tmp.merge1(tmp,f[rs]);
    tmp.integral();
    g[x].merge2(tmp,g[rs]);
}

int c;poi t;

int solve(int x,int l,int r,int L,int R)
{
    if(L>R)return -1;
    if(L<=l&&R>=r)
    {
        if(g[x].find(t)<c)
        {
            c-=f[x].find(t);
            return -1;
        }
        if(l==r)return l;
        int w=solve(RS,L,R);
        return w==-1?solve(LS,L,R):w;
    }
    if(R>mid)
    {
        int w=solve(RS,L,R);
        if(w!=-1)return w;
    }
    return solve(LS,L,R);
}

void dfs(int x,int l,int r)
{
    f[x].integral();
    if(l==r)return;
    dfs(LS);dfs(RS);
}

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].y;
        if(i==n)break;
        int k;cin>>k;
        p[i].resize(k);
        while(k--)cin>>p[i][k].x>>p[i][k].y;
    }
    build(1,1,n);dfs(1,1,n);
    cin>>q;
    for(int i=1;i<=q;i++)cin>>Q[i].p>>Q[i].x.x>>Q[i].x.y>>Q[i].c,Q[i].id=i;
    sort(Q+1,Q+1+q);
    for(int i=1;i<=q;i++)
    {
        t=Q[i].x,c=Q[i].c;
        int pos=Q[i].p;
        if(a[pos]*t>=c)ans[Q[i].id]=pos;
        else ans[Q[i].id]=solve(1,1,n,1,Q[i].p-1);
    }
    for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}