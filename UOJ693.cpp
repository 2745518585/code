#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include"subway.h"
#include"grader.cpp"
namespace Solve
{
    using namespace std;
    const int N=1000001;
    int n,t,q;
    stack<pair<int,int>> S;
    void init(int _n)
    {
        n=_n;
    }
    int solve(int x)
    {
        while(t+1<=n&&check(t+1)) merge(++t),S.push(make_pair(t,1));
        if(q==0)
        {
            vector<int> z;
            while(!S.empty()) z.push_back(S.top().first),S.pop(),undo();
            for(auto i:z) S.push(make_pair(i,0)),merge(i);
            q=S.size();
        }
        else if(S.top().second==1)
        {
            vector<int> z1,z2;
            while(S.top().second==1) z1.push_back(S.top().first),S.pop(),undo();
            for(int i=1;i<=(q&-q);++i) z2.push_back(S.top().first),S.pop(),undo();
            while(!z1.empty()) S.push(make_pair(z1.back(),1)),merge(z1.back()),z1.pop_back();
            while(!z2.empty()) S.push(make_pair(z2.back(),0)),merge(z2.back()),z2.pop_back();
        }
        S.pop();
        undo();
        --q;
        return t;
    }
}
void init(int,int n,int)
{
    Solve::init(n);
}
int solve(int x)
{
    return Solve::solve(x);
}