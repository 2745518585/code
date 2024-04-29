#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+50,mod=998244353;

int T,n,a[N],c,cm[N],mi[N];

#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)

int chk(int x,int y)
{
    return a[x]<a[y]?x:y;
}

void build(int x,int l,int r)
{
    if(l==r)return mi[x]=l,void();
    build(ls,l,mid);build(rs,mid+1,r);
    mi[x]=chk(mi[ls],mi[rs]);
}

void insert(int x,int l,int r,int d)
{
    if(l==r)return mi[x]=l,void();
    if(d<=mid)insert(ls,l,mid,d);
    else insert(rs,mid+1,r,d);
    mi[x]=chk(mi[ls],mi[rs]);
}

int find(int x,int l,int r,int L,int R)
{
    if(L<=l&&R>=r)return mi[x];
    if(L>mid)return find(rs,mid+1,r,L,R);
    if(R<=mid)return find(ls,l,mid,L,R);
    return chk(find(ls,l,mid,L,R),find(rs,mid+1,r,L,R));
}

int solve(int l,int r,int x,int y)
{
	// printf("%d %d %d %d\n",l,r,x,y);
    if(l>n||r<1)return 1;
    if(x+y>r-l+1)return cm[r-l+1];
    if(r-l+1<=c)return cm[x]*cm[y]%mod;
    int pos=find(1,1,n,l,r);
    if(pos>l+x-1&&pos<r-y+1)return solve(l,pos-1,x,(pos-l>=c)?c:0)*solve(pos+1,r,(r-pos>=c)?c:0,y)%mod;
    if(pos<l+x)
    {
        swap(a[pos],a[l]);insert(1,1,n,l);insert(1,1,n,pos);
        return solve(l+1,r,c+x-1,y)*x%mod;
    }
    swap(a[pos],a[r]);insert(1,1,n,r);insert(1,1,n,pos);
    return solve(l,r-1,x,y+c-1)*y%mod;
}

void sol()
{
    cin>>n>>c;
    cm[0]=1;
    for(int i=1;i<=n;i++)cin>>a[i],cm[i]=cm[i-1]*i%mod;
    build(1,1,n);
    cout<<solve(1,n,0,0)<<'\n';
}

main()
{
    // freopen("in.txt","r",stdin);
    cin>>T;
    while(T--)sol();
}