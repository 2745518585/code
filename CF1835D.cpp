#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,tot,r[N],f[N];
ll k;
bool h[N];
struct tree
{
    int b,c,d;
}T[N];
vector<int> a[N],b[N];
stack<int> S;
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(auto i:a[x])
    {
        if(T[i].b==0)
        {
            T[i].d=T[x].d+1;
            dfs(i);
            T[x].c=min(T[x].c,T[i].c);
        }
        else if(h[i]==false) T[x].c=min(T[x].c,T[i].c);
    }
    if(T[x].b==T[x].c)
    {
        ++q;
        while(S.top()!=x)
        {
            b[q].push_back(S.top());
            r[S.top()]=q;
            h[S.top()]=true;
            S.pop();
        }
        b[q].push_back(x);
        r[S.top()]=q;
        h[x]=true;
        S.pop();
    }
}
int main()
{
    scanf("%d%d%lld",&n,&m,&k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(T[i].b==0)
        {
            T[i].d=1;
            dfs(i);
        }
    }
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        if(b[i].size()==1) continue;
        int w=0;
        for(auto j:b[i])
        {
            for(auto l:a[j])
            {
                if(r[j]==r[l])
                {
                    w=gcd(w,abs(T[l].d-T[j].d-1));
                }
            }
        }
        if(k%w!=0&&(w%2==1||k%w!=w/2)) continue;
        for(auto j:b[i])
        {
            ++f[T[j].d%w];
            s+=f[(T[j].d+k)%w];
        }
        for(auto j:b[i]) f[T[j].d%w]=0;
    }
    printf("%lld",s);
    return 0;
}