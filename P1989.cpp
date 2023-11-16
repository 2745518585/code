#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N],l[N];
bool h[N];
ll s;
struct road
{
    int m,q;
}a[N<<1];
struct road2
{
    int x,y;
}a2[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a2[i].x,&a2[i].y);
        ++l[a2[i].x],++l[a2[i].y];
    }
    for(int i=1;i<=m;++i)
    {
        if(l[a2[i].x]<l[a2[i].y]||(l[a2[i].x]==l[a2[i].y]&&a2[i].x<a2[i].y)) road(a2[i].x,a2[i].y);
        else road(a2[i].y,a2[i].x);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=t[i];j!=0;j=a[j].q) h[a[j].m]=true;
        for(int j=t[i];j!=0;j=a[j].q)
        {
            for(int k=t[a[j].m];k!=0;k=a[k].q)
            {
                if(h[a[k].m]) ++s;
            }
        }
        for(int j=t[i];j!=0;j=a[j].q) h[a[j].m]=false;
    }
    printf("%lld",s);
    return 0;
}