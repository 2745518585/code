#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int m,k,f[N],g1[N],g2[N];
char a[N],b[N];
int KMP()
{
    int m=strlen(a+1),n=strlen(b+1);
    if(k>=n) return max(m-n+1,0);
    for(int i=1;i<=m;++i) g1[i]=g2[i]=0;
    for(int i=1;i<=m/2;++i) swap(a[i],a[m-i+1]);
    for(int i=1;i<=n/2;++i) swap(b[i],b[n-i+1]);
    f[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&b[i]!=b[j+1]) j=f[j];
        if(b[i]==b[j+1]) ++j;
        f[i]=j;
    }
    for(int i=1,j=0;i<=m;++i)
    {
        while(j!=0&&a[i]!=b[j+1]) j=f[j];
        if(a[i]==b[j+1]) ++j;
        g1[i-j+1]=j;
    }
    for(int i=1;i<=m/2;++i) swap(a[i],a[m-i+1]),swap(g1[i],g1[m-i+1]);
    for(int i=1;i<=n/2;++i) swap(b[i],b[n-i+1]);
    f[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&b[i]!=b[j+1]) j=f[j];
        if(b[i]==b[j+1]) ++j;
        f[i]=j;
    }
    for(int i=1,j=0;i<=m;++i)
    {
        while(j!=0&&a[i]!=b[j+1]) j=f[j];
        if(a[i]==b[j+1]) ++j;
        g2[i-j+1]=j;
    }
    int s=0;
    for(int i=1;i<=m-n+1;++i)
    {
        if(g2[i]+g1[i+n-1]+k>=n) ++s;
    }
    return s;
}
int main()
{
	scanf("%d%s%d",&k,a+1,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%s",b+1);
		printf("%d\n",KMP());
	}
	return 0;
}