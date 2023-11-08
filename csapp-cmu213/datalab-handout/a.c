#include <stdio.h>

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
// 求 2*f
/*
 * */
//unsigned floatScale2(unsigned uf) {
////    printf("uf : %d ", uf);
////    unsigned sign = (uf & 0x80000000) >> 31;
//    unsigned exponential = (uf & 0x7f800000) >> 23;
////    printf("   uf & 0x7f800000: %d  ", uf & 0x7f800000);
////    printf(" exponential: %d",  exponential);
//    if (exponential == 0) {
//        return uf; // 1 | 0
//    }
//    if (exponential == 255) {
//        return uf;
//    }
//    exponential++;
//
//    return exponential<<23 | (uf&0x807fffff);
//}

unsigned floatScale2(unsigned uf) {
    int exp = (uf&0x7f800000)>>23;
    int sign = uf&(1<<31);
    if(exp==0) return uf<<1|sign;
    if(exp==255) return uf;
    exp++;
    if(exp==255) return 0x7f800000|sign;
    return (exp<<23)|(uf&0x807fffff);
}
int main() {
    unsigned a;
    /*
    符号位：0（表示正数）
     // 127 - 127 = 0
    指数位：01111111（表示指数偏移为0，即指数为-127）
    尾数位：00000000000000000000000（表示尾数为0）
    */
//    a = floatScale2(0); //0x80000000
//    printf("\n 0 -- %u  \n", a);
    a = floatScale2(1);
    printf("\n 2 -- %u  \n", a);
//    a = floatScale2(5); //0x80000000
//    printf("\n 10 -- %u  \n", a);
}
