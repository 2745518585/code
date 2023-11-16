#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2001;
int n,f[N][N];
int sum(int l,int r,int k)
{
    if(l==0) ++l;
    if(r==n+1) --r;
    if(l>r) return 0;
    if(l==r) return 1;
    if(k==2)
    {
        if(f[l][r]!=-1) return f[l][r];
        printf("? %d %d %d\n",l,r,2);
        fflush(stdout);
        scanf("%d",&f[l][r]);
        return f[l][r];
    }
    printf("? %d %d %d\n",l,r,k);
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
int query(int l,int r)
{
    return sum(1,r,2)-sum(1,l-1,2)+sum(l,n,2)-sum(r+1,n,2)-(r-l+1);
}
int main()
{
    scanf("%d",&n);
    bool u=false;
    if(n%2==0) u=true;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=-1;
    }
    f[1][n]=(n/2)+1;
    int l=1,r=n;
    while(l<r)
    {
        int z=l+r>>1;
        if(l==r-1)
        {
            if(u==true)
            {
                if(z==1)
                {
                    if(sum(z+1,n,n)==1) l=z+1;
                    else r=z;
                }
                else
                {
                    if(sum(1,z,n)==1) r=z;
                    else l=z+1;
                }
                u=false;
            }
            else
            {
                if(sum(1,r,2)-sum(1,l-1,2)==1)
                {
                    if(sum(1,z,2)-sum(1,l-1,2)==1) r=z;
                    else l=z+1;
                }
                else
                {
                    if(sum(l,n,2)-sum(z+1,n,2)==1) r=z;
                    else l=z+1;
                }
            }
            continue;
        }
        int p=query(l,z);
        if(u==false)
        {
            if(p==1) r=z;
            else l=z+1;
        }
        else
        {
            if(p==2) r=z;
            else if(p==0) l=z+1;
            else
            {
                if(z==1)
                {
                    if(sum(z+1,n,n)==1) l=z+1;
                    else r=z;
                }
                else
                {
                    if(sum(1,z,n)==1) r=z;
                    else l=z+1;
                }
                u=false;
            }
        }
    }
    printf("! %d",l);
    fflush(stdout);
    return 0;
}