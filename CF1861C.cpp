#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n;
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        int w1=0,w2=1e9,t=0;
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i]=='+') ++t;
            else if(a[i]=='-')
            {
                --t;
                if(t<w1) w1=t;
                if(t<w2) w2=1e9;
            }
            else if(a[i]=='1')
            {
                w1=t;
            }
            else if(a[i]=='0')
            {
                if(w2>t) w2=t;
            }
            if(t==1) w1=1;
            if(w1>=w2)
            {
                u=false;
                break;
            }
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}