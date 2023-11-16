#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(i>=2&&a[i]==a[i-1]&&a[i]==a[i-2]) --n,--i;
    }
    int s=0,x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==a[i+1])
        {
            ++s;
            if(a[i]==a[x])
            {
                bool u=false;
                for(int j=x+2;j<=i-1;++j)
                {
                    if(a[j-1]!=a[j+1]&&a[j]!=a[x])
                    {
                        u=true;
                        break;
                    }
                }
                s+=u;
            }
            else ++s;
            x=i;
            ++i;
        }
        else ++s;
    }
    printf("%d",s);
    return 0;
}