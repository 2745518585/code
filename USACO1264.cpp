#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,m,h[N];
struct str
{
    int x,y,w;
}a[N];
struct str2
{
    int x,y,w,t;
}b[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d%d",&b[i].x,&b[i].y,&b[i].w,&b[i].t);
    }
    int s=1e9;
    for(int i=0;i<=(1<<m)-1;++i)
    {
        for(int j=0;j<=100;++j) h[j]=0;
        int w=0;
        for(int j=1;j<=m;++j)
        {
            if((i&(1<<(j-1)))==0) continue;
            for(int k=b[j].x;k<=b[j].y;++k) h[k]+=b[j].w;
            w+=b[j].t;
        }
        bool u=true;
        for(int j=1;j<=n;++j)
        {
            for(int k=a[j].x;k<=a[j].y;++k)
            {
                if(h[k]<a[j].w)
                {
                    u=false;
                    break;
                }
            }
            if(u==false) break;
        }
        if(u) s=min(s,w);
    }
    printf("%d",s);
    return 0;
}