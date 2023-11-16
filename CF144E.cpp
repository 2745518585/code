#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200001;
int n,m,b[N];
struct str
{
    int l,r,x;
    friend bool operator <(str a,str b)
    {
        return a.r>b.r;
    }
}a[N];
priority_queue<str> Q;
bool cmp(str a,str b)
{
    return a.l<b.l;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i].l=n-y+1,a[i].r=x,a[i].x=i;
    }
    sort(a+1,a+m+1,cmp);
    int s=0,x=0;
    for(int i=1;i<=n;++i)
    {
        while(x+1<=m&&a[x+1].l<=i) Q.push(a[++x]);
        while(!Q.empty()&&Q.top().r<i) Q.pop();
        if(!Q.empty()) b[++s]=Q.top().x,Q.pop();
    }
    printf("%d\n",s);
    for(int i=1;i<=s;++i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}