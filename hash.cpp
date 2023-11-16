#include<bits/stdc++.h>
using namespace std;
const int N=1001,P=1000000;
int n,s;
char a[N];
int main()
{
    scanf("%s",a);
    n=strlen(a);
    for(int i=0;i<=n-1;++i)
    {
        int w=0;
        for(int j=i;j<=n-1;++j)
        {
            w=(w+a[j])%P;
            s=(s+w*(j-i+1)%P)%P;
        }
    }
    printf("%.6d",(s%P+P)%P);
    return 0;
}