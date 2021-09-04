#include <stdio.h>
#include <stdlib.h>

/*6.27*/
/*
A. �������־λ��0x45��0x38����������0x001 , ������л����еĵ�ַΪ��
   0x08A4 , 0x08A5 , 0x08A6 , 0x08A7
   0x0704 , 0x0705 , 0x0706 , 0x0707
B. �������־λ��0x91����������0x110 , ������л����еĵ�ַΪ��
   0x1238 , 0x1239 , 0x123A , 0x123B
*/
/*6.31*/
/*
A.  12  11  10  9  8  7  6  5  4  3  2  1  0
    CT  CT  CT  CT CT CT CT CT CI CI CI CO CO
B.
      ����
      CO                     0x10
      CI                     0x110
      CT                     0x38
      �Ƿ�����               ��
      ���صĸ��ٻ����ֽ�      -
*/
/*6.35*/
/*
            dst����
          ��0  ��1  ��2  ��3
      ��0  m    h    h    h
      ��1  m    h    h    h
      ��2  m    h    h    h
      ��3  m    h    h    h

             src����
          ��0  ��1  ��2  ��3
      ��0  m    h    h    h
      ��1  m    h    h    h
      ��2  m    h    h    h
      ��3  m    h    h    h
*/

/*6.39*/
/*
A.16*16*4 = 1024
B.256
  ���СΪ32�ֽڣ����һ����װ2��point_color�ṹ�壬����cacheװ1/2��squareԪ��,
  �����ǰ��з��ʣ�ÿ��дsquare[i][j].cʱ�����У�дsquare[i][j].m , square[i][j].y , square[i][j].k
  ʱ���У����Բ����д��� = 1024/4 = 256
C.25%
*/

/*6.43
100%
*/

/*6.45(���� ѡ��)*/
//�÷ֿ�ķ���
#define x 4   //xΪ�ֿ��С
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
