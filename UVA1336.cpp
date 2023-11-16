#include<cstdio>
#include<algorithm>
using namespace std;
int n,m=0,v,q,s1,s2,s,a[1001],b[1001],c[1001],f[1001][1001][2];
void abc()
{
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d%d%d",&a[i],&x,&b[i]);
        m+=x;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i;j<=n;++j)
        {
            if(a[i]>a[j])
            {
                swap(a[i],a[j]);
                swap(b[i],b[j]);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        c[i]=c[i-1]+b[i];
        if(a[i]<q&&a[i+1]>q)
        {
            s1=i;
            s2=i+1;
        }
        else if(a[i]==q)
        {
            s1=s2=i;
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j][0]=1e9;
            f[i][j][1]=1e9;
        }
    }
    f[s1][s1][0]=0;
    f[s1][s1][1]=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=max(s1-i,1);j<=min(s1,n-i);++j)
        {
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j-1][1]+(a[i+j]-a[i+j-1])*(c[n]-c[i+j-1]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j+1][i+j][0]+(a[j+1]-a[j])*(c[n]-c[i+j]+c[j]));
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j][0]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j][i+j][1]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
        }
    }
    s=min(f[1][n][0],f[1][n][1])+(q-a[s1])*c[n];
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j][0]=1e9;
            f[i][j][1]=1e9;
        }
    }
    f[s2][s2][0]=0;
    f[s2][s2][1]=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=max(s2-i,1);j<=min(s2,n-i);++j)
        {
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j-1][1]+(a[i+j]-a[i+j-1])*(c[n]-c[i+j-1]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j+1][i+j][0]+(a[j+1]-a[j])*(c[n]-c[i+j]+c[j]));
            f[j][i+j][1]=min(f[j][i+j][1],f[j][i+j][0]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
            f[j][i+j][0]=min(f[j][i+j][0],f[j][i+j][1]+(a[i+j]-a[j])*(c[n]-c[i+j]+c[j-1]));
        }
    }
    s=min(s,min(f[1][n][0],f[1][n][1])+(a[s2]-q)*c[n]);
    printf("%d\n",(int)(s*1.0/v)+m);
}
int main()
{
    scanf("%d%d%d",&n,&v,&q);
    while(n!=0||v!=0||q!=0)
    {
        abc();
        scanf("%d%d%d",&n,&v,&q);
    }
    return 0;
}