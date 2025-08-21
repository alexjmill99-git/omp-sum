#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv) {
  // Default N = 1,000,000; pass a number to override
  unsigned long long N = (argc > 1) ? strtoull(argv[1], NULL, 10) : 1000000ULL;

  double t0 = omp_get_wtime();

  unsigned long long sum = 0ULL;

  // Split the loop across threads; combine partial sums safely
  #pragma omp parallel for reduction(+:sum) schedule(static)
  for (unsigned long long i = 1; i <= N; ++i) {
    sum += i;
  }

  double t1 = omp_get_wtime();

  unsigned long long expected = N * (N + 1ULL) / 2ULL;

  printf("N=%llu\n", N);
  printf("threads=%d\n", omp_get_max_threads());
  printf("sum=%llu expected=%llu\n", sum, expected);
  printf("elapsed=%.6f s\n", t1 - t0);
  puts(sum == expected ? "OK" : "MISMATCH");
  return sum == expected ? 0 : 1;
}
