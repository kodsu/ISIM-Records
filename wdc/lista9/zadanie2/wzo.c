#include <stdio.h>
#include <stdlib.h>

const int MAXN = 1e5 + 5;
typedef long long ll;

struct wie {
    struct wie* lewy;
    struct wie* prawy;
    ll wart;
};

int n, q;
int ile[100005];
ll suma[100005];
struct wie* pocz[100005];
struct wie* kon[100005];

struct wie* tworz(ll a, struct wie* lewy, struct wie* prawy) {
    struct wie* nowy = (struct wie*)malloc(sizeof(struct wie));
    if(nowy == NULL) {
        exit(1);
    }
    nowy->wart = a;
    nowy->lewy = lewy;
    nowy->prawy = prawy;
    return nowy;
}

void przepnij(int mag_pocz, int mag_kon, struct wie* l, struct wie* p) {
    if(l->lewy == NULL && p->prawy == NULL) {
        pocz[mag_pocz] = NULL;
        kon[mag_pocz] = NULL;
        if(kon[mag_kon] == NULL) {
            pocz[mag_kon] = l;
            kon[mag_kon] = p;
        }
        else {
            kon[mag_kon]->prawy = l;
            l->lewy = kon[mag_kon];
            kon[mag_kon] = p;
        }
    }
    else if(l->lewy == NULL) {
        pocz[mag_pocz] = p->prawy;
        p->prawy->lewy = NULL;
        p->prawy = NULL;
        if(kon[mag_kon] == NULL) {
            pocz[mag_kon] = l;
            kon[mag_kon] = p;
        }
        else {
            kon[mag_kon]->prawy = l;
            l->lewy = kon[mag_kon];
            kon[mag_kon] = p;
        }
    }
    else if(p->prawy == NULL){
        kon[mag_pocz] = l->lewy;
        l->lewy->prawy = NULL;
        l->lewy = NULL;
        if(kon[mag_kon] == NULL) {
            pocz[mag_kon] = l;
            kon[mag_kon] = p;
        }
        else {
            kon[mag_kon]->prawy = l;
            l->lewy = kon[mag_kon];
            kon[mag_kon] = p;
        }
    }
    else {
        l->lewy->prawy = p->prawy;
        p->prawy->lewy = l->lewy;
        p->prawy = NULL;
        l->lewy = NULL;
        if(kon[mag_kon] == NULL) {
            pocz[mag_kon] = l;
            kon[mag_kon] = p;
        }
        else {
            kon[mag_kon]->prawy = l;
            l->lewy = kon[mag_kon];
            kon[mag_kon] = p;
        }
    }
}

int main(void) {
    int spr;
    spr = scanf(" %d %d", &n, &q);
    for(int i = 1; i <= n; i++) {
        spr = scanf(" %d", &ile[i]);
        for(int ii = 0; ii < ile[i]; ii++) {
            ll a;
            spr = scanf(" %lld", &a);
            suma[i] += a;
            if(ii == 0) {
                struct wie* nowy = tworz(a, NULL, NULL);
                pocz[i] = nowy;
                kon[i] = nowy;
            }
            else {
                struct wie* nowy = tworz(a, kon[i] , NULL);
                kon[i]->prawy = nowy;
                kon[i] = nowy;
            }
        }
    }
    for(int i = 0; i < q; i++) {
        char c;
        spr = scanf(" %c", &c);
        if(c == 'K') {
            for(int ii = 1; ii <= n; ii++) {
                printf("%lld ", suma[ii]);
            }
            printf("\n");
        }
        else {
            int mag_pocz, mag_kon, od_pocz, od_kon;
            spr = scanf(" %d %d %d %d", &mag_pocz, &mag_kon, &od_pocz, &od_kon);
            if(od_pocz > 0 && od_kon > 0) {
                struct wie* p = pocz[mag_pocz];
                struct wie* l = pocz[mag_pocz];
                ll usun = p->wart;
                for(int ii = 0; ii < od_kon - 1; ii++) {
                    p = p->prawy;
                    usun += p->wart;
                }
                for(int ii = 0; ii < od_pocz - 1; ii++) {
                    usun -= l->wart;
                    l = l->prawy;
                }
                przepnij(mag_pocz, mag_kon, l, p);
                suma[mag_pocz] -= usun;
                suma[mag_kon] += usun;
                ile[mag_kon] += od_kon - od_pocz + 1;
                ile[mag_pocz] -= od_kon - od_pocz + 1;
            }
            else if(od_pocz > 0 && od_kon < 0) {
                od_kon = ile[mag_pocz] + od_kon + 1;
                struct wie* p = kon[mag_pocz];
                struct wie* l = pocz[mag_pocz];
                ll usun = suma[mag_pocz];
                for(int ii = 0; ii < ile[mag_pocz] - od_kon; ii++) {
                    usun -= p->wart;
                    p = p->lewy;
                }
                for(int ii = 0; ii < od_pocz - 1; ii++) {
                    usun -= l->wart;
                    l = l->prawy;
                }
                przepnij(mag_pocz, mag_kon, l, p);
                suma[mag_pocz] -= usun;
                suma[mag_kon] += usun;
                ile[mag_kon] += od_kon - od_pocz + 1;
                ile[mag_pocz] -= od_kon - od_pocz + 1;
            }
            else {
                od_pocz = ile[mag_pocz] + od_pocz + 1;
                od_kon = ile[mag_pocz] + od_kon + 1;
                struct wie* p = kon[mag_pocz];
                struct wie* l = kon[mag_pocz];
                ll usun = l->wart;
                for(int ii = 0; ii < ile[mag_pocz] - od_pocz; ii++) {
                    l = l->lewy;
                    usun += l->wart;
                }
                for(int ii = 0; ii < ile[mag_pocz] - od_kon; ii++) {
                    usun -= p->wart;
                    p = p->lewy;
                }
                przepnij(mag_pocz, mag_kon, l, p);
                suma[mag_pocz] -= usun;
                suma[mag_kon] += usun;
                ile[mag_kon] += od_kon - od_pocz + 1;
                ile[mag_pocz] -= od_kon - od_pocz + 1;
            }
        }
    }
    spr--;
    return 0;
}