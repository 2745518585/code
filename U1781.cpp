#include<bits/stdc++.h>
using namespace std;
const int N=101;
int n,m,a[N][2],fa[N];
struct str
{
    int x,y,w;
}b[N*N];
bool cmp(str a,str b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
        for(int j=1;j<i;++j)
        {
            b[++m].w=(abs(a[i][0]-a[j][0])+abs(a[i][1]-a[j][1])+1)/2;
            b[m].x=i,b[m].y=j;
        }
    }
    sort(b+1,b+m+1,cmp);
    for(int i=1;i<=n;++i) fa[i]=i;
    int s=0;
    for(int i=1;i<=m;++i)
    {
        if(find(b[i].x)!=find(b[i].y))
        {
            ++s;
            fa[find(b[i].x)]=find(b[i].y);
            if(s==n-1)
            {
                printf("%d",b[i].w);
                return 0;
            }
        }
    }
    return 0;
}