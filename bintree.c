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
  }else{
    printf("Tree kosong\n");
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
  }else{
    printf("Tree kosong\n");
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
  }else{
    printf("Tree kosong\n");
  }
}
/* IS : P terdefinisi, h adalah jarak indentasi */
/* FS : Semua simpul P sudah ditulis dengan indentasi */
void PrintTree (BinTree P, int h){
  if (P != NULL) {
    PrintTree(Right(P), h + 1);
    for (int i = 0; i < h; i++) {
      printf("   ");
    }
    printf("%d\n", Info(P));
    PrintTree(Left(P), h + 1);
  }
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
int nbElmt (BinTree P);
