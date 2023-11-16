#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int N=20001;
int n,m;
struct str
{
    int a,b,c;
}a[N];
struct str2
{
    int x,t,s;
    friend bool operator <(str2 a,str2 b)
    {
        return a.s>b.s;
    }
};
priority_queue<str2> Q;
int sum(int t,int x)
{
    return a[t].a*x*x+a[t].b*x+a[t].c;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) 
    {
        scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c);
        Q.push((str2){i,1,sum(i,1)});
    }
    for(int i=1;i<=m;++i)
    {
        str2 x=Q.top();
        Q.pop();
        printf("%d ",x.s);
        x.s=sum(x.x,++x.t);
        Q.push(x);
    }
    return 0;
}