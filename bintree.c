#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>


address Alokasi(infotype X)
{
  address new_node =(address) malloc(sizeof(Node));
  if(new_node == NULL) return NULL;

  new_node->info = X;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

void DeAlokasi(address P)
{
  free(P);
}

/* Menghasilkan sebuah pohon biner dari A, L dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
BinTree Tree (infotype Akar, BinTree L, BinTree R){
  BinTree P = Alokasi(Akar);
  if (P != NULL) {
    Left(P) = L;
    Right(P) = R;
    return P;
  }else{
    return NULL;
  }
}
/* IS : BinTree Sembarang */
/* FS : Menghasilkan sebuah BinTree */
/* Menghasilkan sebuah pohon biner dari A, L dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void MakeTree (infotype Akar, BinTree L, BinTree R, BinTree *P){
  *P = Tree(Akar, L, R);
}

/* Membentuk sebuah BinTree P dari pita karakter yang dibaca */
/* IS : Pita berisi "konstanta" pohon dalam bentuk prefix. Memori pasti cukup */
/*      Alokasi pasti berhasil */
/* FS : P dibentuk dari ekspresi dalam pita */
void BuildTree (BinTree *P){
}

boolean IsEmpty (BinTree P){
  return P == NULL;
}

/* Traversal PreOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara PreOrder : Akar, Kiri, Kanan */
void PreOrder (BinTree P) {
  if (P != NULL) {
    printf("%d ", Info(P));
    PreOrder(Left(P));
    PreOrder(Right(P));
  }
}

/* Traversal InOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara InOrder : Kiri, Arak, Kanan */
void InOrder (BinTree P){
  if (P != NULL) {
    InOrder(Left(P));
    printf("%d ", Info(P));
    InOrder(Right(P));
  }
}
/* Traversal PostOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara PostOrder :  Kiri, Kanan, Akar */
void PostOrder (BinTree P){
  if (P != NULL) {
    PostOrder(Left(P));
    PostOrder(Right(P));
    printf("%d ", Info(P));
  }
}
/* IS : P terdefinisi, h adalah jarak indentasi */
/* FS : Semua simpul P sudah ditulis dengan indentasi */
void PrintTree (BinTree P, int h){
    (void) h;
    int jmlNode = nbElmt(P);
    BinTree *queue =(BinTree*)malloc(sizeof(Node)*jmlNode);
    int front = 0, rear = 0;
    queue[rear++] = P;
    while (front < rear) {
        BinTree current = queue[front++];
        printf("info node: %c \n", Info(current));
        if (Left(current) != NULL) {
            printf("info node left son: %c \n", Info(Left(current)));
        }
        else {
            printf("info node left son: (kosong) \n");
        }
        if (Right(current) != NULL) {
            printf("info node right son: %c \n\n", Info(Right(current)));
        }
        else {
            printf("info node left son: (kosong) \n\n");
        }
        if (Left(current) != NULL) {
            queue[rear++] = Left(current);
        }
        if (Right(current) != NULL) {
            queue[rear++] = Right(current);
        }
    }
    printf("\n");
}

/***** Search *****/
boolean Search (BinTree P, infotype X){
  if (P == NULL) {
    return false;
  } else if (Info(P) == X) {
    return true;
  } else {
    return Search(Left(P), X) || Search(Right(P), X);
  }
}
/* Mengirimkan true jika ada node dari P yang bernilai X */

/***** Fungsi Lain *****/
int nbElmt (BinTree P){
  int count = 0;
  if (P != NULL) {
    count++;
    nbElmt(Left(P));
    nbElmt(Right(P));
  }

  return count;
}


/* Mengirimkan level dari node X yang merupakan salah satu simpul dari */
/* pohon biner P. Akar (P) levelnya adalah 1. Pohon tidak kosong */
int Level (BinTree P, infotype X){
  if(P == NULL) return 0;
  if(P->info == X) return 1;
  int left = Level(Left(P), X);
  if (left > 0) {
    return left + 1;
  }
  int right = Level(Right(P), X);
  if (right > 0) {
    return right + 1;
  }
  
  return 0;
}

/***** Operasi Lain *****/
/* Menambah elemen Tree di cabang Kiri dengan alokasi baru */
/* IS : P boleh kosong */
/* FS : P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
void AddDaunTerkiri (BinTree *P, infotype X){
  if(*P == NULL) {
    MakeTree(X, NULL, NULL, P);
    return;
  }
  AddDaunTerkiri(&Left(*P), X);
}

/* IS : P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* FS : P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri) */
/*      atau sebagai anak Kanan X (jika NOT Kiri) */
void AddDaun (BinTree *P, infotype X, infotype Y, boolean Kiri){
  address new_node, parent;
  parent = BinSearch(*P, X);
  if(parent != NULL){
    new_node = Alokasi(Y);
    if(Kiri){
      parent->left = new_node;
    }else{
      parent->right = new_node;
    }
  }else{
    printf("Daun tidak ditemukan\n");
  }
}


/***** Operasi untuk Binary Search Tree *****/
/* Mengirimkan alamat Node jika ada node dari P yang bernilai X */
/* Mengirimkan Nil jika tidak ditemukan */
address BinSearch (BinTree P, infotype X){
  if(P == NULL) return NULL;
  if(P->info == X) return P;

  address found = BinSearch(Left(P), X);
  if (found != NULL) return found;  
  return BinSearch(Right(P), X);
}

/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. */
/* Belum ada simpul P yang bernilai X */
void InsSearch (BinTree *P, infotype X){

}
