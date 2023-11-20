#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=30000001;
int n,f[N];
char a[N];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=n;i>=1;--i)
    {
        a[i*2]=a[i];
        a[i*2-1]='#';
    }
    a[n*2+1]='#';
    a[0]='~';
    a[n*2+2]='@';
    n=n*2+1;
    int x=1,s=0;
    for(int i=1;i<=n;++i)
    {
        if(i<=x+f[x]-1) f[i]=min(f[x*2-i],x+f[x]-i);
        while(a[i+f[i]]==a[i-f[i]]) ++f[i];
        if(i+f[i]>x+f[x]) x=i;
        s=max(s,f[i]);
    }
    printf("%d",s-1);
    return 0;
}