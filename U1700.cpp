#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int m;
bool h[N];
struct str
{
    int x,y,k;
}a[N];
bool cmp(str a,str b)
{
    if(a.y!=b.y) return a.y<b.y;
    return a.x<b.x;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].k);
    }
    sort(a+1,a+m+1,cmp);
    int s=0;
    for(int i=1;i<=m;++i)
    {
        int w=0;
        for(int j=a[i].x;j<=a[i].y;++j) w+=h[j];
        if(w>=a[i].k) continue;
        for(int j=a[i].y;j>=a[i].x;--j)
        {
            if(h[j]==false)
            {
                h[j]=true;
                ++s;
                ++w;
            }
            if(w>=a[i].k) break;
        }
    }
    printf("%d",s);
    return 0;
}