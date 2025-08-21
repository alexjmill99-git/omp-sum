FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive

# compiler + OpenMP support
RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY src/ ./
RUN gcc -O3 -fopenmp sum_omp.c -o /usr/local/bin/sum_omp

# default: sum 1,000,000
CMD ["/usr/local/bin/sum_omp","1000000"]
