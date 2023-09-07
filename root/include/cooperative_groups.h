// Contains stuff from https://cs.calvin.edu/courses/cs/374/CUDA/CUDA-Thread-Indexing-Cheatsheet.pdf


  //#include <hip/hip_cooperative_groups.h>


namespace cooperative_groups { 
	struct Grid {
		__device__ int thread_rank() {
			int blockId = blockIdx.x + blockIdx.y * gridDim.x
			+ gridDim.x * gridDim.y * blockIdx.z;
			int threadId = blockId * (blockDim.x * blockDim.y * blockDim.z)
			+ (threadIdx.z * (blockDim.x * blockDim.y))
			+ (threadIdx.y * blockDim.x) + threadIdx.x;
			return threadId;
		}
	};
	struct Block {
		__device__ dim3 group_index() {
			return dim3{blockIdx.x,blockIdx.y,blockIdx.z}; //dim3{0,0,0};
		}
		__device__ dim3 thread_index() {
			return dim3{threadIdx.x,threadIdx.y,threadIdx.z}; //dim3{0,0,0};
		}
		__device__ void sync() {
			__syncthreads();
		}
#if 1
		__device__ int thread_rank() {
			return 0
				+ threadIdx.z * blockDim.x * blockDim.y
				+ threadIdx.y * blockDim.x
				+ threadIdx.x;
		}
#endif
	};
	__device__ Grid this_grid() {
		return {};
	}
	__device__ Block this_thread_block() {
		return {};
	}
}