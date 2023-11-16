#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100001;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
int n,g[2][2];
point a[N];
bool check(int x1,int x2,int y1,int y2,int z1,int z2)
{
    return (((x1+y1)%2&&(x2+y2)%2)+((x1+z1)%2&&(x2+z2)%2)+((y1+z1)%2&&(y2+z2)%2))%2==0;
}
ll sum(int x1,int x2,int y1,int y2,int z1,int z2)
{
    ll s=1;
    s*=g[x1][x2];
    s*=(g[y1][y2]-(x1==y1&&x2==y2));
    s*=(g[z1][z2]-(x1==z1&&x2==z2)-(y1==z1&&y2==z2));
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].x/=2,a[i].y/=2;
        ++g[a[i].x%2][a[i].y%2];
    }
    ll s=0;
    for(int i1=0;i1<=1;++i1)
    {
        for(int i2=0;i2<=1;++i2)
        {
            for(int j1=0;j1<=1;++j1)
            {
                for(int j2=0;j2<=1;++j2)
                {
                    for(int k1=0;k1<=1;++k1)
                    {
                        for(int k2=0;k2<=1;++k2)
                        {
                            if(check(i1,i2,j1,j2,k1,k2)) s+=sum(i1,i2,j1,j2,k1,k2);
                        }
                    }
                }
            }
        }
    }
    printf("%lld",s/6);
    return 0;
}