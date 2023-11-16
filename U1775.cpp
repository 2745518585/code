#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,m,a[N],b[N],c[N];
struct str
{
    int a,b;
    friend bool operator <(str a,str b)
    {
        return a.a<b.a;
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    m*=12;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&c[i]);
        c[i]+=c[i-1];
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        priority_queue<str> Q;
        for(int j=1;j<=i;++j)
        {
            Q.push((str){a[j],b[j]});
        }
        int w=0;
        for(int j=1;j<=m-c[i];++j)
        {
            if(Q.empty()) break;
            str k=Q.top();
            Q.pop();
            w+=k.a;
            k.a-=k.b;
            if(k.a>0) Q.push(k);
        }
        s=max(s,w);
    }
    printf("%d",s);
    return 0;
}