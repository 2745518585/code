#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a,b,c;
int check(int a,int b,int c)
{
    int s=min(b,c);
    a+=s*2,b-=s,c-=s;
    if(b==0) swap(b,c);
    if(b%3!=0) return 1e9;
    return s+b;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&a,&b,&c);
        int s=min(min(check(a,b,c),check(b,a,c)),check(c,a,b));
        printf("%d\n",s==1e9?-1:s);
    }
    return 0;
}