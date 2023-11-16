#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,a[N],b[N],g[N],h[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ++h[a[i]];
        ++g[a[i]%2];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        --h[b[i]];
    }
    for(int i=1;i<=1000000;++i)
    {
        if(h[i]!=0)
        {
            printf("No");
            return 0;
        }
    }
    bool u=true;
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=b[i])
        {
            u=false;
            break;
        }
    }
    if(u)
    {
        printf("Yes");
        return 0;
    }
    if(g[0]==0)
    {
        printf("No");
        return 0;
    }
    if(g[0]==1)
    {
        printf("Yes");
        return 0;
    }
    if(g[0]==2)
    {
        int x=0,x2=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]%2==0)
            {
                if(x==0) x=i;
                else x2=i;
            }
        }
        int y=0,y2=0;
        for(int i=1;i<=n;++i)
        {
            if(b[i]%2==0)
            {
                if(y==0) y=i;
                else y2=i;
            }
        }
        if(a[x]!=b[y]||(x2-x==1&&x-2<1&&x2+2>n)||(y2-y==1&&y-2<1&&y2+2>n)) printf("No");
        else printf("Yes");
        return 0;
    }
    bool v=false;
    for(int i=1;i<=n-2;++i)
    {
        if(a[i]%2+a[i+1]%2+a[i+2]%2==2) u=true;
        if(b[i]%2+b[i+1]%2+b[i+2]%2==2) v=true;
    }
    if(u&&v)
    {
        printf("Yes");
        return 0;
    }
    if(u||v)
    {
        printf("No");
        return 0;
    }
    u=false;
    for(int i=1;i<=n;++i)
    {
        if(a[i]%2!=b[i]%2)
        {
            u=true;
            break;
        }
    }
    if(u)
    {
        printf("No");
        return 0;
    }
    auto check=[&](int x,int y)
    {
        if(x>y) return true;
        if(y-x<=1)
        {
            for(int i=x;i<=y;++i)
            {
                if(a[i]!=b[i]) return false;
            }
            return true;
        }
        for(int i=x;i<=y;++i) h[a[i]]=0;
        for(int i=x;i<=y;++i) ++h[a[i]],--h[b[i]];
        for(int i=x;i<=y;++i)
        {
            if(h[a[i]]!=0) return false;
        }
        return true;
    };
    int x=0;
    u=false;
    for(int i=1;i<=n;++i)
    {
        if(a[i]%2==1)
        {
            if(a[i]!=b[i])
            {
                u=true;
                break;
            }
            if(!check(x+1,i-1))
            {
                u=true;
                break;
            }
            x=i;
        }
    }
    if(!check(x+1,n)) u=true;
    if(u)
    {
        printf("No");
        return 0;
    }
    printf("Yes");
    return 0;
}