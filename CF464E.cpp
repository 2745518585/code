#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,q,w,s1,s2,g[N];
ll pow2[N];
bool h[N];
vector<pair<int,int>> a[N];
struct tree
{
    tree *l,*r;
    int s,k,u;
    ll t;
    tree():l(NULL),r(NULL),s(0),k(0),u(0),t(0){}
}*f[N];
void pushup(tree *x)
{
    x->s=(x->l!=NULL?x->l->s:0)+(x->r!=NULL?x->r->s:0);
    x->t=((x->l!=NULL?x->l->t:0)+(x->r!=NULL?x->r->t:0))%P;
}
void pushdown(tree *x)
{
    if(x==NULL||x->k==0) return;
    if(x->l!=NULL)
    {
        if(x->l->u!=x->u)
        {
            x->l=new tree;
            x->l->u=x->u;
        }
        x->l->s=x->l->t=0;
        x->l->k=1;
    }
    if(x->r!=NULL)
    {
        if(x->r->u!=x->u)
        {
            x->r=new tree;
            x->r->u=x->u;
        }
        x->r->s=(x->r)->t=0;
        x->r->k=1;
    }
    x->k=0;
}
void add1(tree *&x,int ls,int rs,int q,int u)
{
    if(x==NULL) x=new tree,x->u=u;
    if(x->u!=u)
    {
        tree *z=new tree;
        (*z)=(*x);
        z->u=u;
        x=z;
    }
    if(ls==rs)
    {
        (x->s)=1;
        (x->t)=pow2[ls];
        return;
    }
    pushdown(x);
    int z=ls+rs>>1;
    if(q<=z) add1(x->l,ls,z,q,u);
    else add1(x->r,z+1,rs,q,u);
    pushup(x);
}
void add2(tree *&x,int ls,int rs,int l,int r,int u)
{
    if(l>r) return;
    if(x==NULL) x=new tree,x->u=u;
    if(x->u!=u)
    {
        tree *z=new tree;
        (*z)=(*x);
        z->u=u;
        x=z;
    }
    if(ls>=l&&rs<=r)
    {
        (x->s)=(x->t)=0;
        (x->k)=1;
        return;
    }
    pushdown(x);
    int z=ls+rs>>1;
    if(l<=z) add2(x->l,ls,z,l,r,u);
    if(r>z) add2(x->r,z+1,rs,l,r,u);
    pushup(x);
}
int sum(tree *x,int ls,int rs,int l,int r)
{
    if(l>r) return 0;
    if(x==NULL) return min(rs,r)-max(ls,l)+1;
    if(ls>=l&&rs<=r) return (rs-ls+1)-(x->s);
    pushdown(x);
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(x->l,ls,z,l,r);
    if(r>z) s+=sum(x->r,z+1,rs,l,r);
    return s;
}
int find(tree *x,int ls,int rs,int q)
{
    if(ls==rs) return ls;
    if(x==NULL) return ls+q-1;
    pushdown(x);
    int z=ls+rs>>1,k=(z-ls+1)-(x->l!=NULL?x->l->s:0);
    if(q<=k) return find(x->l,ls,z,q);
    return find(x->r,z+1,rs,q-k);
}
bool check(tree* x1,tree* x2,int ls,int rs)
{
    if(x2==NULL) return false;
    if(x1==NULL) return true;
    if(ls==rs) return x1->s<x2->s;
    pushdown(x1);
    pushdown(x2);
    int z=ls+rs>>1;
    if((x1->r!=NULL?x1->r->t:0)!=(x2->r!=NULL?x2->r->t:0)) return check(x1->r,x2->r,z+1,rs);
    return check(x1->l,x2->l,ls,z);
}
void del(tree *&x)
{
    if(x->l==x) exit(1);
    if(x->l!=NULL&&x->l->u==x->u) del(x->l);
    if(x->r!=NULL&&x->r->u==x->u) del(x->r);
    delete x;
    x=NULL;
}
struct str
{
    int x;
    tree *s;
    str(){}
    str(int x,tree *s):x(x),s(s){}
    friend bool operator<(str a,str b)
    {
        return check(b.s,a.s,0,q);
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
        q=max(q,w);
    }
    q+=30;
    scanf("%d%d",&s1,&s2);
    pow2[0]=1;
    for(int i=1;i<=q;++i) pow2[i]=pow2[i-1]*2%P;
    priority_queue<str> Q;
    for(int i=1;i<=n;++i) add1(f[i],0,q,q,++w);
    add2(f[s1],0,q,0,q,++w);
    Q.push(str(s1,f[s1]));
    while(!Q.empty())
    {
        int k=Q.top().x;
        Q.pop();
        if(h[k]==true) continue;
        h[k]=true;
        for(auto i:a[k])
        {
            tree *z=f[k];
            ++w;
            int p=find(z,0,q,sum(z,0,q,0,i.second-1)+1);
            add1(z,0,q,p,w);
            add2(z,0,q,i.second,p-1,w);
            if(check(z,f[i.first],0,q))
            {
                f[i.first]=z;
                g[i.first]=k;
                Q.push(str(i.first,f[i.first]));
            }
            else del(z);
        }
    }
    if(sum(f[s2],0,q,q,q)==0)
    {
        printf("-1");
        return 0;
    }
    printf("%lld\n",f[s2]->t);
    vector<int> z;
    int x=s2;
    while(x!=s1)
    {
        z.push_back(x);
        x=g[x];
    }
    z.push_back(s1);
    printf("%d\n",z.size());
    while(!z.empty()) printf("%d ",z.back()),z.pop_back();
    return 0;
}