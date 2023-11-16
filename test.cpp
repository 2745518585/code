#include<cstdio>
int f[2][2][2];
void abc(int f[][2][2])
{
    f[0][0][0]=1;
}
int main()
{
    abc(f);
    printf("%d\n",f[0][0][0]);
    return 0;
}