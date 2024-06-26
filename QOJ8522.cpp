#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,b[N],g[N],h[N];
ll s;
struct str
{
    int x,y,w;
}a[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
bool cmp2(str a,str b)
{
    return a.y<b.y;
}
void solve(int l,int r,vector<str> p)
{
    if(l==r)
    {
        for(auto i:p) s+=abs(b[l]-b[i.w]);
        return;
    }
    int z=l+r+1>>1;
    multiset<int> Set;
    Set.insert(n+1);
    for(auto i:p)
    {
        if(i.w<z) Set.insert(i.y);
        else
        {
            Set.insert(0);
            auto z=prev(Set.upper_bound(i.y));
            g[i.x]=*z;
            Set.erase(z);
        }
    }
    int x=0;
    reverse(p.begin(),p.end());
    vector<str> p1,p2;
    for(auto i:p)
    {
        if(i.w>=z)
        {
            if(x>=g[i.x]&&x<i.y) x=i.y;
        }
        if(i.y>x) p1.push_back(i);
        else p2.push_back(i);
    }
    reverse(p1.begin(),p1.end());
    reverse(p2.begin(),p2.end());
    solve(l,z-1,p1);
    solve(z,r,p2);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
        b[++q]=a[i].w;
    }
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i].w=lower_bound(b+1,b+q+1,a[i].w)-b;
        ++h[a[i].x];
    }
    for(int i=1;i<=n;++i) h[i]+=h[i-1];
    sort(a+1,a+n+1,cmp2);
    for(int i=n;i>=1;--i)
    {
        a[i].x=h[a[i].x]--;
    }
    sort(a+1,a+n+1,cmp);
    vector<str> p;
    for(int i=1;i<=n;++i) p.push_back(a[i]);
    solve(1,q,p);
    printf("%lld",s);
    return 0;
}