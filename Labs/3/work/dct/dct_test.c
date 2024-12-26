#include <stdio.h>
#include "dct.h"

int main() {
#if !RECOVERY_MODE    
    // short a[N][N], b[N][N], b_expected[N][N];
    short a[N], b[N], c[N];
    int i, tmp;
    FILE *fp;

    fp = fopen("input.dat", "r");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        fscanf(fp, "%d", &tmp);
        //     a[i][j] = tmp;
        // }
        a[i] = tmp;
    }
    fclose(fp);
    dct(a, b);
    #if SECTION_3_9
    idct(b, c);
    #endif

    #if 0
    fp = fopen("output.golden.dat", "r");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        fscanf(fp, "%d", &tmp);
        //     b_expected[i][j] = tmp;
        // }
        b_expected[i] = tmp;
    }
    fclose(fp);

    for (i = 0; i < N; ++i) {
        if (b[i] != b_expected[i]){
            printf("Incorrect output on sample %d. Expected %d, Received %d \n", i, b_expected[i], b[i]);
            retval = 2;
        }
    }
    #endif

    #if 1 // Optionally write out computed values
    fp = fopen("output.dat", "w");
    for (i = 0; i < N; i++) {
        // for (j = 0; j < N; j++) {
        #if SECTION_3_9
        fprintf(fp, "%d\n", c[i]);
        #else
        fprintf(fp, "%d\n", b[i]);
        #endif
        // }
        // fprintf(fp, "\n");
    }
    fclose(fp);
    #endif

    #if 0
    if (retval != 2) {
        printf("    *** *** *** *** \n");
        printf("    Results are good \n");
        printf("    *** *** *** *** \n");
    } else {
        printf("    *** *** *** *** \n");
        printf("    BAD!! \n");
        printf("    *** *** *** *** \n");
    }
    #endif
#else
    int i, j;
    FILE *fp;

    fp = fopen("input.dat", "r");
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            int tmp;
            fscanf(fp, "%d", &tmp);
            input[i][j] = tmp;
        }
    }
    fclose(fp);

    for (int y = 0; y < HEIGHT; y += BLOCK_SIZE) {
        for (int x = WIDTH - BLOCK_SIZE; x >= 0; x -= BLOCK_SIZE) {
            process_8x8_block(x, y);
        }
    }

    fp = fopen("output.dat", "w");
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            fprintf(fp, "%d ", idct_output[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
#endif

    return 0;
}

#if RECOVERY_MODE    
void process_8x8_block(int x, int y) {
    dct_data_t block_in[BLOCK_SIZE * BLOCK_SIZE];
    dct_data_t block_out[BLOCK_SIZE * BLOCK_SIZE];
    dct_data_t block_idct[BLOCK_SIZE * BLOCK_SIZE];
    int i, j, k = 0;

    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            block_in[k++] = input[y + i][x + j];
        }
    }

    dct(block_in, block_out);
    idct(block_out, block_idct);

    k = 0;
    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            dct_output[y + i][x + j] = block_out[k];
            idct_output[y + i][x + j] = block_idct[k];
            k++;
        }
    }
}
#endif
