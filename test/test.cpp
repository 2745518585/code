// LUOGU_RID: 151603280
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=1e9+10;
int T,n,m,a[N],t1,b[N];
pair<int,int>b1[N];
struct dat{
    vector<pair<int,int> >d;
    int operator*(const dat &z)const{
        int z1=d.size(),z2=z.d.size(),res=M,l,r;
        for(l=0,r=z2;l<z1;++l){
            while(r&&(z.d[r-1].second|d[l].second)>=m)--r;
            if(r<z2)res=min(res,max(d[l].first,z.d[r].first));
        }return res;
    }
    void upc(pair<int,int> &p){
        if(d.empty()||d.back().second<p.second)d.push_back(p);
    }
    void upd(int A,int B,dat &z){
        for(auto &p:z.d){
            A=max(A,p.first),B|=p.second;
            if(d.empty()||d.back().second<B)d.emplace_back(A,B);
        }
    }
};
struct dc{
    dat pr,to;int v,s,x;
    void mg(dc &p,dc &q){
        v=min({p.v,q.v,p.to*q.pr});
        s=p.s|q.s,x=max(p.x,q.x);
        pr=p.pr,pr.upd(p.x,p.s,q.pr);
        to=q.to,to.upd(q.x,q.s,p.to);
    }
    void mgg(dc p,dc &q){
        v=min({p.v,q.v,p.to*q.pr});
        s=p.s|q.s,x=max(p.x,q.x);
        pr=p.pr,pr.upd(p.x,p.s,q.pr);
        to=q.to,to.upd(q.x,q.s,p.to);
    }
    void init(int l){
        v=b[l]>=m?a[l]:M;
        s=b[l],x=a[l];
        pr.d=to.d={{0,0},{a[l],b[l]}};
    }
    void init(){pr=to={},v=M,s=x=0;}
}ac[N],sum;
int T1;
#define ls x<<1
#define rs x<<1|1
void pp(int x){ac[x].mg(ac[ls],ac[rs]);}
void build(int x,int l,int r){
    if(l==r)ac[x].init(l);
    else{
        int md=(l+r)>>1;
        build(ls,l,md);
        build(rs,md+1,r),pp(x);
    }
}
void cg(int x,int l,int r,int p){
    if(l==r)ac[x].init(l);
    else{
        int md=(l+r)>>1;
        if(p>md)cg(rs,md+1,r,p);
        else cg(ls,l,md,p);pp(x);
    }
}
void ask(int x,int l,int r,int L,int R){
    if(l>=L&&r<=R)sum.mgg(sum,ac[x]);
    else{
        int md=(l+r)>>1;
        if(L<=md)ask(ls,l,md,L,R);
        if(md<R)ask(rs,md+1,r,L,R);
    }
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0);
    int i,k,l,r,x;
    for(cin>>T;T--;){
        cin>>n>>m;
        for(i=1;i<=n;++i)cin>>a[i];
        for(i=1;i<=n;++i)cin>>b[i];
        build(1,1,n);
        for(cin>>T1;T1--;){
            cin>>k;
            if(k==1){
                cin>>x,cin>>b[x];
                cg(1,1,n,x);
            }else{
                sum.init(),cin>>l>>r;
                ask(1,1,n,l,r);
                printf("%d ",sum.v==M?-1:sum.v);
            }
        }puts("");
    }
    return 0;
}
//taoluti,copied