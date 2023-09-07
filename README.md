To be renamed to chipStar-nvcc or something

This implements nvcc and some of the CUDA toolkit using chipStar.

- nvcc tries to mimic the original tool (NVIDIA docs https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html)
- Some libraries are stubbed

Everything is extremly hacky.

## Install chipstar into tmp

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/tmp/chipstar-cuda-install/
make install
```

## Set up your CMake (temporary step, should be gone soon) 

Use it like this:

Add this before the CMake `LANGUAGES CUDA` stuff:
```
set(CMAKE_CUDA_COMPILER_LIBRARY_ROOT_FROM_NVVMIR_LIBRARY_DIR /tmp/chipstar-cuda-install/)
set(CMAKE_CUDA_ARCHITECTURES "75")
```

Link against CHIP:
```
link_directories(cudatest PUBLIC /tmp/chipstar-install/lib/)
link_libraries(cudatest PUBLIC CHIP)
```

## Configure the build

In the cuda-cmake sample build directory:
```
rm CMakeCache.txt
rm -f /tmp/cuda-log.txt && LDFLAGS="-L/tmp/chipstar-cuda-install/" PATH=/tmp/chipstar-cuda-install/bin:$PATH cmake .. ; cat /tmp/cuda-log.txt
```

## Build

```
make; cat /tmp/cuda-log.txt 
```


#TODO CODE

```cuda
__syncthreads_count {
    // Init counter to 0
    __shared__ int count;
    if (thread_rank == 0) {
        count = 0;
    }
    __syncthreads();

    // Add each thread
    atomicAdd(count, predicate != 0)
    __syncthreads();

    // Check the total count
    return count;
}
```

##FIXME: Most of the includes in include/ should be taken from cuspv