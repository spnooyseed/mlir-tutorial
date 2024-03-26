## in docker use mlir to do GEMM optimization
```
1. git clone git@github.com:spnooyseed/mlir-tutorial.git
2. git submodule update --init --recursive
```
**compile llvm-project**
```
1. mkdir llvm-project/build
2. cd llvm-project/build
3. cmake ../llvm \
   -DLLVM_ENABLE_PROJECTS=mlir \
   -DLLVM_BUILD_EXAMPLES=ON \
   -DLLVM_TARGETS_TO_BUILD="Native;NVPTX" \
   -DCMAKE_BUILD_TYPE=Release \
   -DLLVM_ENABLE_ASSERTIONS=ON
4. export PATH=/workspace/mlir-tutorial/llvm-project/build/bin:$PATH
5. make -j mlir-opt // if need other tool , can add ; it need all , only: make -j
```
**compile own mlir-tutorial**
```
1. mkdir build && cd build 
2. cmake .. \
    -DMLIR_DIR=$PWD/../llvm-project/build/lib/cmake/mlir \
    -DLLVM_DIR=$PWD/../llvm-project/build/lib/cmake/llvm \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_BUILD_TYPE=RELEASE

3. make -j mltu-opt
```
**install required software**
```
1. apt-get update
2. apt-get install openssl libssl-dev wget
3. wget https://github.com/Kitware/CMake/releases/download/v3.24.3/cmake-3.24.3.tar.gz
4. tar -zxvf cmake-3.24.3.tar.gz 
5. cd cmake-3.24.3
6. ./bootstrap
7. make -j
8. make instasll
9. wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
10. bash Miniconda3-latest-Linux-x86_64.sh
```

**clang-format file**
```
find . -name "*.cpp" -o -name "*.h" | grep -v "build/\|llvm-project/" | xargs clang-format -i
```