#pragma once




void Xor_payload(PBYTE sh, SIZE_T ssize, PBYTE KEY, SIZE_T skey) {

    for (int i = 0, j = 0; i < ssize; i++, j++) {
        if (j >= skey) {
            j = 0;
        }
        sh[i] ^= KEY[j] + i;
        //printf("%02X\n", KEY[j]);
    }
}
