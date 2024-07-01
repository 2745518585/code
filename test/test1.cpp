#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
#define vp vector<pii>
const int N=100005,M=1<<18,inf=30;
int n,q,op,l,r,i,a[N],R;
struct node{
    int ans;vp a;
}f[M],tmp;
void ins(vp &a,pii x){
    if(a.empty()) a.push_back(x);
    else if(a.back().fi==x.fi) a.back().se+=x.se;
    else if(a.size()<2||!(a.back().fi<a.end()[-2].fi&&a.back().fi<x.fi)) a.push_back(x);
    else{
        pii u=a.back();a.pop_back();
        int c=min(a.back().fi,x.fi)-u.fi;
        R=max(R,u.fi+__lg(u.se));
        if(((u.se>>c)<<c)==u.se) ins(a,{u.fi+c,u.se>>c});
        else{
            if(u.se>>c) ins(a,{u.fi+c,u.se>>c});
            ins(a,{inf,1});
            if(u.se>>c) ins(a,{u.fi+c,u.se>>c});
        }
        ins(a,x);
    }
}
node operator +(const node &a,const node &b){
    node c;c.ans=max(a.ans,b.ans);R=-1<<30;
    c.a=a.a;for(auto j:b.a) ins(c.a,j);c.ans=max(c.ans,R);
    return c;
}
void upd(int k){f[k]=f[k<<1]+f[k<<1|1];}
void bd(int k,int l,int r){
    if(l==r) return f[k]=node{0,{{a[l],1}}},void();
    int mid=l+r>>1;
    bd(k<<1,l,mid),bd(k<<1|1,mid+1,r);
    upd(k);
}
void ad(int k,int l,int r,int pos){
    if(l==r) return f[k]=node{0,{{a[l],1}}},void();
    int mid=l+r>>1;
    pos<=mid?ad(k<<1,l,mid,pos):ad(k<<1|1,mid+1,r,pos);
    upd(k);
}
node fd(int k,int l,int r,int s,int e){
    if(l>=s&&r<=e) return f[k];
    int mid=l+r>>1;
    return s<=mid&&e>mid?fd(k<<1,l,mid,s,e)+fd(k<<1|1,mid+1,r,s,e):(s<=mid?fd(k<<1,l,mid,s,e):fd(k<<1|1,mid+1,r,s,e));
}
vp c;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    bd(1,1,n);
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d",&op,&l,&r);
        if(op==2) a[l]=r,ad(1,1,n,l);
        else{
            tmp=fd(1,1,n,l,r);R=tmp.ans;
            c={{inf,1}};
            for(auto j:tmp.a) ins(c,j);
            ins(c,{inf,1});
            printf("%d\n",R);
        }
    }
    return 0;
}