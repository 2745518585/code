#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,t[N];
struct str
{
    int x,l,r;
    str(){}
    str(int x,int l,int r):x(x),l(l),r(r){}
    friend bool operator <(str a,str b)
    {
        return a.l>b.l;
    }
};
vector<str> a[N];
bool cmp(str a,str b)
{
    return a.l<b.l;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        --r;
        int l1=l,l2=l,r1=r,r2=r;
        if(l%2==1) ++l1;
        else ++l2;
        if(r%2==1) --r1;
        else --r2;
        if(l1<=r1)
        {
            a[x].push_back(str(y+n,l1,r1));
            a[y].push_back(str(x+n,l1,r1));
        }
        if(l2<=r2)
        {
            a[x+n].push_back(str(y,l2,r2));
            a[y+n].push_back(str(x,l2,r2));
        }
    }
    for(int i=1;i<=n*2;++i)
    {
        sort(a[i].begin(),a[i].end(),cmp);
    }
    priority_queue<str> Q;
    Q.push(str(1,0,0));
    while(!Q.empty())
    {
        str k=Q.top();
        Q.pop();
        if(k.x==n||k.x==n*2)
        {
            printf("%d",k.l);
            return 0;
        }
        for(int i=t[k.x];i<a[k.x].size();++i)
        {
            if(a[k.x][i].l>k.r) break;
            t[k.x]=i+1;
            if(k.l<=a[k.x][i].r) Q.push(str(a[k.x][i].x,max(k.l,a[k.x][i].l)+1,a[k.x][i].r+1));
        }
    }
    printf("-1");
    return 0;
}