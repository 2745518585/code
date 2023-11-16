#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001,P=1e9+7;
int m,n,f[N];
char a[N],b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s%s",b+1,a+1);
        m=strlen(a+1),n=strlen(b+1);
        ll t=0,k=1;
        for(int i=1;i<=n;++i) k=k*131%P;
        for(int i=1;i<=n;++i) t=(t*131+b[i])%P;
        ll w=0;
        int s=0;
        for(int i=1;i<=m;++i)
        {
            w=(w*131+a[i])%P;
            if(w>n) w=((w-a[i-n]*k)%P+P)%P;
            if(w==t) ++s;
        }
        printf("%d\n",s);
    }
    return 0;
}