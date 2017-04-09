/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
    "Justin Cai",     /* First member full name */
    "justin.cai@colorado.edu"  /* First member email address */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/
 
/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX(dim-1-j, i, dim)].red   = src[RIDX(i, j, dim)].red;
            dst[RIDX(dim-1-j, i, dim)].green = src[RIDX(i, j, dim)].green;
            dst[RIDX(dim-1-j, i, dim)].blue  = src[RIDX(i, j, dim)].blue;
        }
    }
}

char rotate_1_descr[] = "rotate_1: direct copy";
void rotate_1(int dim, pixel* src, pixel* dst)
{
    int i, j, sc, dc;
    sc = 0;
    for(i = 0; i < dim; ++i)
    {
        // #define RIDX(i,j,n) ((i)*(n)+(j))
        dc = RIDX(dim-1, i, dim);
        for(j = 0; j < dim; ++j)
        {
            dst[dc] = src[sc];
            dc -= dim;
            ++sc;
        }
    }
}

char rotate_2_descr[] = "rotate_2: unroll x2";
void rotate_2(int dim, pixel* src, pixel* dst)
{
    int i, j, sc, dc;
    sc = 0;
    for(i = 0; i < dim; ++i)
    {
        // #define RIDX(i,j,n) ((i)*(n)+(j))
        dc = RIDX(dim-1, i, dim);
        for(j = 0; j < dim; j += 2)
        {
            dst[dc] = src[sc];
            dst[dc-dim] = src[sc+1];
            dc -= 2*dim;
            sc += 2;
        }
    }
}

char rotate_3_descr[] = "rotate_3: unroll x4";
void rotate_3(int dim, pixel* src, pixel* dst)
{
    int i, j, sc, dc;
    sc = 0;
    for(i = 0; i < dim; ++i)
    {
        // #define RIDX(i,j,n) ((i)*(n)+(j))
        dc = RIDX(dim-1, i, dim);
        for(j = 0; j < dim; j += 4)
        {
            dst[dc] = src[sc];
            dst[dc-dim] = src[sc+1];
            dst[dc-2*dim] = src[sc+2];
            dst[dc-3*dim] = src[sc+3];
            dc -= 4*dim;
            sc += 4;
        }
    }
}

#define BLOCK 16

char rotate_4_descr[] = "rotate_4: blocking";
void rotate_4(int dim, pixel* src, pixel* dst)
{
    int i, j, ii, jj;
    for(i = 0; i < dim; i+=BLOCK)
    {
        for (j = 0; j < dim; j+=BLOCK)
        {
            for(jj = j; jj < j+BLOCK; ++jj)
            {
                for(ii = i; ii < i+BLOCK; ii+=16)
                {
                    int d = RIDX(dim-1-jj, ii, dim);
                    int s = RIDX(ii, jj, dim);
                    dst[d] = src[s];
                    dst[d+1] = src[s+dim];
                    dst[d+2] = src[s+2*dim];
                    dst[d+3] = src[s+3*dim];
                    dst[d+4] = src[s+4*dim];
                    dst[d+5] = src[s+5*dim];
                    dst[d+6] = src[s+6*dim];
                    dst[d+7] = src[s+7*dim];
                    dst[d+8] = src[s+8*dim];
                    dst[d+9] = src[s+9*dim];
                    dst[d+10] = src[s+10*dim];
                    dst[d+11] = src[s+11*dim];
                    dst[d+12] = src[s+12*dim];
                    dst[d+13] = src[s+13*dim];
                    dst[d+14] = src[s+14*dim];
                    dst[d+15] = src[s+15*dim];
                }
            }
        }
    }
}
/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    rotate_4(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate_1, rotate_1_descr);
    add_rotate_function(&rotate_2, rotate_2_descr);
    add_rotate_function(&rotate_3, rotate_3_descr); 
    add_rotate_function(&rotate_4, rotate_4_descr);
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/
 
/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* Compute min of two integers */
inline static int min(int a, int b) {
    if(a<b){
        return a;
    }else{
        return b;
    }
}

/* Compute max of two integers */
inline static int max(int a, int b) {
    if(a>b){
        return a;
    }else{
        return b;
    }
}

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
inline static void initialize_pixel_sum(pixel_sum *sum){
    sum->red = 0;
    sum->green = 0;
    sum->blue = 0;
    sum->num = 0;
}

inline static void accumulate_sum(pixel_sum *sum, pixel p){
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
}
/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j, ii, jj;
    pixel_sum ps;
    
    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            initialize_pixel_sum(&ps);
            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++){
                for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++){
                    accumulate_sum(&ps, src[RIDX(ii,jj,dim)]);
                }
            }
            dst[RIDX(i,j,dim)].red   = ps.red/ps.num;
            dst[RIDX(i,j,dim)].green = ps.green/ps.num;
            dst[RIDX(i,j,dim)].blue  = ps.blue/ps.num;
        }
    }
}

void smooth_1(int dim, pixel* src, pixel* dst)
{
    int i, j, ii, jj;
    
    for (j = 0; j < dim; j++){
        for (i = 0; i < dim; i++){
            int r, g, b, n;
            r = g = b = n = 0;
            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++){
                for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++){
                    //accumulate_sum(&ps, src[RIDX(ii,jj,dim)]);
                    r += (int) src[RIDX(ii,jj,dim)].red;
                    g += (int) src[RIDX(ii,jj,dim)].green;
                    b += (int) src[RIDX(ii,jj,dim)].blue;
                    ++n;
                }
            }
            dst[RIDX(i,j,dim)].red   = r/n;
            dst[RIDX(i,j,dim)].green = g/n;
            dst[RIDX(i,j,dim)].blue  = b/n;
        }
    }
}

void smooth_2(int dim, pixel *src, pixel *dst) 
{
    int i, j, ii, jj, si, sj, bl;
    int r1, g1, b1, n1;
    bl = 16;
    
    for (i = 0; i < dim; i+=bl)
    {
        for (j = 0; j < dim; j+=bl)
        {
            for (ii = i; ii < i+bl; ++ii)
            {
                for (jj = j; jj < j+bl; ++jj)
                {
                    r1 = g1 = b1 = n1 = 0;
                    for(si = max(ii-1, 0); si <= min(ii+1, dim-1); si++)
                    {
                        for(sj = max(jj-1, 0); sj <= min(jj+1, dim-1); sj++)
                        {
                            r1 += (int) src[RIDX(si,sj,dim)].red;
                            g1 += (int) src[RIDX(si,sj,dim)].green;
                            b1 += (int) src[RIDX(si,sj,dim)].blue;
                            ++n1;
                        }
                    }
                    dst[RIDX(ii,jj,dim)].red   = r1/n1;
                    dst[RIDX(ii,jj,dim)].green = g1/n1;
                    dst[RIDX(ii,jj,dim)].blue  = b1/n1;
                }
            }
        }
    }
}

void smooth_3(int dim, pixel* src, pixel* dst)
{
    int r, g, b, i, j;
    r = g = b = 0;
    //top left corner
    r += (int) src[RIDX(0,0,dim)].red;
    g += (int) src[RIDX(0,0,dim)].green;
    b += (int) src[RIDX(0,0,dim)].blue;

    r += (int) src[RIDX(0,1,dim)].red;
    g += (int) src[RIDX(0,1,dim)].green;
    b += (int) src[RIDX(0,1,dim)].blue;
    
    r += (int) src[RIDX(1,0,dim)].red;
    g += (int) src[RIDX(1,0,dim)].green;
    b += (int) src[RIDX(1,0,dim)].blue;
    
    r += (int) src[RIDX(1,1,dim)].red;
    g += (int) src[RIDX(1,1,dim)].green;
    b += (int) src[RIDX(1,1,dim)].blue;

    dst[RIDX(0,0,dim)].red = r/4;
    dst[RIDX(0,0,dim)].green = g/4;
    dst[RIDX(0,0,dim)].blue = b/4;
    
    //top edge
    for(j = 1; j < dim-1; ++j)
    {
        r = g = b = 0;
        r += (int) src[RIDX(0,j-1,dim)].red;
        g += (int) src[RIDX(0,j-1,dim)].green;
        b += (int) src[RIDX(0,j-1,dim)].blue;

        r += (int) src[RIDX(0,j,dim)].red;
        g += (int) src[RIDX(0,j,dim)].green;
        b += (int) src[RIDX(0,j,dim)].blue;

        r += (int) src[RIDX(0,j+1,dim)].red;
        g += (int) src[RIDX(0,j+1,dim)].green;
        b += (int) src[RIDX(0,j+1,dim)].blue;

        r += (int) src[RIDX(1,j-1,dim)].red;
        g += (int) src[RIDX(1,j-1,dim)].green;
        b += (int) src[RIDX(1,j-1,dim)].blue;

        r += (int) src[RIDX(1,j,dim)].red;
        g += (int) src[RIDX(1,j,dim)].green;
        b += (int) src[RIDX(1,j,dim)].blue;

        r += (int) src[RIDX(1,j+1,dim)].red;
        g += (int) src[RIDX(1,j+1,dim)].green;
        b += (int) src[RIDX(1,j+1,dim)].blue;

        dst[RIDX(0,j,dim)].red = r/6;
        dst[RIDX(0,j,dim)].green = g/6;
        dst[RIDX(0,j,dim)].blue = b/6;
    }

    //top right corner
    r = g = b = 0;
    r += (int) src[RIDX(0,dim-2,dim)].red;
    g += (int) src[RIDX(0,dim-2,dim)].green;
    b += (int) src[RIDX(0,dim-2,dim)].blue;

    r += (int) src[RIDX(0,dim-1,dim)].red;
    g += (int) src[RIDX(0,dim-1,dim)].green;
    b += (int) src[RIDX(0,dim-1,dim)].blue;
    
    r += (int) src[RIDX(1,dim-2,dim)].red;
    g += (int) src[RIDX(1,dim-2,dim)].green;
    b += (int) src[RIDX(1,dim-2,dim)].blue;
    
    r += (int) src[RIDX(1,dim-1,dim)].red;
    g += (int) src[RIDX(1,dim-1,dim)].green;
    b += (int) src[RIDX(1,dim-1,dim)].blue;

    dst[RIDX(0,dim-1,dim)].red = r/4;
    dst[RIDX(0,dim-1,dim)].green = g/4;
    dst[RIDX(0,dim-1,dim)].blue = b/4;

    for (i = 1; i < dim-1; ++i)
    {
        //left edge
        r = g = b = 0;
        r += (int) src[RIDX(i-1,0,dim)].red;
        g += (int) src[RIDX(i-1,0,dim)].green;
        b += (int) src[RIDX(i-1,0,dim)].blue;

        r += (int) src[RIDX(i-1,1,dim)].red;
        g += (int) src[RIDX(i-1,1,dim)].green;
        b += (int) src[RIDX(i-1,1,dim)].blue;

        r += (int) src[RIDX(i,0,dim)].red;
        g += (int) src[RIDX(i,0,dim)].green;
        b += (int) src[RIDX(i,0,dim)].blue;

        r += (int) src[RIDX(i,1,dim)].red;
        g += (int) src[RIDX(i,1,dim)].green;
        b += (int) src[RIDX(i,1,dim)].blue;

        r += (int) src[RIDX(i+1,0,dim)].red;
        g += (int) src[RIDX(i+1,0,dim)].green;
        b += (int) src[RIDX(i+1,0,dim)].blue;

        r += (int) src[RIDX(i+1,1,dim)].red;
        g += (int) src[RIDX(i+1,1,dim)].green;
        b += (int) src[RIDX(i+1,1,dim)].blue;

        dst[RIDX(i,0,dim)].red = r/6;
        dst[RIDX(i,0,dim)].green = g/6;
        dst[RIDX(i,0,dim)].blue = b/6;

        for (j = 1; j < dim-1; ++j)
        {
            //center
            r = g = b = 0;
            r += (int) src[RIDX(i-1,j-1,dim)].red;
            g += (int) src[RIDX(i-1,j-1,dim)].green;
            b += (int) src[RIDX(i-1,j-1,dim)].blue;

            r += (int) src[RIDX(i-1,j,dim)].red;
            g += (int) src[RIDX(i-1,j,dim)].green;
            b += (int) src[RIDX(i-1,j,dim)].blue;

            r += (int) src[RIDX(i-1,j+1,dim)].red;
            g += (int) src[RIDX(i-1,j+1,dim)].green;
            b += (int) src[RIDX(i-1,j+1,dim)].blue;

            r += (int) src[RIDX(i,j-1,dim)].red;
            g += (int) src[RIDX(i,j-1,dim)].green;
            b += (int) src[RIDX(i,j-1,dim)].blue;

            r += (int) src[RIDX(i,j,dim)].red;
            g += (int) src[RIDX(i,j,dim)].green;
            b += (int) src[RIDX(i,j,dim)].blue;

            r += (int) src[RIDX(i,j+1,dim)].red;
            g += (int) src[RIDX(i,j+1,dim)].green;
            b += (int) src[RIDX(i,j+1,dim)].blue;

            r += (int) src[RIDX(i+1,j-1,dim)].red;
            g += (int) src[RIDX(i+1,j-1,dim)].green;
            b += (int) src[RIDX(i+1,j-1,dim)].blue;

            r += (int) src[RIDX(i+1,j,dim)].red;
            g += (int) src[RIDX(i+1,j,dim)].green;
            b += (int) src[RIDX(i+1,j,dim)].blue;

            r += (int) src[RIDX(i+1,j+1,dim)].red;
            g += (int) src[RIDX(i+1,j+1,dim)].green;
            b += (int) src[RIDX(i+1,j+1,dim)].blue;

            dst[RIDX(i,j,dim)].red = r/9;
            dst[RIDX(i,j,dim)].green = g/9;
            dst[RIDX(i,j,dim)].blue = b/9;
        }

        //right edge
        r = g = b = 0;
        r += (int) src[RIDX(i-1,dim-2,dim)].red;
        g += (int) src[RIDX(i-1,dim-2,dim)].green;
        b += (int) src[RIDX(i-1,dim-2,dim)].blue;

        r += (int) src[RIDX(i-1,dim-1,dim)].red;
        g += (int) src[RIDX(i-1,dim-1,dim)].green;
        b += (int) src[RIDX(i-1,dim-1,dim)].blue;

        r += (int) src[RIDX(i,dim-2,dim)].red;
        g += (int) src[RIDX(i,dim-2,dim)].green;
        b += (int) src[RIDX(i,dim-2,dim)].blue;

        r += (int) src[RIDX(i,dim-1,dim)].red;
        g += (int) src[RIDX(i,dim-1,dim)].green;
        b += (int) src[RIDX(i,dim-1,dim)].blue;

        r += (int) src[RIDX(i+1,dim-2,dim)].red;
        g += (int) src[RIDX(i+1,dim-2,dim)].green;
        b += (int) src[RIDX(i+1,dim-2,dim)].blue;

        r += (int) src[RIDX(i+1,dim-1,dim)].red;
        g += (int) src[RIDX(i+1,dim-1,dim)].green;
        b += (int) src[RIDX(i+1,dim-1,dim)].blue;

        dst[RIDX(i,dim-1,dim)].red = r/6;
        dst[RIDX(i,dim-1,dim)].green = g/6;
        dst[RIDX(i,dim-1,dim)].blue = b/6;
    }

    //bottom left corner
    r = g = b = 0;
    r += (int) src[RIDX(dim-2,0,dim)].red;
    g += (int) src[RIDX(dim-2,0,dim)].green;
    b += (int) src[RIDX(dim-2,0,dim)].blue;

    r += (int) src[RIDX(dim-2,1,dim)].red;
    g += (int) src[RIDX(dim-2,1,dim)].green;
    b += (int) src[RIDX(dim-2,1,dim)].blue;
    
    r += (int) src[RIDX(dim-1,0,dim)].red;
    g += (int) src[RIDX(dim-1,0,dim)].green;
    b += (int) src[RIDX(dim-1,0,dim)].blue;
    
    r += (int) src[RIDX(dim-1,1,dim)].red;
    g += (int) src[RIDX(dim-1,1,dim)].green;
    b += (int) src[RIDX(dim-1,1,dim)].blue;

    dst[RIDX(dim-1,0,dim)].red = r/4;
    dst[RIDX(dim-1,0,dim)].green = g/4;
    dst[RIDX(dim-1,0,dim)].blue = b/4;

    //bottom edge
    for(j = 1; j < dim-1; ++j)
    {
        r = g = b = 0;
        r += (int) src[RIDX(dim-2,j-1,dim)].red;
        g += (int) src[RIDX(dim-2,j-1,dim)].green;
        b += (int) src[RIDX(dim-2,j-1,dim)].blue;

        r += (int) src[RIDX(dim-2,j,dim)].red;
        g += (int) src[RIDX(dim-2,j,dim)].green;
        b += (int) src[RIDX(dim-2,j,dim)].blue;

        r += (int) src[RIDX(dim-2,j+1,dim)].red;
        g += (int) src[RIDX(dim-2,j+1,dim)].green;
        b += (int) src[RIDX(dim-2,j+1,dim)].blue;

        r += (int) src[RIDX(dim-1,j-1,dim)].red;
        g += (int) src[RIDX(dim-1,j-1,dim)].green;
        b += (int) src[RIDX(dim-1,j-1,dim)].blue;

        r += (int) src[RIDX(dim-1,j,dim)].red;
        g += (int) src[RIDX(dim-1,j,dim)].green;
        b += (int) src[RIDX(dim-1,j,dim)].blue;

        r += (int) src[RIDX(dim-1,j+1,dim)].red;
        g += (int) src[RIDX(dim-1,j+1,dim)].green;
        b += (int) src[RIDX(dim-1,j+1,dim)].blue;

        dst[RIDX(dim-1,j,dim)].red = r/6;
        dst[RIDX(dim-1,j,dim)].green = g/6;
        dst[RIDX(dim-1,j,dim)].blue = b/6;
    }

    //top right corner
    r = g = b = 0;
    r += (int) src[RIDX(dim-2,dim-2,dim)].red;
    g += (int) src[RIDX(dim-2,dim-2,dim)].green;
    b += (int) src[RIDX(dim-2,dim-2,dim)].blue;

    r += (int) src[RIDX(dim-2,dim-1,dim)].red;
    g += (int) src[RIDX(dim-2,dim-1,dim)].green;
    b += (int) src[RIDX(dim-2,dim-1,dim)].blue;
    
    r += (int) src[RIDX(dim-1,dim-2,dim)].red;
    g += (int) src[RIDX(dim-1,dim-2,dim)].green;
    b += (int) src[RIDX(dim-1,dim-2,dim)].blue;
    
    r += (int) src[RIDX(dim-1,dim-1,dim)].red;
    g += (int) src[RIDX(dim-1,dim-1,dim)].green;
    b += (int) src[RIDX(dim-1,dim-1,dim)].blue;

    dst[RIDX(dim-1,dim-1,dim)].red = r/4;
    dst[RIDX(dim-1,dim-1,dim)].green = g/4;
    dst[RIDX(dim-1,dim-1,dim)].blue = b/4;
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    smooth_3(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&smooth_1, "smooth_1");
    add_smooth_function(&smooth_2, "smooth_2");
    add_smooth_function(&smooth_3, "smooth_3");
    /* ... Register additional test functions here */
}

