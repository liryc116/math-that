#include "my_math.h"
#include <stddef.h>

double my_exp(double x)
{
    double num = x;
    double denum = 1;
    double n = 1;
    double res = 1;

    while(num>denum*0.0001)
    {
        res += num/denum;
        n+=1;
        denum *=n;
        num*=x;
    }

    return res;
}

double my_log(double x)
{
    x-=1;
    double res = x;
    double num = x;
    double denum = 1;

    while(num>denum*0.0001)
    {
        num*=x;
        denum+=1;
        res += num/denum;
    }

    return res;
}

double my_dpow(double x, double y)
{
    if(y==0)
        return 1;

    while(y>1)
    {
        if(y>1)
        {
            y/=2;
            x*=x;
        }
        else if(y!=1)
        {
            x = my_exp(my_log(x)*y);
            y = 1;
        }
    }

    return x;
}

double my_pow(double x, double y)
{
    long exp = (long) y;

    if(y==0)
        return 1;

    double result = 1;
    while(exp!=0)
    {
        if(exp%2==0)
        {
            exp/=2;
            x*=x;
        }
        else
        {
            result *= x;
            exp-=1;
        }
    }

    return result;
}
