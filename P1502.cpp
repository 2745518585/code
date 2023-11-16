#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,q1,q2,c1[N],c2[N];
struct str
{
    int x,y,k;
    str(){}
    str(int x,int y,int k):x(x),y(y),k(k){}
};
vector<str> b[N];
struct str2
{
    int x,y,k;
}d[N];
struct tree
{
    int l,r;
    ll k,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int main()
{
    int Tot;
    scanf("%d",&Tot);
    while(Tot--)
    {
        scanf("%d%d%d",&n,&m,&k);
        q1=q2=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&d[i].x,&d[i].y,&d[i].k);
            c1[++q1]=d[i].x;
            c1[++q1]=d[i].x+m-1;
            c2[++q2]=d[i].y;
            c2[++q2]=d[i].y+k;
        }
        sort(c1+1,c1+q1+1);
        q1=unique(c1+1,c1+q1+1)-c1-1;
        sort(c2+1,c2+q2+1);
        q2=unique(c2+1,c2+q2+1)-c2-1;
        for(int i=1;i<=n;++i)
        {
            int x1=lower_bound(c1+1,c1+q1+1,d[i].x)-c1,x2=lower_bound(c1+1,c1+q1+1,d[i].x+m-1)-c1;
            int y1=lower_bound(c2+1,c2+q2+1,d[i].y)-c2,y2=lower_bound(c2+1,c2+q2+1,d[i].y+k)-c2;
            b[y1].push_back(str(x1,x2,d[i].k));
            b[y2].push_back(str(x1,x2,-d[i].k));
        }
        build(1,1,q1);
        ll s=0;
        for(int i=1;i<=q2;++i)
        {
            for(auto j:b[i]) add(1,j.x,j.y,j.k);
            b[i].clear();
            s=max(s,T[1].s);
        }
        printf("%lld\n",s);
    }
    return 0;
}