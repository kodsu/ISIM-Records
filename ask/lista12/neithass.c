long neigh(long a[], long n, long i, long j){ 
    int x = (i-1)*n; n += n; int  y = x + n, e = j-1; j++; 
    int res = a[x + j]; 
    res += a[x + e]; 
    res += a[y - e];
    res += a[y - j];   
    return res; 
}


long neigh(long a[], long n, long i, long j) {
    long ul = a[(i-1)*n + (j-1)];
    long ur = a[(i-1)*n + (j+1)];
    long dl = a[(i+1)*n - (j-1)];
    long dr = a[(i+1)*n - (j+1)];
    return ul + ur + dl + dr;
}

long neigh(long a[], long n, long i, long j) {
    long x = n*i, y = n - (j+1); 
    long *w = a + x + y; 
    long ans = *w + *(w + 2);
    w -= 2*y; 
    ans += *w + *(w+2); 
    return ans; 
}