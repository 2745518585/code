#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001,M=31;
int n,b[M][M],c[M][M],d[M],s;
char a[N];
int main()
{
    scanf("%d%s",&n,a+1);
    for(int i=0;i<=25;++i)
    {
        for(int j=0;j<=25;++j) b[i][j]=1e9;
    }
    for(int i=1;i<=n;++i)
    {
        ++d[a[i]-'a'];
        for(int j=0;j<=25;++j) b[j][a[i]-'a']=c[j][a[i]-'a'];
        for(int j=0;j<=25;++j) s=max(s,(d[a[i]-'a']-d[j])-b[a[i]-'a'][j]);
        for(int j=0;j<=25;++j) s=max(s,(d[j]-d[a[i]-'a'])-b[j][a[i]-'a']);
        for(int j=0;j<=25;++j) c[j][a[i]-'a']=min(c[j][a[i]-'a'],d[j]-d[a[i]-'a']);
    }
    printf("%d",s);
    return 0;
}