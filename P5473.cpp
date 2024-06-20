#include<cstdio>
#include<algorithm>
#include<vector>
#include<ctime>
#include"explore.h"
#include"grader.cpp"
namespace Solve
{
    using namespace std;
    const int N=1000001;
    int n,m,t,a[N],f[N],l[N];
    bool h[N];
    vector<int> b[N];
    vector<pair<int,int>> ans;
    void modify(int x)
    {
        f[x]^=1;
        for(auto i:b[x]) f[i]^=1;
        return ::modify(x-1);
    }
    int query(int x)
    {
        return ::query(x-1);
    }
    void report(int x,int y)
    {
        ans.push_back(make_pair(x,y));
    }
    int check(int x)
    {
        if(n%10==8) return l[x];
        return h[x]||(h[x]=::check(x-1));
    }
    void solve(vector<int> p,int l,int r)
    {
        if(l>r) return;
        if(l==r)
        {
            for(auto i:p)
            {
                if(a[i]!=a[l]) report(a[i],a[l]);
            }
            return;
        }
        int z=l+r>>1;
        vector<int> p1,p2;
        while(t<z)
        {
            ++t;
            if(!h[a[t]]) modify(a[t]);
        }
        while(t>z)
        {
            if(!h[a[t]]) modify(a[t]);
            --t;
        }
        for(auto i:p)
        {
            if(i>z)
            {
                // printf("%d %d %d: %d %d\n",l,r,z,a[i],query(a[i]));
                if(query(a[i])!=f[a[i]]) p1.push_back(i);
                else p2.push_back(i);
            }
            else p1.push_back(i);
        }
        solve(p2,z+1,r);
        for(int i=l;i<=z;++i)
        {
            if(!h[a[i]]) modify(a[i]);
        }
        solve(p1,l,z);
        while(t<l-1)
        {
            ++t;
            if(!h[a[t]]) modify(a[t]);
        }
        while(t>l-1)
        {
            if(!h[a[t]]) modify(a[t]);
            --t;
        }
    }
    void main(int _n,int _m)
    {
        // srand(time(NULL));
        n=_n,m=_m;
        if(n%10==7)
        {
            vector<int> p;
            for(int i=1;i<=n;++i) p.push_back(i),a[i]=i;
            solve(p,1,n);
            for(auto [x,y]:ans) ::report(x-1,y-1);
            return;
        }
        while(true)
        {
            bool u=false;
            for(int i=1;i<=n;++i)
            {
                if(!check(i)) u=true;
            }
            if(!u) break;
            for(int i=1;i<=n;++i) a[i]=i;
            random_shuffle(a+1,a+n+1);
            vector<int> p;
            for(int i=1;i<=n;++i)
            {
                modify(a[i]);
                if(query(a[i])!=f[a[i]]&&!check(a[i])) p.push_back(i);
            }
            for(int i=1;i<=n;++i) modify(a[i]);
            // for(int i=1;i<=n;++i) printf("%d ",a[i]);printf("\n");
            // for(auto i:p) printf("%d ",a[i]);printf("\n");
            solve(p,1,n);
            for(auto [x,y]:ans)
            {
                ++l[x],++l[y];
                b[x].push_back(y);
                b[y].push_back(x);
                ::report(x-1,y-1);
                // printf("find %d %d\n",x,y);
            }
            ans.clear();
        }
    }
}
void explore(int n,int m)
{
    return Solve::main(n,m);
}