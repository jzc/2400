/* 
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Team name: Replace with either:
      Your login ID if working as a one person team
      or, ID1+ID2 where ID1 is the login ID of the first team member
      and ID2 is the login ID of the second team member */
    "105604773", 
   /* Student name 1: Replace with the full name of first team member */
   "Justin Cai",
   /* Login ID 1: Replace with the login ID of first team member */
   "105604773",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "",
   /* Login ID 2: Login ID of the second team member */
   ""
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//
// 15 problems, 40 points
// 2 - rating 1
// 5 - rating 2
// 4 - rating 3
// 4 - rating 4
// rating 1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */

//DeMorgan's Law
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */

//unsigned is logical shift
int tmax(void) {
  return ~0U >> 1;
}

// rating 2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */

//0b01010101 four times
int evenBits(void) {
  return (0x55) + (0x55 << 8) + (0x55 << 16) + (0x55 << 24);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */

//Shift the byte you want to the first 8 bits and mask those.
int getByte(int x, int n) {
    return (x >> (n << 3)) & 0xff;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
 
 //Also known as XNOR
 //x y x==y
 //0 0 1
 //0 1 0
 //1 0 0
 //1 1 1
int isEqual(int x, int y) {
  return !(x ^ y);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */

//~0001 = 1110
//~1 = -2
//~0010 = 1101
//~2 = -3
//~1111 = 0000
//~-1 = 0 
// -x = ~x + 1

int negate(int x) {
  return ~x + 1;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

 //Didn't read directions (trying to save operations by adding 0xffffffff to subtract 1)
 //at first so this fact is kinda unrelated 

 //C fact: hex literals are unsigned. If you replaced bias in the return statement
 //with its expression that creates its value, the function will return the wrong value
 //(technically). since the expression is unsigned, it will return an unsigned value.
 //On a bit level, the value is correct, if you then casted to (int), it would return the
 //correct int value.
 
 //bias = 2^n - 1, when x < 0, else 0.
int divpwr2(int x, int n) {
  int bias = (x>>31) & ((1<<n)+(~0));
  return (x + bias) >> n;
}
// rating 3
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  //alternate solution with less signs
  /*
  unsigned ux = x;
  unsigned uy = y;
  int signsDifferent = (ux>>31) ^ (uy>>31);
  int signFlip = ((ux+uy)>>31) ^ (ux>>31);
  return signsDifferent | !signFlip;
  */

  int signsDifferent = ((x>>31) & 1) ^ ((y>>31) & 1);
  int signFlip = (((x+y)>>31) & 1) ^ ((x>>31) & 1);
  return signsDifferent | !signFlip;

  /*return !(!((x+y)>>31) | !(x>>31)) |
          (!(x>>31) & (y>>31)) |
          (!((x+y)>>31) & !(y>>31));*/
}

/*
 * multFiveEights - multiplies by 5/8 rounding toward 0.
 *   Examples: multFiveEights(77) = 48
 *             multFiveEights(-22) = -13
 *   You can assume |x| < (1 << 29)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */

 //5x = (2^2+2^0)x = (2^2)x + x
 //Multiply by 5, divide by 8 (2^3).
 //bias = 2^3-1 = 7
int multFiveEights(int x) {
  int x_times_5 = (x << 2) + x;
  int bias = (x_times_5 >> 31) & 0x7;
  int x_div_8 = (x_times_5 + bias) >> 3;
  return x_div_8;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
 //when x and y have the same signs, compute y-x and if positive, eval true
 //if false "short circuit" the other operations
 //when y positive and x negative, evaluate to true
 //when y negative and x positive, evaluate to false 
int isLessOrEqual(int x, int y) {
  int xSign = (x >> 31) & 1;
  int ySign = (y >> 31) & 1;
  int signsSame = !(xSign ^ ySign);
  int lessOrEqual = !(((y+(~x+1)) >> 31) & 1);
  return (signsSame & lessOrEqual) | ((!signsSame) & (((!ySign) & xSign) | !(ySign & !xSign)));
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */

 //C fact (well at least for this VM and compilation): 1<<32 will produce 0, like expected, but
 //if you have a variable with a value of 32 (e.g. highbit) 1<<highbit where highbit
 //is 32, it will perform 1<<0 (producing 1). if the variable has a value of 1<<33,
 // it will perform 1<<1  (producing 2) and so on.
int bitMask(int highbit, int lowbit) {
  int rightBits = (1<<highbit<<1) + (~0);
  int leftBits = ~((1<<lowbit) + (~0));
  return rightBits & leftBits;
}

// rating 4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */

 //Powers of 2 have only one bit, subtract one and and it with itself
 //to see if it is power of 2. Exceptions are Tmin and 0.
int isPower2(int x) {
  int isNotZero = !!x;
  int isNotTmin = !!((1<<31) ^ x);
  int power2Test = !(x & (x + (~0)));
  return isNotZero & isNotTmin & power2Test;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4 
 */

 //All the bits before the least significant 1 bit will changed when 1 is subtracted
 //from it. XOR this with the original value to get a mask of all the values changed.
 //Shift that mask right one and XOR those together to get the specified value. 
 //In this case, unsigned allows for logical shift and bypasses the corner case of 
 //Tmin. In the case of signed, the corner case would flip to 0.
int leastBitPos(int x) {
  unsigned int bitsChanged = x ^ (x + (~0));
  return x & (bitsChanged ^ (bitsChanged >> 1));
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */

 //bit parity: 
 //even # zero is 0
 //odd # zero is 1
 //example for 1 bit number
 //XOR can calculate the parity of 2 bits 
 //the parity of two subsets is the  parity values xor'd together
 //the reasoning behind this is 
 //even + even = even
 //even + odd = odd
 //odd + odd = even
 //can be done to a whole word by divide and conquer (2 bit subsets->4 bit subsets, etc.
 //think something like merge sort)

int bitParity(int x) {
  int p2 = x ^ (x >> 1); 
  int p4 = p2 ^ (p2 >> 2);
  int p8 = p4 ^ (p4 >> 4);
  int p16 = p8 ^ (p8 >> 8);
  int p32 = p16 ^ (p16 >> 16);
  return p32 & 1;
}
/* 
 * logicalNeg - implement the ! operator, using any of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */

 //Might not be the most efficient solution, but it repeats the same process
 //as in bitParity, except with ORs.
int logicalNeg(int x) {
  int p2 = x | (x >> 1); 
  int p4 = p2 | (p2 >> 2);
  int p8 = p4 | (p4 >> 4);
  int p16 = p8 | (p8 >> 8);
  int p32 = p16 | (p16 >> 16);
  return ~p32 & 1;
}
