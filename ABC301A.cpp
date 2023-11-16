#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n;
char a[N];
int main()
{
    scanf("%d%s",&n,a+1);
    int s1=0,s2=0,x1=0,x2=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='A') ++s1,x1=i;
        else ++s2,x2=i;
    }
    if(s1>s2||(s1==s2&&x1<x2)) printf("A");
    else printf("T");
    return 0;
}