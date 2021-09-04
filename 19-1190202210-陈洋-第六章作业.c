#include <stdio.h>
#include <stdlib.h>

/*6.27*/
/*
A. 需满足标志位是0x45或0x38，组索引是0x001 , 因此所有会命中的地址为：
   0x08A4 , 0x08A5 , 0x08A6 , 0x08A7
   0x0704 , 0x0705 , 0x0706 , 0x0707
B. 需满足标志位是0x91，组索引是0x110 , 因此所有会命中的地址为：
   0x1238 , 0x1239 , 0x123A , 0x123B
*/
/*6.31*/
/*
A.  12  11  10  9  8  7  6  5  4  3  2  1  0
    CT  CT  CT  CT CT CT CT CT CI CI CI CO CO
B.
      参数
      CO                     0x10
      CI                     0x110
      CT                     0x38
      是否命中               否
      返回的高速缓存字节      -
*/
/*6.35*/
/*
            dst数组
          列0  列1  列2  列3
      行0  m    h    h    h
      行1  m    h    h    h
      行2  m    h    h    h
      行3  m    h    h    h

             src数组
          列0  列1  列2  列3
      行0  m    h    h    h
      行1  m    h    h    h
      行2  m    h    h    h
      行3  m    h    h    h
*/

/*6.39*/
/*
A.16*16*4 = 1024
B.256
  块大小为32字节，因此一个块装2个point_color结构体，整个cache装1/2的square元素,
  由于是按列访问，每次写square[i][j].c时不命中，写square[i][j].m , square[i][j].y , square[i][j].k
  时命中，所以不命中次数 = 1024/4 = 256
C.25%
*/

/*6.43
100%
*/

/*6.45(四星 选做)*/
//用分块的方法
#define x 4   //x为分块大小
void transpose(int *dst, int *src, int dim)
{
    long limit = dim * dim;
    for (int i = 0; i < dim; i += x)
    {
        for (int j = 0; j < dim; j += x)
        {
            for (int k = i; k < i+x&&k<dim; k++)
            {
                for (int t = j; t < j+x&&t<dim; t++)
                {

                    int dst_index = t*dim + k;
                    int src_index = k*dim + t;

                    dst[dst_index] = src[src_index];

                }
            }
        }
    }
}
int main()
{
    //test for 6.45
    int a[6][6] = {1,2,3,4,5,6,
                    1,2,3,4,5,6,
                    1,2,3,4,5,6};
    int b[6][6];
    transpose(b,a,6);
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }

    return 0;
}
