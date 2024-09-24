#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IM_DIM 512
#define KERNEL_DIM 7
#define THREADS_PER_BLOCK 16

typedef struct {
    double arr[KERNEL_DIM][KERNEL_DIM];
} Kernel;

typedef struct {
    unsigned int arr[IM_DIM][IM_DIM];
} Gray_Image;

// returns a kernel of a given size
Kernel blur_kernel() {
    Kernel kernel;
    for (int i=0; i < KERNEL_DIM; i++) {
        for (int j=0; j < KERNEL_DIM; j++) {
            kernel.arr[i][j] = 1.0/(KERNEL_DIM*KERNEL_DIM);
        }
    }
    return kernel;
}



    // applies a kernel to blur images 
__global__ void apply_kernel(unsigned char* input, unsigned char* output, double *kernel, int dim) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (col < dim && row < dim) {
        unsigned int pixel;
        double total = 0;
        for (int i = row - KERNEL_DIM/2; i < row+KERNEL_DIM/2+1;i++){
            for (int j = col-KERNEL_DIM/2; j < col+KERNEL_DIM/2+1;j++){
                double kernel_gradient = kernel[(i-(row - KERNEL_DIM/2))*KERNEL_DIM+j-(col - KERNEL_DIM/2)];
                if(0<=i&& i<IM_DIM && 0<=j&& j<IM_DIM){
                    total += ((double)(input[i*IM_DIM+j]))*kernel_gradient;
                }
                else{
                    total += ((double)(input[row*IM_DIM+col]))*kernel_gradient;
                }
            }
        }
        pixel=(unsigned int)((0 <= total && total <= 255)?total:(total > 255)?255:0);
        output[row * dim + col] = (unsigned char)pixel;
    }
}

Gray_Image make_image(){
    Gray_Image image = {.arr = {{0}}};
    for (int i = 0; i < IM_DIM; i++){
        for (int j = 0; j < IM_DIM; j++){
            image.arr[i][j] = rand()%256;
        }
    }
    return image;
}

void print_image(Gray_Image image){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d,",image.arr[i][j]);
        }
        printf("end\n");
    }
}

int main() {
    Gray_Image original = make_image();
    Kernel kernel = blur_kernel();
    Gray_Image blured;
    unsigned char *o_image, *b_image;
    double  *d_kernel;
    size_t image_size = sizeof(Gray_Image);
    size_t kernel_size = sizeof(Kernel);
    cudaMalloc(&o_image, image_size);
    cudaMalloc(&b_image, image_size);
    cudaMalloc(&d_kernel, kernel_size);
    cudaMemcpy(o_image, &original, image_size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_kernel, &kernel, kernel_size, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    dim3 numBlocks(IM_DIM / threadsPerBlock.x, IM_DIM / threadsPerBlock.y);
    apply_kernel<<<numBlocks, threadsPerBlock>>>(o_image, b_image, d_kernel, IM_DIM);

    cudaMemcpy(blured.arr, b_image, image_size, cudaMemcpyDeviceToHost);

    cudaFree(o_image);
    cudaFree(b_image);
    cudaFree(d_kernel);
    
    printf("Original image:\n");
    print_image(original);
    printf("Blured image:\n");
    print_image(blured);
    return 0;
}