#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
int n,m,k,fa[N];
double b[N][2];
struct str
{
    int x,y;
    double w;
}a[N];
bool cmp(str a,str b)
{
    return a.w<b.w;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&k);
    if(n==k)
    {
        printf("0.00\n");
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lf%lf",&b[i][0],&b[i][1]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            a[++m]=(str){i,j,sqrt((b[i][0]-b[j][0])*(b[i][0]-b[j][0])+(b[i][1]-b[j][1])*(b[i][1]-b[j][1]))};
        }
    }
    sort(a+1,a+m+1,cmp);
    int s=n;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        if(find(a[i].x)!=find(a[i].y))
        {
            fa[find(a[i].x)]=find(a[i].y);
            --s;
        }
        if(s<=k)
        {
            printf("%.2lf",a[i].w);
            return 0;
        }
    }
    return 0;
}