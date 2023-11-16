#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001;
int n;
char a[N];
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        int t=1,s=0;
        for(int i=1;i<=n*2;++i) h[i]=false;
        h[1]=true;
        for(int i=1;i<=n*2;++i)
        {
            if(a[i]=='(')
            {
                ++t;
                h[t]=true;
            }
            else
            {
                --t;
                if(h[t]==true) ++s;
                h[t]=false;
            }
        }
        printf("%d\n",s);
    }
    return 0;
}