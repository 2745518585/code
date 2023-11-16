#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
double s,w,p[128][128];
char a[1001];
void init()
{
    p[0]['H']=1;
    p[0]['C']=12;
    p[0]['N']=14;
    p[0]['O']=16;
    p[0]['F']=19;
    p['N']['a']=23;
    p['M']['g']=24;
    p['A']['l']=27;
    p['S']['i']=28;
    p[0]['P']=31;
    p[0]['S']=32;
    p['C']['l']=35.5;
    p[0]['K']=39;
    p['C']['a']=40;
    p['M']['n']=55;
    p['F']['e']=56;
    p['C']['u']=64;
    p['Z']['n']=65;
    p['A']['g']=108;
    p[0]['I']=127;
    p['B']['a']=137;
    p['H']['f']=178.5;
    p['P']['t']=195;
    p['A']['u']=197;
    p['H']['g']=201;
}
int read(int x)
{
    int k=0;
    while(a[x]>='0'&&a[x]<='9')
    {
        k=k*10+a[x++]-'0';
    }
    return k;
}
int main()
{
    init();
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        if(a[i]>='A'&&a[i]<='Z')
        {
            if(a[i+1]>='a'&&a[i+1]<='z')
            {
                if(a[i+2]=='_')
                {
                    w+=p[a[i]][a[i+1]]*read(i+4);
                    while(a[i]!='}') ++i;
                }
                else
                {
                    w+=p[a[i]][a[i+1]];
                    ++i;
                }
            }
            else
            {
                if(a[i+1]=='_')
                {
                    w+=p[0][a[i]]*read(i+3);
                    while(a[i]!='}') ++i;
                }
                else
                {
                    w+=p[0][a[i]];
                }
            }
        }
        else if(a[i]=='~')
        {
            if(a[i+1]>='0'&&a[i+1]<='9')
            {
                s+=18*read(i+1);
            }
            else s+=18;
            cout<<s+w;
            return 0;
        }
        else if(a[i]=='(')
        {
            s+=w;
            w=0;
        }
        else if(a[i]==')')
        {
            if(a[i+1]=='_')
            {
                s+=w*read(i+3);
                while(a[i]!='}') ++i;
            }
            else s+=w;
            w=0;
        }
    }
    cout<<s+w;
    return 0;
}