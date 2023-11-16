#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001,M=11;
int n,a[N],g[N][M+1],h[N];
ll f[N][2],t[N];
bool b[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=n;++i)
    {
        if(b[i]==true) continue;
        for(int j=2;i*j<=n;++j) b[i*j]=true,g[i*j][++h[i*j]]=i;
    }
    ll s=0;
    for(int i=2;i<=n;++i)
    {
        ll w=(1<<h[i])-1;
        for(int j=0;j<=w;++j)
        {
            t[j]=1;
            for(int k=1;k<=h[i];++k) if(j&(1<<(k-1))) t[j]*=g[i][k];
        }
        for(int j=1;j<=w;++j)
        {
            f[i][0]=max(f[i][0],max(max(f[t[j]][0]+f[t[w^j]][0],f[t[j]][0]+f[t[w^j]][1]),max(f[t[j]][1]+f[t[w^j]][0],f[t[j]][1]+f[t[w^j]][1])));
			f[i][1]=max(f[i][1],f[t[j]][0]+f[t[w^j]][0]);
        }
		f[i][1]+=a[i];
		if(b[i]==true) s=max(s,max(f[i][0],f[i][1])+max(a[1],0));
		else s=max(max(s,(ll)a[1]),max(f[i][0],f[i][1]));
		for(int j=i*2;j<=n;j+=i)
        {
			f[j][0]=max(f[j][0],max(f[i][0],f[i][1]));
			f[j][1]=max(f[j][1],f[i][0]);
		}
    }
    printf("%lld",s);
    return 0;
}