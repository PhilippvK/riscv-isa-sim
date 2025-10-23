uint64_t g = 0;
uint64_t tmp1 = (RS2) & 15;

for (int j = 0; j < 16; j++) {
    uint64_t tmp2 = tmp1 - j;
    uint64_t u = MMU.load_uint64(RS1 + j*8);
    g ^= (u & -(1 - ((tmp2 | -tmp2) >> 63)));
}

WRITE_RD(g);
