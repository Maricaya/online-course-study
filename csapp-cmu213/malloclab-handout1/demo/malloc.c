//void *
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int heap_int();

uint64_t mem_alloc(uint32_t size);

void mem_free(uint64_t vaddr);

static uint64_t round_up(uint64_t x, uint64_t n) {
    return n * ((x + n - 1) / n);
}

static void get_blocksize(uint64_t header_vaddr) {
int heap;
uint32_t header_value = heap[header_vaddr];
}


int main() {
    return 1;
}