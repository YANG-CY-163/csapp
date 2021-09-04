#include <stdio.h>
#include <stdlib.h>

/*2.59*/
int xy(int x,int y){
    return (0xFF & x) | (~0xFF & y);

}

/*2.63*/
unsigned srl(unsigned x,int k){
    /*Perform shift arithmetically*/
    unsigned xsra = (int)x>>k;
    int w = sizeof(int)<<3;

    //a的高k位是连续的0.低位是连续的1
    int a = (2<<(w-k-1))-1;

    return xsra & a;

}
int sra(int x,int k)
{
    /*Perform shift logically*/
    int xsrl = (unsigned)x>>k;
    int w = sizeof(int)<<3;
    //获取xsrl的符号位是否为1,若是1,则s的位级表示中与xsrl符号位对应的那一位也是1，否则全是0
    int s = (1<<(w-k-1)) & xsrl;

    //若xsrl符号位是1，则~(s-1)的符号位及更高位全为1，否则~(s-1)全为0
    return ~(s-1)|xsrl;
}

/*2.65  (选做）*/
int odd_ones(unsigned x)
{
    //将x右移一位后再与自己异或，相当于1，2位异或，2，3位异或，以此类推
    x = (x>>1)^x;
    //此时x的第2位存着原来1，2位异或的结果，第3位存着2，3位异或的结果，第4位存着3，4位异或的结果，以此类推，
    //因此将x右移两位后再异或，相当于将1，2位异或的结果再与3，4位异或的结果进行异或，得到1，2，3，4位异或的结果，以此类推
    x = (x>>2)^x;
    //同理，得到没8个相邻位异或的结果
    x = (x>>4)^x;
    //得到每16个相邻位异或的结果
    x = (x>>8)^x;
    //最后得到32位依次异或的结果
    x = (x>>16)^x;
    //x的最低位存着异或结果，结果为1则含1的个数为奇数个，否则是偶数个
    return x&1;
}

/*2.67*/
/*A.位移量的大小超过了int的位数,这是未定义的
*/
/*B*/
int int_size_is_32()
{
    int set_msb = 1<<31;
    int beyond_msb = set_msb<<1;
    return set_msb && !beyond_msb;
}
/*C*/
int int_size_is_32_2()
{
    int set_msb = 1<<15;
    set_msb = set_msb<<15;
    set_msb = set_msb<<1;
    int beyond_msb = set_msb<<1;

    return set_msb && !beyond_msb;

}

/*2.71*/
/*A.原来的代码错在把指定字节前的位全部清零了,没有考虑到符号位是1时扩展后指定字节前应该全为1,
    因此得到的是unsigned，不是正确的符号扩展后的结果
*/
/*B*/
typedef unsigned packed_t;
int xbyte(packed_t word,int bytenum)
{
    int left = (3-bytenum)<<3;
    //先左移清除掉不需要的字节
    word = word<<left;
    //算术右移，清除掉不需要的字节同时符号扩展
    return (int)word >>24;
}

/*2.75 (选做)*/
int signed_high_prod(int x,int y)
{
    return (int)(((unsigned)((x*y)<<26))>>29);
}
unsigned unsigned_high_prod(unsigned x,unsigned y)
{

    int w = sizeof(int)<<3;
    //调用库函数，获取补码形式下x*y的高w位
    int signed_highprod = signed_high_prod((int)x,(int)y);
    //分别获取x和y的最高位
    int x_w = (int)x>>(w-1);
    int y_w = (int)y>>(w-1);
    //根据书上公式2.18化简得到关系式
    unsigned un_highprod = (unsigned)(signed_highprod + (x_w&(int)y) + (y_w&(int)x)) ;
    return un_highprod;
}


/*2.79 (选做)*/
int mul3div4(int x)
{
    int w = sizeof(int)<<3;
    int s = x>>(w-1);//若x符号位是1则s的位级表示全为1，否则全为0
    x = (x<<1)+ x;//计算x*3

    int bias = (1<<2)-1;//计算偏置量
    return (x+(s & bias))>>2;//若x是负数则加上偏置量后再右移，实现向上舍入，否则不加偏置量实现向下舍入
}

/*2.83
A.  Y/(2^k-1)
B.  (a) 5/7     (b) 2/5     (c) 19/63
*/

/*2.87

描述                      Hex         M               E       V            D
-0                        8000        0               -14     -0           -0.0
最小的大于2的值           4001        1025/1024       1       1025*(2^-9)  2.001953
512                       6000        1               9       512          512.0
最大的非规格化数          03ff        1023/1024       -14     1023*(2^-24) 0.000061
负无穷                    fc00        -               -       负无穷       负无穷
十六进制表示为3BB0的数    3BB0        123/64          -1      123*(2^-7)   0.960938

*/

int main()
{
    printf("%x\n",xy(0x89ABCDEF,0x76543210));
    unsigned x1 = srl(0x87799000,8);
    int x2 = sra(0x80000000,31);
    printf("逻辑位移=%x  算数位移=%x\n",x1,x2);
    printf("is_odd:%d\n",odd_ones(0x88888886));
    printf("int_32:%d %d\n",int_size_is_32(),int_size_is_32_2());

    printf("xbyte: %x\n",xbyte(0x8778,1));

    printf("x*y %x\n",unsigned_high_prod(-2,-2));
    printf("mul=%d\n",mul3div4(-17));




}
