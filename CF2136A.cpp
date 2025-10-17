#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
bool check(int x,int y)
{
    if(max(x,y)>min(x,y)*2+2) return false;
    return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        c-=a,d-=b;
        if(check(a,b)&&check(c,d)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}