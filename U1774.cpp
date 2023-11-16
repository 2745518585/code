#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n;
struct str
{
    int k,t;
}a[N];
bool cmp(str a,str b)
{
    return a.t>b.t;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].t,&a[i].k);
    }
    sort(a+1,a+n+1,cmp);
    priority_queue<int> Q;
    int t=1;
    for(;t<=n;++t)
    {
        if(a[t].t>n) Q.push(a[t].k);
        else break;
    }
    int s=0;
    for(int i=n;i>=1;--i)
    {
        for(;t<=n;++t)
        {
            if(a[t].t==i) Q.push(a[t].k);
            else break;
        }
        if(Q.empty()) continue;
        s+=Q.top();
        Q.pop();
    }
    printf("%d",s);
    return 0;
}