#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int n,a[N][N];
bool h[N*N];
int main()
{
    scanf("%d",&n);
    if(n==3)
    {
        printf("3 9 1\n");
        printf("5 7 8\n");
        printf("4 2 6\n");
        return 0;
    }
    if(n%2==0)
    {
        int x=1;
        for(int i=1;i<=n;++i)
        {
            while(x%3!=i%2+1||h[x])
            {
                x+=2;
                if(x>n*n) x=1;
            }
            a[n/2][i]=x;
            h[x]=true;
        }
        for(int i=1;i<=n/2-1;++i)
        {
            for(int j=1;j<=n;++j)
            {
                while(h[x])
                {
                    x+=2;
                    if(x>n*n) x=1;
                }
                a[i][j]=x;
                h[x]=true;
            }
        }
        x=2;
        for(int i=1;i<=n;++i)
        {
            while(x%3!=(i%2^1)+1||h[x])
            {
                x+=2;
                if(x>n*n) x=2;
            }
            a[n/2+1][i]=x;
            h[x]=true;
        }
        for(int i=n/2+2;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                while(h[x])
                {
                    x+=2;
                    if(x>n*n) x=2;
                }
                a[i][j]=x;
                h[x]=true;
            }
        }
    }
    else
    {
        int x=1;
        for(int i=1;i<=n/2+1;++i)
        {
            while(x%3!=i%2+1||h[x])
            {
                x+=2;
                if(x>n*n) x=1;
            }
            a[n/2+1][i]=x;
            h[x]=true;
        }
        for(int i=n/2+2;i<=n;++i)
        {
            while(x%3!=(i%2^1)+1||h[x])
            {
                x+=2;
                if(x>n*n) x=1;
            }
            a[n/2][i]=x;
            h[x]=true;
        }
        x=2;
        for(int i=1;i<=n/2+1;++i)
        {
            while(x%3!=(i%2^1)+1||h[x])
            {
                x+=2;
                if(x>n*n) x=2;
            }
            a[n/2+2][i]=x;
            h[x]=true;
        }
        for(int i=n/2+2;i<=n;++i)
        {
            while(x%3!=i%2+1||h[x])
            {
                x+=2;
                if(x>n*n) x=2;
            }
            a[n/2+1][i]=x;
            h[x]=true;
        }
        x=1;
        for(int i=1;i<=n/2+1;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(a[i][j]!=0) continue;
                while(h[x])
                {
                    x+=2;
                    if(x>n*n) x=1;
                }
                a[i][j]=x;
                h[x]=true;
            }
        }
        x=2;
        for(int i=n/2+1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(a[i][j]!=0) continue;
                while(h[x])
                {
                    x+=2;
                    if(x>n*n) x=2;
                }
                a[i][j]=x;
                h[x]=true;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}