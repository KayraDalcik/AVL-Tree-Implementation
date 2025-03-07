#include <stdio.h>
#include <stdlib.h>

struct AVLDugum {
    int deger;
    struct AVLDugum* sol;
    struct AVLDugum* sag;
    int yukseklik;
    struct AVLDugum* ebeveyn;
};

struct AVLDugum* dugumOlustur(int deger) {
    struct AVLDugum* dugum = (struct AVLDugum*)malloc(sizeof(struct AVLDugum));
    dugum->deger = deger;
    dugum->sol = NULL;
    dugum->sag = NULL;
    dugum->yukseklik = 1;
    dugum->ebeveyn = NULL;
    return dugum;
}

int yukseklikHesapla(struct AVLDugum* dugum) {
    if (dugum == NULL)
        return 0;
    return dugum->yukseklik;
}

int maksimum(int a, int b) {
    return (a > b) ? a : b;
}

struct AVLDugum* sagaDondur(struct AVLDugum* y) {
    struct AVLDugum* x = y->sol;
    struct AVLDugum* T2 = x->sag;

    x->sag = y;
    y->sol = T2;

    y->yukseklik = maksimum(yukseklikHesapla(y->sol), yukseklikHesapla(y->sag)) + 1;
    x->yukseklik = maksimum(yukseklikHesapla(x->sol), yukseklikHesapla(x->sag)) + 1;

    return x;
}

struct AVLDugum* solaDondur(struct AVLDugum* x) {
    struct AVLDugum* y = x->sag;
    struct AVLDugum* T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    x->yukseklik = maksimum(yukseklikHesapla(x->sol), yukseklikHesapla(x->sag)) + 1;
    y->yukseklik = maksimum(yukseklikHesapla(y->sol), yukseklikHesapla(y->sag)) + 1;

    return y;
}

int dengeFaktoru(struct AVLDugum* dugum) {
    if (dugum == NULL)
        return 0;
    return yukseklikHesapla(dugum->sol) - yukseklikHesapla(dugum->sag);
}

struct AVLDugum* ekle(struct AVLDugum* dugum, int deger) {
    if (dugum == NULL)
        return dugumOlustur(deger);

    if (deger < dugum->deger) {
        dugum->sol = ekle(dugum->sol, deger);
        dugum->sol->ebeveyn = dugum;
    } else if (deger > dugum->deger) {
        dugum->sag = ekle(dugum->sag, deger);
        dugum->sag->ebeveyn = dugum;
    } else
        return dugum;

    dugum->yukseklik = 1 + maksimum(yukseklikHesapla(dugum->sol), yukseklikHesapla(dugum->sag));
    int denge = dengeFaktoru(dugum);

    if (denge > 1 && deger < dugum->sol->deger)
        return sagaDondur(dugum);

    if (denge < -1 && deger > dugum->sag->deger)
        return solaDondur(dugum);

    if (denge > 1 && deger > dugum->sol->deger) {
        dugum->sol = solaDondur(dugum->sol);
        return sagaDondur(dugum);
    }

    if (denge < -1 && deger < dugum->sag->deger) {
        dugum->sag = sagaDondur(dugum->sag);
        return solaDondur(dugum);
    }

    return dugum;
}

void siraliGez(struct AVLDugum* kok) {
    if (kok != NULL) {
        siraliGez(kok->sol);
        printf("%d\n", kok->deger);
        siraliGez(kok->sag);
    }
}

void agaciYazdir(struct AVLDugum* kok) {
    if (kok) {
        printf("%d(-1B)\n", kok->deger);

        struct AVLDugum* kuyruk[100];
        int basla = 0, bitir = 0;

        kuyruk[bitir++] = kok;

        while (basla < bitir) {
            int dugumSayisi = bitir - basla;
            while (dugumSayisi > 0) {
                struct AVLDugum* mevcut = kuyruk[basla++];
                if (mevcut->sol) {
                    printf("%d(%dL)(%dB)", mevcut->sol->deger, mevcut->deger, dengeFaktoru(mevcut->sol));
                    kuyruk[bitir++] = mevcut->sol;
                }
                if (mevcut->sag) {
                    printf("%d(%dR)(%dB)", mevcut->sag->deger, mevcut->deger, dengeFaktoru(mevcut->sag));
                    kuyruk[bitir++] = mevcut->sag;
                }
                dugumSayisi--;
            }
            printf("\n");
        }
    }
}

int main() {
    struct AVLDugum* kok = NULL;
    int deger;

    while (1) {
        scanf("%d", &deger);
        if (deger == -1)
            break;
        kok = ekle(kok, deger);
    }

    siraliGez(kok);

    agaciYazdir(kok);

    return 0;
}