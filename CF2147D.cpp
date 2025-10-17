#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,a[N],b[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        ll s1=0,s2=0;
        q=0;
        for(int i=1;i<=n;++i)
        {
            int j=i;
            while(j+1<=n&&a[j+1]==a[i]) ++j;
            s1+=(ll)(j-i+1)*(a[i]/2);
            s2+=(ll)(j-i+1)*(a[i]/2);
            if(a[i]%2==0)
            {
                i=j;
                continue;
            }
            b[++q]=j-i+1;
            i=j;
        }
        sort(b+1,b+q+1,[](int x,int y){return x>y;});
        for(int i=1;i<=q;++i)
        {
            if(i%2==1) s1+=b[i];
            else s2+=b[i];
        }
        printf("%lld %lld\n",s1,s2);
    }
    return 0;
}