#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+50,S=316,M=S+50;
const ll inf=1e18;

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
template<class T> inline void read(T &x) {
  x = 0;int f = 0;char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc());
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc());
  x = (f == 1 ? ~ x + 1 : x);
}
template<class T, class... Args> inline void read(T &x, Args&... args) { read(x), read(args...); }
template<class T> inline void readch(T &x) { char ch = gc(); for (; !isalpha(ch); ch = gc()); x = ch; }
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template<class T> inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter ++ = '-', x = ~ x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10);
  for (; l; -- l, *iter ++ = c[l] + '0');*iter ++ = ch;
  flush();
}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }
} // IO
using namespace IO;

int tim;

struct query
{
    int op,l,r,x;
    ll suf,ans,ad;

    void in()
    {
        read(op,l,r);
        if(op==1)read(x);
    }
}Q[N];

int b[256];
pair<int,ll>g[N],d[N];

void SORT(int*a,int n)
{
    // int bg=clock();
    ll ba=inf;
    for(int i=1;i<=n;i++)d[i]=make_pair(a[i],Q[a[i]].ad),ba=min(ba,Q[a[i]].ad);
    for(int i=1;i<=n;i++)d[i].second-=ba;
    const int w=255;
    memset(b,0,sizeof b);
    for(int i=1;i<=n;i++)b[d[i].second&w]++;
    for(int i=1;i<=w;i++)b[i]+=b[i-1];
    for(int i=n;i>=1;i--)g[b[d[i].second&w]--]=d[i];
    memset(b,0,sizeof b);
    for(int i=1;i<=n;i++)b[g[i].second>>8&w]++;
    for(int i=1;i<=w;i++)b[i]+=b[i-1];
    for(int i=n;i>=1;i--)d[b[g[i].second>>8&w]--]=g[i];
    memset(b,0,sizeof b);
    for(int i=1;i<=n;i++)b[d[i].second>>16&w]++;
    for(int i=1;i<=w;i++)b[i]+=b[i-1];
    for(int i=n;i>=1;i--)g[b[d[i].second>>16&w]--]=d[i];
    memset(b,0,sizeof b);
    for(int i=1;i<=n;i++)b[g[i].second>>24&w]++;
    for(int i=1;i<=w;i++)b[i]+=b[i-1];
    for(int i=n;i>=1;i--)a[b[g[i].second>>24&w]--]=g[i].first;
    // tim+=clock()-bg;
}

int n,q,a[N];

struct poi
{
    ll x,y;

    poi operator-(poi b)
    {
        return (poi){x-b.x,y-b.y};
    }

    poi operator+(poi b)
    {
        return (poi){x+b.x,y+b.y};
    }

    poi ad(ll d)
    {
        return (poi){x,x*d+y};
    }

    ll f(int p){return x*p+y;}
}p[N],tmp[N];

ll cross(poi a,poi b){return a.x*b.y-a.y*b.x;}

int chk(poi a,poi b,poi c)
{
    return cross(c-a,b-a)<=0;
}

struct segpoi
{
    int n,pos;poi*a;

    void mk(int m)
    {
        a=new poi[m+5];
    }

    void init(poi*p,int m)
    {
        pos=n=0;a[0]=p[0];
        for(int i=1;i<=m;i++)if(p[i].y!=-inf)
        {
            while(n&&chk(a[n-1],a[n],p[i]))n--;
            a[++n]=p[i];
        }
        a[n+1]=(poi){inf,inf};
    }

    ll find(int x)
    {
        while(pos+1<=n&&a[pos].f(x)<a[pos+1].f(x))pos++;
        return a[pos].f(x);
    }
};

void ckmax(ll&x,ll y){x=max(x,y);}

struct seg
{
    ll sum;
    segpoi fir,suf,sub;

    void init(ll*a,int n,seg&l,seg&r,ll lal,ll lar)
    {
        // int bg=clock();
        if(n==1)
        {
            p[0]=(poi){0,0};
            ll w=0;
            for(int i=0;i<n;i++)p[i+1]=(poi){i+1,w+=a[i]};
            fir.init(p,n);
            w=0;
            for(int i=0;i<n;i++)p[i+1]=(poi){i+1,w+=a[n-i-1]};
            suf.init(p,n);
            sum=w;
        }
        else
        {
            int cc=0,rz=n/2,lz=n-n/2;
            sum=l.sum+r.sum+lz*lal+rz*lar;
            for(int i=0;i<=l.fir.n;i++)p[cc++]=l.fir.a[i].ad(lal);
            for(int i=1;i<=r.fir.n;i++)p[cc++]=(poi){r.fir.a[i].x+lz,r.fir.a[i].ad(lar).y+l.sum+lz*lal};
            fir.init(p,cc-1);
            cc=0;
            for(int i=0;i<=r.suf.n;i++)p[cc++]=r.suf.a[i].ad(lar);
            for(int i=1;i<=l.suf.n;i++)p[cc++]=(poi){l.suf.a[i].x+rz,l.suf.a[i].ad(lal).y+r.sum+rz*lar};
            suf.init(p,cc-1);
        }
        // tim+=clock()-bg;
        // bg=clock();
        if(n==1)return sub.init(p,n);
        int pos1=1,pos2=1,cc=0;poi now=(poi){0,0};
        auto&s=l.suf,&f=r.fir;
        while(pos1<=s.n||pos2<=f.n)
        {
            if(pos1>s.n)now=now+(f.a[pos2]-f.a[pos2-1]).ad(lar),pos2++;
            else if(pos2>f.n)now=now+(s.a[pos1]-s.a[pos1-1]).ad(lal),pos1++;
            else if(cross((f.a[pos2]-f.a[pos2-1]).ad(lar),(s.a[pos1]-s.a[pos1-1]).ad(lal))<=0)now=now+(f.a[pos2]-f.a[pos2-1]).ad(lar),pos2++;
            else now=now+(s.a[pos1]-s.a[pos1-1]).ad(lal),pos1++;
            tmp[cc++]=now;
        }
        int cnt=0;
        auto&L=l.sub.a,&R=r.sub.a;tmp[cc].x=inf;
        for(int i=0,p1=0,p2=0;i<=cc;i++)
        {
            while(min(L[p1].x,R[p2].x)<tmp[i].x)
            {
                if(L[p1].x==R[p2].x)p[cnt++]=(poi){L[p1].x,max(L[p1].ad(lal).y,R[p2].ad(lar).y)},p1++,p2++;
                else if(L[p1].x<R[p2].x)p[cnt++]=L[p1++].ad(lal);
                else p[cnt++]=R[p2++].ad(lar);
            }
            if(i==cc)break;
            ll w=tmp[i].y;
            if(L[p1].x==tmp[i].x)w=max(w,L[p1++].ad(lal).y);
            if(R[p2].x==tmp[i].x)w=max(w,R[p2++].ad(lar).y);
            p[cnt++]=(poi){tmp[i].x,w};
        }
        sub.init(p,cnt-1);
        // tim+=clock()-bg;
    }
}T[N];

namespace Block
{
    int L,R,n;
    ll la[N],a[M];
    int s[N],top;

    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid ((l+r)>>1)
    #define LS ls,l,mid
    #define RS rs,mid+1,r

    void build(int x,int l,int r,int f)
    {
        if(f)
        {
            T[x].fir.mk(r-l+1);
            T[x].suf.mk(r-l+1);
            T[x].sub.mk(r-l+1);
        }
        la[x]=0;
        if(l==r)return T[x].init(a+l,1,T[0],T[0],0,0);
        build(LS,f);build(RS,f);
        T[x].init(a+l,r-l+1,T[ls],T[rs],0,0);
    }

    void down(int x){la[ls]+=la[x];la[rs]+=la[x];la[x]=0;}

    void add(int x,int l,int r,int L,int R,int d)
    {
        if(L<=l&&R>=r)return la[x]+=d,void();
        down(x);
        if(L<=mid)add(LS,L,R,d);
        if(R>mid)add(RS,L,R,d);
        T[x].init(a+l,r-l+1,T[ls],T[rs],la[ls],la[rs]);
    }

    void sol(int pos,int l,int r)
    {
        ll d=Q[pos].ad,fir=0,sub=0,suf=0,w=0;
        for(int i=l;i<=r;i++)
        {
            ll x=a[i]+d;
            w+=x;
            fir=max(fir,w);
            suf=max(0ll,max(x,suf+x));
            sub=max(sub,suf);
        }
        Q[pos].ans=max(Q[pos].ans,max(sub,fir+Q[pos].suf));
        Q[pos].suf=max(suf,Q[pos].suf+w);
    }

    void sol()
    {
        if(!top)return;
        SORT(s,top);
        T[1].sub.pos=T[1].fir.pos=T[1].suf.pos=0;
        for(int p=1;p<=top;p++)
        {
            int i=s[p],l=Q[i].l-L+1,r=Q[i].r-L+1;
            l=max(l,1);r=min(r,n);
            if(l==1&&r==n)
            {
                ll d=Q[i].ad;
                ckmax(Q[i].ans,max(Q[i].suf+T[1].fir.find(d),T[1].sub.find(d)));
                Q[i].suf=max(Q[i].suf+T[1].sum+n*d,T[1].suf.find(d));
            }
            else sol(i,l,r);
        }
        top=0;
    }

    void solve(int*p,int m,int pl,int f)
    {
        f|=(m!=S);n=m;L=pl;R=L+n-1;
        for(int i=0;i<m;i++)a[i+1]=p[i];
        build(1,1,n,f);
        ll la=0;
        for(int i=1;i<=q;i++)
        {
            if(Q[i].l>R||Q[i].r<L)continue;
            int l=Q[i].l-L+1,r=Q[i].r-L+1;
            l=max(l,1);r=min(r,n);
            if(Q[i].op==1)
            {
                if(l!=1||r!=n)
                {
                    sol();
                    for(int j=l;j<=r;j++)a[j]+=Q[i].x;
                    add(1,1,n,l,r,Q[i].x);
                }
                else la+=Q[i].x;
            }
            else Q[i].ad=la,s[++top]=i;
        }
        sol();
    }
};

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    read(n,q);
    for(int i=1;i<=n;i++)read(a[i]);
    for(int i=1;i<=q;i++)Q[i].in();
    // cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
    for(int i=1;i<=n;i+=S)Block::solve(a+i,min(S,n-i+1),i,i==1);
    for(int i=1;i<=q;i++)if(Q[i].op==2)write(Q[i].ans);
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n'<<tim*1.0/CLOCKS_PER_SEC;
}