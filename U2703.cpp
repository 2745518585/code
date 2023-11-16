#include<bits/stdc++.h>
using namespace std;
const int N=10001;
int n,l[N];
char a[N][N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d\n",&n);
        for(int i=1;i<=n;++i)
        {
            l[i]=0;
            gets(a[i]+1);
            for(int j=1;j<=n;++j)
            {
                if(a[i][j]=='1') ++l[i];
            }
        }
        int w=0;
        for(int i=1;i<=n;++i) w=max(w,l[i]);
        if(n==1) printf("0\n");
        else if(w==n-1) printf("1\n");
        else printf("2\n");
    }
    return 0;
}