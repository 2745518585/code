#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=6e5+50,inf=1e18;

struct ask
{
    int opt,v,l,r;
}Q[N];

int n,a[N],q,v[N],fir[N],m,tot,ch[N][2],vi[N],ro;
vector<int>tmp,in[N];

#define mid ((l+r)>>1)

struct line
{
    int k,b;

    int f(int x)
    {
        return k*x+b;
    }
}mi[N];

void insert(int&x,int l,int r,line d)
{
    if(!x)x=++tot;
    if(!vi[x]||(mi[x].f(l)>=d.f(l)&&mi[x].f(r)>=d.f(r))){mi[x]=d;vi[x]=1;return;}
    if(mi[x].f(l)<=d.f(l)&&mi[x].f(r)<=d.f(r))return;
    if(mi[x].f(mid)>=d.f(mid))swap(d,mi[x]);if(l==r)return;
    if(d.f(l)<=mi[x].f(l))insert(ch[x][0],l,mid,d);else insert(ch[x][1],mid+1,r,d);
}

int find(int x,int l,int r,int d)
{
    if(!vi[x])return inf;
    if(l==r)return mi[x].f(d);
    return min(mi[x].f(d),(d<=mid?find(ch[x][0],l,mid,d):find(ch[x][1],mid+1,r,d)));
}

void clear()
{
    for(int i=1;i<=tot;i++)ch[i][0]=ch[i][1]=vi[i]=0;
    tot=ro=0;
}

void solve(int l,int r,vector<int>tmp)
{
    if(tmp.empty())return;
    if(l==r)
    {
        for(auto x:tmp)if(x*fir[l]+a[x]>=v[l])in[l].push_back(x);
        return;
    }
    for(int i=l;i<=mid;i++)insert(ro,1,n,(line){-fir[i],v[i]});
    vector<int>L,R;
    for(auto x:tmp)
    {
        if(a[x]>=find(1,1,n,x))L.push_back(x);
        else R.push_back(x);
    }
    clear();solve(l,mid,L);solve(mid+1,r,R);
}

int sum[N],ad[N],la[N],mx[N],mxad[N],val[N],num[N],tad[N],cm[N],siz[N];

#define ls (x<<1)
#define rs (x<<1|1)
#define LS ls,l,mid
#define RS rs,mid+1,r

void up1(int x)
{
    sum[x]=sum[ls]+sum[rs];
    ad[x]=ad[ls]+ad[rs];
}

void up2(int x)
{
    if(siz[rs])mx[x]=mx[rs],mxad[x]=mxad[rs];else mx[x]=mx[ls],mxad[x]=mxad[ls];
    val[x]=val[ls]+val[rs];tad[x]=tad[ls]+tad[rs];siz[x]=siz[ls]+siz[rs];
}

void mk1(int x,int d)
{
    la[x]+=d;
    sum[x]+=d*ad[x];
}

void mk2(int x,int d)
{
    num[x]+=d;
    val[x]+=d*tad[x];
    mx[x]+=d*mxad[x];
}

void mk3(int x,int w)
{
    if(!siz[x])return;
    cm[x]=mx[x]=w;val[x]=w*siz[x];num[x]=0;
}

void down1(int x)
{
    if(!la[x])return;
    mk1(ls,la[x]);mk1(rs,la[x]);
    la[x]=0;
}

void down2(int x)
{
    if(cm[x]!=inf)mk3(ls,cm[x]),mk3(rs,cm[x]),cm[x]=inf;
    if(num[x])mk2(ls,num[x]),mk2(rs,num[x]),num[x]=0;
}

void build(int x,int l,int r)
{
    cm[x]=inf;
    if(l==r)
    {
        sum[x]=a[l];ad[x]=l;
        return;
    }
    build(LS);build(RS);up1(x);
}

void del(int x,int l,int r,int d)
{
    if(l==r)
    {
        sum[x]=la[x]=ad[x]=0;
        return;
    }
    down1(x);
    if(d<=mid)del(LS,d);else del(RS,d);
    up1(x);
}

void insert(int x,int l,int r,int d,int w)
{
    if(l==r)
    {
        mx[x]=val[x]=w;tad[x]=mxad[x]=l;siz[x]=1;
        return;
    }
    down2(x);
    if(d<=mid)insert(LS,d,w);else insert(RS,d,w);
    up2(x);
}

void solve(int x,int l,int r,int d)
{
    if(mx[x]<=d)return;
    if(l==r)return mk3(x,d);
    down2(x);
    if(mx[ls]>=d)mk3(rs,d),solve(LS,d);
    else solve(RS,d);
    up2(x);
}

int find(int x,int l,int r,int L,int R)
{
    if(L<=l&&R>=r)return sum[x]+val[x];
    down1(x);down2(x);
    int ans=0;
    if(L<=mid)ans+=find(LS,L,R);
    if(R>mid)ans+=find(RS,L,R);
    return ans;
}

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i],tmp.push_back(i);
    for(int i=1;i<=q;i++)
    {
        cin>>Q[i].opt;
        if(Q[i].opt==2)fir[m+1]++;
        if(Q[i].opt==1)
        {
            m++;fir[m+1]=fir[m];
            cin>>Q[i].v;v[m]=Q[i].v;
        }
        if(Q[i].opt==3)cin>>Q[i].l>>Q[i].r;
    }
    if(m)solve(1,m,tmp);
    build(1,1,n);m=0;
    for(int i=1;i<=q;i++)
    {
        if(Q[i].opt==1)
        {
            ++m;
            solve(1,1,n,v[m]);
            for(auto x:in[m])del(1,1,n,x),insert(1,1,n,x,v[m]);
        }
        if(Q[i].opt==2)mk1(1,1),mk2(1,1);
        if(Q[i].opt==3)cout<<find(1,1,n,Q[i].l,Q[i].r)<<'\n';
    }
}