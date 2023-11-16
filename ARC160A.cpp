#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,k;
vector<int> solve(int m,int k,vector<int> a)
{
    for(int i=1;i<=m;++i)
    {
        if(a[1]==i)
        {
            if(k<=m*(m-1)/2+(n-m+1))
            {
                vector<int> b;
                b.resize(m+1);
                for(int j=1;j<=m-1;++j) b[j]=a[j+1]-(a[j+1]>i);
                vector<int> c=solve(m-1,k,b),d;
                d.resize(m+1);
                for(int j=1;j<=m-1;++j) d[j+1]=c[j]+(c[j]>=i);
                d[1]=i;
                return d;
            }
            else k-=m*(m-1)/2+(n-m+1);
        }
        else
        {
            if(k==1)
            {
                int x=0;
                for(int j=1;j<=m;++j)
                {
                    if(a[j]==i)
                    {
                        x=j;
                        break;
                    }
                }
                for(int j=1;j<=x/2;++j) swap(a[j],a[x-j+1]);
                return a;
            }
            else --k;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    vector<int> a;
    a.resize(n+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    vector<int> b=solve(n,k,a);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}