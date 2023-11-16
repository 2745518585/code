#include<bits/stdc++.h>
using namespace std;
const int N=10000001;
int n;
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    return a.b<b.b;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].a,&a[i].b);
    }
    sort(a+1,a+n+1,cmp);
    int s=0,x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i].a>=x)
        {
            ++s;
            x=a[i].b;
        }
    }
    printf("%d",s);
    return 0;
}