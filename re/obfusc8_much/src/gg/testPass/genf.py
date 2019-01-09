
def genf(a,b,c,i):
    x = """ // %c-%c-%c
    if(flag[%d]*flag[%d]*flag[%d] - (flag[%d]*flag[%d])*(%d) + flag[%d]*(%d) - %d !=0 || flag[%d]*flag[%d]*flag[%d] - (flag[%d]*flag[%d])*(%d) + flag[%d]*(%d) - %d !=0 || flag[%d]*flag[%d]*flag[%d] - (flag[%d]*flag[%d])*(%d) + flag[%d]*(%d) - %d != 0)
        {
            // printf("%c:%c:%c\\n");
            fin |= 1;
        }
    else
        fin ^= 0;
    """ % (chr(a),chr(b),chr(c),i,i,i,i,i,a+b+c,i,a*b+b*c+c*a,a*b*c,i+2,i+2,i+2,i+2,i+2,a+b+c,i+2,a*b+b*c+c*a,a*b*c,i+1,i+1,i+1,i+1,i+1,a+b+c,i+1,a*b+b*c+c*a,a*b*c,chr(a),chr(b),chr(c))

    print x

flag = raw_input().strip()

print '''#include <stdio.h>
#include<strings.h>'''
print '''int main(int argc, char **argv)
{
    int fin = 0;
    char flag[%d] ;//%s;
    bzero(flag, %d); 
    scanf("%%s", flag);
''' % (len(flag), flag,len(flag))
for i in xrange(0, len(flag) - 2):
    genf(ord(flag[i]),ord(flag[i+1]),ord(flag[i+2]),i)

print '''   printf("%d",fin==0);
    return 0;
}'''
