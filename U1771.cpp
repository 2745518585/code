#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    priority_queue<int> Q1;
    for(int i=1;i<=n;++i) Q1.push(a[i]);
    while(Q1.size()>1)
    {
        int x=Q1.top();
        Q1.pop();
        int y=Q1.top();
        Q1.pop();
        Q1.push(x*y+1);
    }
    priority_queue<int,vector<int>,greater<int> > Q2;
    for(int i=1;i<=n;++i) Q2.push(a[i]);
    while(Q2.size()>1)
    {
        int x=Q2.top();
        Q2.pop();
        int y=Q2.top();
        Q2.pop();
        Q2.push(x*y+1);
    }
    printf("%d",Q2.top()-Q1.top());
    return 0;
}