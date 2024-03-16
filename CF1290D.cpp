#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,k;
bool h[N];
int query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    char c;
    scanf("%s",&c);
    return c=='Y';
}
void reset()
{
    printf("R\n");
    fflush(stdout);
}
void add(int x)
{
    for(int i=(x-1)*k+1;i<=x*k;++i)
    {
        if(query(i)) h[i]=true;
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    k=(k+1)/2;
    n/=k;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i&&i+j<=n;++j)
        {
            for(int l=j;l<=n;l+=i) add(l);
            reset();
        }
    }
    int s=0;
    for(int i=1;i<=n*k;++i) s+=!h[i];
    printf("! %d\n",s);
    fflush(stdout);
    return 0;
}