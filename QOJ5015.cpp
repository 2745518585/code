#include<cstdio>
#include<algorithm>
#include<random>
#include"tree.h"
namespace Solve
{
    using namespace std;
    const int N=2001;
    mt19937 rd(random_device{}());
    int rnd(const int &x,const int &y)
    {
        return (uniform_int_distribution(x,y))(rd);
    }
    int n,f[N][N];
    vector<int> a[N],t;
    vector<pair<int,int>> ans;
    void add(int x,int y)
    {
        ans.push_back(make_pair(x,y));
        for(auto i:t) f[i][y]=f[y][i]=f[x][i]+1;
        t.push_back(y);
    }
    int query(int x,vector<int> y)
    {
        int s=0;
        for(auto i:y) s+=f[x][i];
        return s;
    }
    void solve(vector<int> a,vector<int> b)
    {
        if(b.size()==0) return;
        if(a.size()==1)
        {
            for(auto i:b) add(a[0],i);
            return;
        }
        vector<int> p;
        for(auto i:a) p.push_back(i);
        shuffle(p.begin(),p.end(),rd);
        for(int i=0;i<a.size()/2;++i) p.pop_back();
        map<int,pair<vector<int>,vector<int>>> v;
        for(auto i:a)
        {
            v[query(i,p)].first.push_back(i);
        }
        for(auto i:b)
        {
            v[ask(i,p)-p.size()].second.push_back(i);
        }
        for(auto i:v)
        {
            solve(i.second.first,i.second.second);
        }
    }
    void main(int _n)
    {
        n=_n;
        int rt=rnd(1,n);
        for(int i=1;i<=n;++i)
        {
            a[ask(rt,{i})].push_back(i);
        }
        t.push_back(rt);
        for(int i=0;i<=n;++i)
        {
            solve(a[i],a[i+1]);
        }
        for(auto i:ans)
        {
            answer(i.first,i.second);
        }
    }
}
void solver(int n, int A, int B)
{
    return Solve::main(n);
}