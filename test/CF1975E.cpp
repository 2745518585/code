#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,tot,tot2,b[N];
vector<int> a[N];
struct tree
{
    int f,s,d,t,z,b,bm,b2;
}T[N];
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
struct str1
{
    int x;
    str1() {}
    str1(int x):x(x) {}
    friend bool operator<(str1 a,str1 b)
    {
        return T[a.x].b<T[b.x].b;
    }
};
struct str2
{
    int x;
    str2() {}
    str2(int x):x(x) {}
    friend bool operator<(str2 a,str2 b)
    {
        return T[a.x].b2<T[b.x].b2;
    }
};
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    T[x].z=0;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int k)
{
    T[x].b=++tot;
    T[x].t=k;
    if(T[x].z!=0) dfs2(T[x].z,k);
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs2(i,i);
    }
    T[x].bm=tot;
    T[x].b2=++tot2;
}
pair<int,int> query(int x,int y)
{
    int s=0;
    while(T[x].t!=T[y].t)
    {
        if(T[T[x].t].d>=T[T[y].t].d)
        {
            s+=sgt::sum(T[x].b)-sgt::sum(T[T[x].t].b-1);
            x=T[T[x].t].f;
        }
        else
        {
            s+=sgt::sum(T[y].b)-sgt::sum(T[T[y].t].b-1);
            y=T[T[y].t].f;
        }
    }
    if(T[x].d<T[y].d) s+=sgt::sum(T[y].b)-sgt::sum(T[x].b-1);
    else s+=sgt::sum(T[x].b)-sgt::sum(T[y].b-1);
    return make_pair(T[x].d<T[y].d?x:y,s);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) a[i].clear(),sgt::T[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        tot=tot2=0;
        dfs1(1);
        dfs2(1,1);
        set<str1> Set1;
        set<str2> Set2;
        for(int i=1;i<=n;++i)
        {
            sgt::add(T[i].b,b[i]);
            if(b[i])
            {
                Set1.insert(i);
                Set2.insert(i);
            }
        }
        for(int i=1;i<=m;++i)
        {
            {
                int x;
                scanf("%d",&x);
                if(b[x])
                {
                    sgt::add(T[x].b,-1);
                    Set1.erase(x);
                    Set2.erase(x);
                }
                b[x]^=1;
                if(b[x])
                {
                    sgt::add(T[x].b,1);
                    Set1.insert(x);
                    Set2.insert(x);
                }
            }
            if(Set1.size()==0)
            {
                printf("No\n");
                continue;
            }
            int x=Set2.begin()->x,y=prev(Set1.end())->x;
            if(x==y) y=Set1.begin()->x;
            auto [z,s]=query(x,y);
            // printf("%d %d %d %d\n",x,y,z,s);
            if(T[x].d+T[y].d-T[z].d*2+1==s&&Set1.size()==s)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
    }
    return 0;
}