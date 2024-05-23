#include<cstdio>
#include<algorithm>
using namespace std;
int a[100000001];
int main()
{
    for(int i=1;i<=1e8;++i)
    {
        for(int j=1;i*j<=1e8;++j) ++a[i*j];
    }
    int s=0;
    for(int i=1;i<=1e8;++i) s=max(s,a[i]);
    printf("%d",s);
    return 0;
}