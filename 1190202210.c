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

    //a�ĸ�kλ��������0.��λ��������1
    int a = (2<<(w-k-1))-1;

    return xsra & a;

}
int sra(int x,int k)
{
    /*Perform shift logically*/
    int xsrl = (unsigned)x>>k;
    int w = sizeof(int)<<3;
    //��ȡxsrl�ķ���λ�Ƿ�Ϊ1,����1,��s��λ����ʾ����xsrl����λ��Ӧ����һλҲ��1������ȫ��0
    int s = (1<<(w-k-1)) & xsrl;

    //��xsrl����λ��1����~(s-1)�ķ���λ������λȫΪ1������~(s-1)ȫΪ0
    return ~(s-1)|xsrl;
}

/*2.65  (ѡ����*/
int odd_ones(unsigned x)
{
    //��x����һλ�������Լ�����൱��1��2λ���2��3λ����Դ�����
    x = (x>>1)^x;
    //��ʱx�ĵ�2λ����ԭ��1��2λ���Ľ������3λ����2��3λ���Ľ������4λ����3��4λ���Ľ�����Դ����ƣ�
    //��˽�x������λ��������൱�ڽ�1��2λ���Ľ������3��4λ���Ľ��������򣬵õ�1��2��3��4λ���Ľ�����Դ�����
    x = (x>>2)^x;
    //ͬ���õ�û8������λ���Ľ��
    x = (x>>4)^x;
    //�õ�ÿ16������λ���Ľ��
    x = (x>>8)^x;
    //���õ�32λ�������Ľ��
    x = (x>>16)^x;
    //x�����λ��������������Ϊ1��1�ĸ���Ϊ��������������ż����
    return x&1;
}

/*2.67*/
/*A.λ�����Ĵ�С������int��λ��,����δ�����
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
/*A.ԭ���Ĵ�����ڰ�ָ���ֽ�ǰ��λȫ��������,û�п��ǵ�����λ��1ʱ��չ��ָ���ֽ�ǰӦ��ȫΪ1,
    ��˵õ�����unsigned��������ȷ�ķ�����չ��Ľ��
*/
/*B*/
typedef unsigned packed_t;
int xbyte(packed_t word,int bytenum)
{
    int left = (3-bytenum)<<3;
    //���������������Ҫ���ֽ�
    word = word<<left;
    //�������ƣ����������Ҫ���ֽ�ͬʱ������չ
    return (int)word >>24;
}

/*2.75 (ѡ��)*/
int signed_high_prod(int x,int y)
{
    return (int)(((unsigned)((x*y)<<26))>>29);
}
unsigned unsigned_high_prod(unsigned x,unsigned y)
{

    int w = sizeof(int)<<3;
    //���ÿ⺯������ȡ������ʽ��x*y�ĸ�wλ
    int signed_highprod = signed_high_prod((int)x,(int)y);
    //�ֱ��ȡx��y�����λ
    int x_w = (int)x>>(w-1);
    int y_w = (int)y>>(w-1);
    //�������Ϲ�ʽ2.18����õ���ϵʽ
    unsigned un_highprod = (unsigned)(signed_highprod + (x_w&(int)y) + (y_w&(int)x)) ;
    return un_highprod;
}


/*2.79 (ѡ��)*/
int mul3div4(int x)
{
    int w = sizeof(int)<<3;
    int s = x>>(w-1);//��x����λ��1��s��λ����ʾȫΪ1������ȫΪ0
    x = (x<<1)+ x;//����x*3

    int bias = (1<<2)-1;//����ƫ����
    return (x+(s & bias))>>2;//��x�Ǹ��������ƫ�����������ƣ�ʵ���������룬���򲻼�ƫ����ʵ����������
}

/*2.83
A.  Y/(2^k-1)
B.  (a) 5/7     (b) 2/5     (c) 19/63
*/

/*2.87

����                      Hex         M               E       V            D
-0                        8000        0               -14     -0           -0.0
��С�Ĵ���2��ֵ           4001        1025/1024       1       1025*(2^-9)  2.001953
512                       6000        1               9       512          512.0
���ķǹ����          03ff        1023/1024       -14     1023*(2^-24) 0.000061
������                    fc00        -               -       ������       ������
ʮ�����Ʊ�ʾΪ3BB0����    3BB0        123/64          -1      123*(2^-7)   0.960938

*/

int main()
{
    printf("%x\n",xy(0x89ABCDEF,0x76543210));
    unsigned x1 = srl(0x87799000,8);
    int x2 = sra(0x80000000,31);
    printf("�߼�λ��=%x  ����λ��=%x\n",x1,x2);
    printf("is_odd:%d\n",odd_ones(0x88888886));
    printf("int_32:%d %d\n",int_size_is_32(),int_size_is_32_2());

    printf("xbyte: %x\n",xbyte(0x8778,1));

    printf("x*y %x\n",unsigned_high_prod(-2,-2));
    printf("mul=%d\n",mul3div4(-17));




}
