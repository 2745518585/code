#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int N=1000001;
int n,q,a[N],f[N],h[N];
vector<int> b[N];
set<int> c;
int solve(vector<int> d)
{
    int s=0;
    int t=d.size();
    for(int j=0;j<=t*2;++j) f[j]=n+1;
    set<int>::iterator p=c.lower_bound(*d.begin());
    if(p!=c.begin()) f[t]=*prev(p);
    else f[t]=0;
    int w=0;
    for(auto i:d)
    {
        s=max(s,i-f[w+t]-1);
        if(a[i]==q) ++w;
        else --w;
        f[w+t]=min(f[w+t],i);
    }
    p=c.upper_bound(*prev(d.end()));
    if(p!=c.end()) s=max(s,(*p)-f[w+t]-1);
    else s=max(s,(n+1)-f[w+t]-1);
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[a[i]].push_back(i);
        ++h[a[i]];
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]>h[q]) q=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]==q) c.insert(i);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        if(i==q||h[i]==0) continue;
        vector<int> d;
        for(auto j:b[i])
        {
            set<int>::iterator p=c.upper_bound(j);
            if(p!=c.begin())
            {
                d.push_back(*prev(p));
                c.erase(prev(p));
            }
        }
        for(auto j:d) c.insert(j);
        for(auto j:b[i])
        {
            set<int>::iterator p=c.upper_bound(j);
            if(p!=c.end())
            {
                d.push_back(*p);
                c.erase(p);
            }
        }
        for(auto j:d) c.insert(j);
        for(auto j:b[i]) d.push_back(j);
        sort(d.begin(),d.end());
        vector<int>::iterator z=unique(d.begin(),d.end());
        d.erase(z,d.end());
        queue<int> e;
        for(auto j:d) e.push(j);
        while(!e.empty())
        {
            d.clear();
            d.push_back(e.front());
            e.pop();
            while(!e.empty())
            {
                set<int>::iterator p=c.upper_bound(*prev(d.end()));
                if(p!=c.end()&&(*p)<e.front()) break;
                d.push_back(e.front()),e.pop();
            }
            s=max(s,solve(d));
        }
    }
    printf("%d",s);
    return 0;
}