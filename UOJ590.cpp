#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001;
int n,m;
struct str
{
    int a,b;
    friend bool operator<(str a,str b)
    {
        return a.b>b.b;
    }
}a[N];
bool cmp(str a,str b)
{
    return a.a<b.a;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].a,&a[i].b);
    }
    sort(a+1,a+n+1,cmp);
    priority_queue<str> Q;
    a[0].a=1;
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=a[i-1].a;j<=a[i].a-1;++j)
        {
            for(int k=1;k<=m;++k)
            {
                if(Q.empty()) break;
                s=max(s,max(j-Q.top().b,0));
                Q.pop();
            }
            if(Q.empty()) break;
        }
        Q.push(a[i]);
    }
    for(int i=a[n].a;;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(Q.empty()) break;
            s=max(s,max(i-Q.top().b,0));
            Q.pop();
        }
        if(Q.empty()) break;
    }
    printf("%d",s);
    return 0;
}