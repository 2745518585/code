#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
char a[N];
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    int x1=0,x2=0;
    while(a[x1+1]=='>') ++x1;
    while(a[n-x2]=='<') ++x2;
    ll s=(ll)x1*(x1+1)/2+(ll)x2*(x2+1)/2;
    int s1=0,s2=0;
    for(int i=x1+1;i<=n-x2;++i)
    {
        if(a[i]=='<') ++s1;
        else ++s2;
        if(a[i]=='>'&&a[i+1]!='>')
        {
            s+=(ll)min(s1,s2)*(min(s1,s2)-1)/2;
            s+=(ll)max(s1,s2)*(max(s1,s2)+1)/2;
            s1=s2=0;
        }
    }
    printf("%lld",s);
    return 0;
}