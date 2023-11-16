#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int s1=0,s2=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(a[i]==i) ++s1;
            if(a[i]==n-i+1) ++s2;
        }
        if(s1>=n-s1) printf("First\n");
        else if(s2>n-s2) printf("Second\n");
        else printf("Tie\n");
    }
    return 0;
}