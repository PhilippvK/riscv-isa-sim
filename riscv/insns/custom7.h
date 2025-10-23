uint64_t h = 0;
uint64_t l = 0;
uint64_t g;
uint64_t u[16] = {0};
uint64_t mask_tab[4] = {0};

// Step 1
u[0] = 0;
u[1] = RS2 & ((1UL << (64 - 4)) - 1UL);
u[2] = u[1] << 1;
u[3] = u[2] ^ u[1];
u[4] = u[2] << 1;
u[5] = u[4] ^ u[1];
u[6] = u[3] << 1;
u[7] = u[6] ^ u[1];
u[8] = u[4] << 1;
u[9] = u[8] ^ u[1];
u[10] = u[5] << 1;
u[11] = u[10] ^ u[1];
u[12] = u[6] << 1;
u[13] = u[12] ^ u[1];
u[14] = u[7] << 1;
u[15] = u[14] ^ u[1];

g=0;
uint64_t tmp1 = RS1 & 15;

for(int i = 0; i < 16; i++) {
  uint64_t tmp2 = tmp1 - i;
  g ^= (u[i] & -(1 - ((tmp2 | -tmp2) >> 63)));
}
l = g;
h = 0;

// Step 2
for (uint8_t i = 4; i < 64; i += 4) {
    g = 0;
    uint64_t tmp1 = (RS1 >> i) & 15;
    for (int j = 0; j < 16; ++j) {
        uint64_t tmp2 = tmp1 - j;
        g ^= (u[j] & -(1 - ((tmp2 | -tmp2) >> 63)));
    }
    l ^= g << i;
    h ^= g >> (64 - i);
}

// Step 3
mask_tab [0] = - ((RS2 >> 60) & 1);
mask_tab [1] = - ((RS2 >> 61) & 1);
mask_tab [2] = - ((RS2 >> 62) & 1);
mask_tab [3] = - ((RS2 >> 63) & 1);

l ^= ((RS1 << 60) & mask_tab[0]);
h ^= ((RS1 >> 4) & mask_tab[0]);

l ^= ((RS1 << 61) & mask_tab[1]);
h ^= ((RS1 >> 3) & mask_tab[1]);

l ^= ((RS1 << 62) & mask_tab[2]);
h ^= ((RS1 >> 2) & mask_tab[2]);

l ^= ((RS1 << 63) & mask_tab[3]);
h ^= ((RS1 >> 1) & mask_tab[3]);

// c[0] = l;
// c[1] = h;
MMU.store_uint64(RD, l);
MMU.store_uint64(RD+8, h);
