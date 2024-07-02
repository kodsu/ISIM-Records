void compute2(long *a, long *b, long k) {
    long n = 1 << k;
    long i, j;

    // Zmienne pomocnicze
    long *end_a = a + n * n;
    long *ptr_a = a;
    long *ptr_b;
    long temp;

    // Pierwsza pętla: a[i * n] = a[i] = 0;
    for (i = 0; i < n; i++) {
        *ptr_a = 0;
        *(a + i) = 0;
        ptr_a += n;
    }

    // Druga pętla: a[j * n + i] = i * j;
    ptr_a = a + n;
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            *(ptr_a + j) = i * j;
        }
        ptr_a += n;
    }

    // Trzecia pętla: b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];
    ptr_a = a + n;
    ptr_b = b + n;
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            temp = *(ptr_a + j - 1) + *(ptr_a - n + j - 1);
            *(ptr_b + j) = temp;
        }
        ptr_a += n;
        ptr_b += n;
    }
}