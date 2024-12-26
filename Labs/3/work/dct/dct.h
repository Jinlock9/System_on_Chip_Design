#ifndef __DCT_H__
#define __DCT_H__

#define DW 16
#define N 1024/DW
#define NUM_TRANS 16

#define SECTION_3_9 1
#define RECOVERY_MODE 0

typedef short dct_data_t;

#define DCT_SIZE 8    /* defines the input matrix as 8x8 */
#define CONST_BITS  13
#define DESCALE(x,n)  (((x) + (1 << ((n)-1))) >> n)

#if RECOVERY_MODE
#define WIDTH 512
#define HEIGHT 512
#define BLOCK_SIZE 8

dct_data_t input[HEIGHT][WIDTH];
dct_data_t dct_output[HEIGHT][WIDTH];
dct_data_t idct_output[HEIGHT][WIDTH];

void process_8x8_block(int x, int y);
#endif

void dct(short input[N], short output[N]);

#if SECTION_3_9
void idct(short input[N], short output[N]);
#endif

#endif // __DCT_H__ not defined
