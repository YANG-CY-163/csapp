#include <stdio.h>
#include <stdlib.h>

/*
9.11
A.
    13  12  11 10  9  8  7  6  5  4  3  2  1  0
     0   0   0  0  1  0  0  1  1  1  1  1  0  0
B.
    参数                值
    VPN                 0x09
    TLB索引             0x01
    TLB标记             0x02
    TLB命中？           否
    缺页？              否
    PPN                 0x17
C.
     11 10  9  8  7  6  5  4  3  2  1  0
     0   1  0  1  1  1  1  1  1  1  0  0
D.
    参数                值
    字节偏移            0x00
    缓存索引            0x0f
    缓存标记            0x17
    缓存命中？          否
    返回的缓存字节      -

9.13
A.
    13  12  11 10  9  8  7  6  5  4  3  2  1  0
     0   0   0  0  1  0  0  1  0  0  0  0  0  0
B.
    参数                值
    VPN                 0x01
    TLB索引             0x01
    TLB标记             0x00
    TLB命中？           否
    缺页？              是
    PPN                 -

9.15
    请求               块大小（十进制字节）            快头部（十六进制）
    malloc(3)          8                               0x09
    malloc(11)         16                              0x11
    malloc(20)         24                              0x19
    malloc(21)         32                              0x21

9.19
1) a
2) d
3) b
*/
int main()
{
    printf("Hello world!\n");
    return 0;
}
