__global__ void raceKernel(int *data) {
  int idx = threadIdx.x;
  data[idx] = idx;  // Write
  int val = data[idx];  // Read
}

int main() {
  int *d_data;
  cudaMalloc((void**)&d_data, sizeof(int) * 256);
  raceKernel<<<1, 256>>>(d_data);
  cudaFree(d_data);
  return 0;
}
