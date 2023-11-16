#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n,h1[N],h2[N];
char a[N],b[N];
int main()
{
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1);
    int s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='@') ++s1;
        else ++h1[a[i]];
        if(b[i]=='@') ++s2;
        else ++h2[b[i]];
    }
    for(int i='a';i<='z';++i)
    {
        if(i=='a'||i=='t'||i=='c'||i=='o'||i=='d'||i=='e'||i=='r')
        {
            if(h1[i]<h2[i]) s1-=h2[i]-h1[i];
            if(h1[i]>h2[i]) s2-=h1[i]-h2[i];
        }
        else
        {
            if(h1[i]!=h2[i])
            {
                printf("No");
                return 0;
            }
        }
    }
    if(s1<0||s2<0) printf("No");
    else printf("Yes");
    return 0;
}