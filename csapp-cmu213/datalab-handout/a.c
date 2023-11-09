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
// 1000 0000 0000 0000 0000 0000 0000 0000
unsigned floatScale2(unsigned uf) {
    unsigned sign = (uf & 0x80000000) >> 31;
    unsigned exponential = (uf & 0x7f800000) >> 23;

//    printf("sign: %d %d -", sign, uf & 0x80000000);

    if (exponential == 0) {
//        printf("exponential: %d  ", (uf&0x7fffffff)<<1|(uf & 0x80000000));
        return (uf&0x7fffffff)<<1|(uf & 0x80000000); // ??
    }
    if (exponential == 255) {
        return uf;
    }
    exponential++;

    return exponential<<23 | (uf&0x807fffff);
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
// 0x8 00000
//   1 000   20
int floatFloat2Int(unsigned uf) {
    int Tmax = 1<<31;
    int sign = (uf & 0x80000000) >> 31; // 第一位
    int exponential = ((uf & 0x7f800000) >> 23) - 127;
    if (exponential > 31) {
        return Tmax;
    }
    if (exponential < 0) {
        return 0;
    }
// 0000 0000 0111 1111 1111 1111 1111 1111
// 0000 0000 1000 0000 0000 0000 0000 0000
    // 补充上小数点前的 1
    int fraction = (uf & 0x007fffff) | 0x00800000;

    int ans;
    // 小数 -》整数 >> 23
    if (exponential > 23) {
        // x 2
        ans = fraction << (exponential - 23);
    } else {
        // x 0.5
        ans = fraction >> (23 - exponential);
    }

    if (sign == 1) {
        ans = ~ans+1;
    }
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 *
 */
// 0011 1111 1000 0000 0000 0000 0000 0000

unsigned floatPower2(int x) {
    int exponential = x;
    if (exponential > 127) {
        // +INF.
        return  0x7f800000;
    }
    int f_e = exponential + 127;
    if (exponential < 0) {
        return 0;
    }
    return f_e << 23;
}

int main() {
    unsigned a;
    /*
    符号位：0（表示正数）
     // 127 - 127 = 0
    指数位：01111111（表示指数偏移为0，即指数为-127）
    尾数位：00000000000000000000000（表示尾数为0）
    */
    a = floatPower2(0); //
    printf(" 1065353216  %d  \n", a); //0x3f800000
    a = floatPower2(-2147483648);
    printf(" 0  %d  \n", a); //0
    a = floatPower2(8388608); // 0x800000
    printf(" 2139095040[0x7f800000]  %d  \n", a); //0
}
