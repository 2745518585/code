#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int M=101;
int f[40000001];
char a[M][M];
int m,n;
int sum()
{
    int s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='o') s|=1<<((i-1)*5+j-1);
        }
    }
    return s;
}
bool check1(int x)
{
    for(int i=1;i<=n;++i)
    {
        if(a[x][i]=='o') return false;
    }
    return true;
}
bool check2(int x)
{
    for(int i=1;i<=m;++i)
    {
        if(a[i][x]=='o') return false;
    }
    return true;
}
int main()
{
    f[1]=1;
    f[3]=2;
    f[7]=1;
    f[15]=1;
    f[39]=2;
    f[71]=2;
    f[135]=2;
    f[35]=1;
    f[99]=1;
    f[1059]=2;
    f[67]=1;
    f[195]=2;
    f[2115]=2;
    f[33]=2;
    f[97]=1;
    f[225]=2;
    f[1121]=2;
    f[2145]=2;
    f[1057]=1;
    f[3105]=2;
    f[33825]=1;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=1;i<=5;++i)
        {
            scanf("%s",a[i]+1);
        }
        m=n=5;
        while(check1(1))
        {
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j) a[i][j]=a[i+1][j];
            }
            --m;
        }
        while(check1(m)) --m;
        while(check2(1))
        {
            for(int i=1;i<=m;++i)
            {
                for(int j=1;j<=n;++j) a[i][j]=a[i][j+1];
            }
            --n;
        }
        while(check2(n)) --n;
        int w=sum();
        if(f[w])
        {
            if(f[w]==1) printf("Away\n");
            else printf("Far\n");
            continue;
        }
        for(int i=1;i<=m/2;++i)
        {
            for(int j=1;j<=n;++j) swap(a[i][j],a[m-i+1][j]);
        }
        w=sum();
        if(f[w])
        {
            if(f[w]==1) printf("Away\n");
            else printf("Far\n");
            continue;
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n/2;++j) swap(a[i][j],a[i][n-j+1]);
        }
        w=sum();
        if(f[w])
        {
            if(f[w]==1) printf("Away\n");
            else printf("Far\n");
            continue;
        }
        for(int i=1;i<=m/2;++i)
        {
            for(int j=1;j<=n;++j) swap(a[i][j],a[m-i+1][j]);
        }
        w=sum();
        if(f[w])
        {
            if(f[w]==1) printf("Away\n");
            else printf("Far\n");
            continue;
        }
    }
    return 0;
}