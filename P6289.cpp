#include<bits/stdc++.h>
using namespace std;
const int N=17,M=30,K=1000001;
int n,a[N][M],b[N],f[1<<N];
char c[K];
int sum(int x)
{
    int s=0;
    for(int i=0;i<=25;++i)
    {
        int w=1e9;
        for(int j=1;j<=n;++j)
        {
            if((x&(1<<(j-1)))!=0) w=min(w,a[j][i]);
        }
        s+=w;
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",c+1);
        b[i]=strlen(c+1);
        for(int j=1;j<=b[i];++j)
        {
            ++a[i][c[j]-'a'];
        }
    }
    for(int i=0;i<=(1<<n)-1;++i) f[i]=1e9;
    f[0]=0;
    for(int i=1;i<=n;++i)
    {
        f[1<<(i-1)]=b[i];
    }
    for(int i=1;i<=(1<<n)-1;++i)
    {
        int z=sum(i);
        for(int j=i&(i-1);j!=0;j=((j-1)&i))
        {
            if(f[i^j]+f[j]-z<f[i])
            {
                f[i]=f[i^j]+f[j]-z;
            }
        }
    }
    printf("%d",f[(1<<n)-1]+1);
    return 0;
}