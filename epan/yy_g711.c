int aaa(unsigned char a_val) {
    int t, seg;
    a_val ^= 0x55;
    t = (a_val & 0xf) << 4;
    seg = ((unsigned) a_val & 0x70) >> 4;
    switch (seg) {
        case 0:
            t += 8;
            break;
        case 1:
            t += 0x108;
            break;
        default:
            t += 0x108;
            t <<= seg - 1;
    }
    return ((a_val & 0x80) ? t : -t);
}

int uuu(unsigned char u_val) {
    int t;
    u_val = ~u_val;
    t = ((u_val & 0xf) << 3) + 0x84;
    t <<= ((unsigned) u_val & 0x70) >> 4;
    return ((u_val & 0x80) ? (0x84 - t) : (t - 0x84));
}

int yy_g711a(unsigned char in[], int inlen, unsigned char out[]) {
    int i, j;
    for (i = 0; i < inlen; i++) {
        j = aaa(in[i]);
        out[2 * i] = j >> 8 & 0xff;
        out[2 * i + 1] = j & 0xff;
    }
    return 2 * inlen;
}

int yy_g711u(unsigned char in[], int inlen, unsigned char out[]) {
    int i, j;
    for (i = 0; i < inlen; i++) {
        j = uuu(in[i]);
        out[2 * i] = j >> 8 & 0xff;
        out[2 * i + 1] = j & 0xff;
    }
    return 2 * inlen;
}
