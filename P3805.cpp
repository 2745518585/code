#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=20000001;
int n,f[N<<1];
char a[N<<1];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=n;i>=1;--i)
    {
        a[i*2]=a[i];
        a[i*2-1]='#';
    }
    n=n*2+1;
    a[n]='#';
    a[0]='~';
    a[n+1]='@';
    int x=1,s=0;
    for(int i=1;i<=n;++i)
    {
        if(i<x+f[x]) f[i]=min(x+f[x]-i,f[x*2-i]);
        else f[i]=1;
        while(a[i-f[i]]==a[i+f[i]]) ++f[i];
        if(i+f[i]>x+f[x]) x=i;
        s=max(s,f[i]*2-1);
    }
    printf("%d",s/2);
    return 0;
}