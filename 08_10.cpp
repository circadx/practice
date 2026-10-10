#include <iostream>
void copy(const int* src, size_t k, int* dst){
  for (size_t i = 0; i < k; ++i) dst[i] = src[i];
}
void paste(int* a, size_t k, int pasta) {
  for (size_t i = 0; i < k; ++i) a[i] = pasta;
}
// Free store (new)
int * extend_fs(const int* a, size_t k, size_t d, int fill){
  int* ret = new int[k + d];
  copy(a, k, ret);
  paste(ret + k, d, fill);
  return ret;
}
// HEAP (malloc)
int * extend_c(const int* a, size_t k, size_t d, int fill){
  const size_t IS = sizeof(int);
  const size_t L = k + d;
  int* ret = reinterpret_cast< int* >(malloc(L * IS));
  if (ret != nullptr) {
    copy(a, k, ret);
    paste(ret + k, d, fill);
  }
  return ret;
}

int main()
{
  int a[] = {1, 2, 3, 4};
  int* c = extend_c(a, 4, 5, 0);
  if (!c) {
    std::cerr << "bad alloc\n";
    return 1;
  }
  int* b = nullptr;
  int* d = nullptr;
  try {
    b = extend_fs(a, 4, 2, 0);
    d = extend_fs(a, 4, 10, 10);
  } catch (...) {
    delete [] b;
    delete [] d;
    free(c);
    std::cerr << "bad alloc\n";
    return 1;
  }
  // todo
  free(c);
  delete [] b;
  delete [] d;
}