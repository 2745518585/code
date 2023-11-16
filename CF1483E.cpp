#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=501;
ll f[N][N],w;
bool query(ll x)
{
    if(x>1e14) return 0;
    printf("? %lld\n",x);
    fflush(stdout);
    char z[10];
    scanf("%s",z);
    if(z[0]=='L')
    {
        w+=x;
        return true;
    }
    else
    {
        w-=x;
        return false;
    }
}
int main()
{
    for(int i=1;i<=200;++i)
    {
        for(int j=0;j<=200;++j)
        {
            if(j>0) f[i][j]=f[i-1][j+1]+f[i-1][j-1]+1;
            else f[i][j]=f[i-1][j+1];
        }
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        w=1;
        ll p=1;
        while(query(p)) p*=2;
        if(p==1)
        {
            printf("! 0\n");
            fflush(stdout);
            continue;
        }
        ll l=p/2,r=p-1;
        query(l);
        ll x=1,y=(w>=r);
        while(f[x][y]<=r-l) ++x;
        while(l<=r)
        {
            while(r-l>f[x][y]) query(l-1),++y;
            ll z=l+f[x-1][y-1];
            while(w<z) query(l-1);
            if(query(z)) ++y,--x,l=z+1;
            else --x,--y,r=z-1;
        }
        printf("! %lld\n",l-1);
        fflush(stdout);
    }
    return 0;
}
