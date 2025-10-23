uint16_t tmp = 0;
uint16_t mask = 0xFFFF;
for (int i = 0; i < 14; ++i) {
    tmp += ((1 - ((RS1 >> i) & 0x0001)) & mask);
    mask &= - (1 - ((RS1 >> i) & 0x0001));
}
WRITE_RD(tmp);
