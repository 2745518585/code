#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=8,M=501,d[100]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,443,449,457,461,463,467,479,487,491,499,1000000000};
int n,g[M],h[M],a[M];
ll s=0,f[1<<N][1<<N],f1[1<<N][1<<N],f2[1<<N][1<<N],p;
bool cmp(int a,int b)
{
    if(g[a]!=g[b]) return g[a]<g[b];
    return a<b;
}
int main()
{
    scanf("%d%lld",&n,&p);
    for(int i=2;i<=n;++i) a[i]=i;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=8;++j)
        {
            if(i%d[j]==0) h[i]|=(1<<(j-1));
        }
        g[i]=1;
        for(int j=9;d[j]<=n;++j)
        {
            if(i%d[j]==0)
            {
                g[i]=j;
                break;
            }
        }
    }
    sort(a+2,a+n+1,cmp);
    f[0][0]=f1[0][0]=f2[0][0]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=255;j>=0;--j)
        {
            for(int k=255;k>=0;--k)
            {
                if((j&k)!=0) continue;
                if((j&h[a[i]])==0) f1[j][k|h[a[i]]]=(f1[j][k|h[a[i]]]+f1[j][k])%p;
                if((k&h[a[i]])==0) f2[j|h[a[i]]][k]=(f2[j|h[a[i]]][k]+f2[j][k])%p;
            }
        }
        if(g[a[i]]!=g[a[i+1]]||g[a[i]]==1)
        {
            for(int j=0;j<=255;++j)
            {
                for(int k=0;k<=255;++k)
                {
                    if((j&k)!=0) continue;
                    f[j][k]=((f1[j][k]+f2[j][k]-f[j][k])%p+p)%p;
                    f1[j][k]=f2[j][k]=f[j][k];
                }
            }
        }
    }
    ll s=0;
    for(int i=0;i<=255;++i)
    {
        for(int j=0;j<=255;++j)
        {
            s=(s+f[i][j])%p;
        }
    }
    printf("%lld",s);
    return 0;
}