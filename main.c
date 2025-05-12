#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bintree.h"

#define MAX_LEN 100
int FindMorsePath(BinTree P, infotype target, char* path, int depth);
void TeksToMorse(BinTree P, char* teks);
void MorseToTeks(BinTree P, char* morseStr);
BinTree MorseTree();

int main()
{
    BinTree tree = NULL;
    char* teks = ".--- - -.-";
    tree = MorseTree();
    MorseToTeks(tree, teks);
    // TeksToMorse(tree, teks);
 

    printf("Program selesai");
    return 0;
}


int FindMorsePath(BinTree P, infotype target, char* path, int depth) {
    if (P == Nil) return 0;

    if (Info(P) == target) {
        path[depth] = '\0'; 
        return 1;           
    }

    // Kiri .
    path[depth] = '.'; 
    if (FindMorsePath(Left(P), target, path, depth + 1)) {
        return 1;
    }

    // Kanan -
    path[depth] = '-';  
    if (FindMorsePath(Right(P), target, path, depth + 1)) {
        return 1;
    }

    return 0;
}

void TeksToMorse(BinTree P, char* teks) {
    char path[MAX_LEN];
    for (int i = 0; teks[i] != '\0'; i++) {
        char ch = tolower(teks[i]); 
            if (FindMorsePath(P, ch, path, 0)) {
                printf("%s", path);
                printf("  ");
            } else {
                printf("?  "); 
            }
    }
    printf("\n");
}

void MorseToTeks(BinTree P, char* morseStr) {
    int len = strlen(morseStr);
    int i = 0;

    while (i < len) {
        // Ambil satu kode morse (hingga spasi)
        char kode[10];
        int k = 0;
        while (i < len && morseStr[i] != ' ') {
            kode[k++] = morseStr[i++];
        }
        kode[k] = '\0';  // akhiri string

        // Telusuri pohon morse sesuai simbol kode
        BinTree current = P;
        for (int j = 0; j < strlen(kode); j++) {
            // Kiri .
            if (kode[j] == '.') {
                current = Left(current);
            } else if (kode[j] == '-') { // Kanan -
                current = Right(current);
            }
        }

        // Jika simpul valid dan berisi huruf, cetak
        if (current != Nil) {
            printf("%c", Info(current));
        } else {
            printf("?");  // tidak dikenali
        }

        // Lewati satu atau dua spasi antar huruf
        while (i < len && morseStr[i] == ' ') i++;
    }

    printf("\n");
}

BinTree MorseTree(){
    
    BinTree new_tree = NULL;
    BinTree temp = NULL;

    // Level 0;
    AddDaunTerkiri(&new_tree, '#');

    // Level 1
    AddDaunTerkiri(&new_tree, 'e');
    AddDaun(&new_tree, '#', 't', false);

    // Level 2
    AddDaun(&new_tree, 'e', 'i', true);
    AddDaun(&new_tree, 'e', 'a', false);
    AddDaun(&new_tree, 't', 'n', true);
    AddDaun(&new_tree, 't', 'm', false);
    
    // Level 3
    AddDaun(&new_tree, 'i', 's', true);
    AddDaun(&new_tree, 'i', 'u', false);
    AddDaun(&new_tree, 'a', 'r', true);
    AddDaun(&new_tree, 'a', 'w', false);
    AddDaun(&new_tree, 'n', 'd', true);
    AddDaun(&new_tree, 'n', 'k', false);
    AddDaun(&new_tree, 'm', 'g', true);
    AddDaun(&new_tree, 'm', 'o', false);

    // Level 4
    AddDaun(&new_tree, 's', 'h', true);
    AddDaun(&new_tree, 's', 'v', false);
    AddDaun(&new_tree, 'u', 'f', true);
    AddDaun(&new_tree, 'u', '_', false);
    AddDaun(&new_tree, 'r', 'l', true);
    AddDaun(&new_tree, 'r', '_', false);
    AddDaun(&new_tree, 'w', 'p', true);
    AddDaun(&new_tree, 'w', 'j', false);
    AddDaun(&new_tree, 'd', 'b', true);
    AddDaun(&new_tree, 'd', 'x', false);
    AddDaun(&new_tree, 'k', 'c', true);
    AddDaun(&new_tree, 'k', 'y', false);
    AddDaun(&new_tree, 'g', 'z', true);
    AddDaun(&new_tree, 'g', 'q', false);
    AddDaun(&new_tree, 'o', '0', true);
    AddDaun(&new_tree, 'o', '_', false);
    
    // Level 5
    AddDaun(&new_tree, 'h', '5', true);
    AddDaun(&new_tree, 'h', '4', false);

    AddDaun(&new_tree, 'v', '3', false);
    
    temp = BinSearch(new_tree, 'u');
    temp->right->right = N(NULL, '2', NULL);
    
    temp = BinSearch(new_tree, 'r');
    temp->right->left = N(NULL, ' ', NULL);
    
    AddDaun(&new_tree, 'j', '1', false);
    
    AddDaun(&new_tree, 'b', '6', true);
    
    AddDaun(&new_tree, 'z', '7', true);
    
    AddDaun(&new_tree, '0', '8', true);

    temp = BinSearch(new_tree, 'o');
    temp->right->left = N(NULL, '9', NULL);
    
    return new_tree;
}


//    while (isLoop){
//         system("cls");
//         printf("1.\tInsert Node\n");
//         printf("2.\tPrint Tree\n");
//         printf("3.\tTraversal PreOrder\n");
//         printf("4.\tTraversal InOrder\n");
//         printf("5.\tTraversal PostOrder\n");
//         printf("6.\tTraversal LevelOrder\n");
//         printf("7.\tSearch Node Tree\n");
//         printf("8.\tJumlah Daun/Leaf\n");
//         printf("9.\tMencari Kedalaman Node Tree\n");
//         printf("10.\tMembandingkan 2 Node Tree\n");
//         printf("11.\tAuto Generate Morse Tree\n");
//         printf("12.\tTeks To Morse (Harus terbentuk Morse Tree)\n");
//         printf("13.\tMorse To Teks (Harus terbentuk Morse Tree)\n");
//         printf("14.\tExit\n");
//         printf("-------------------------------------------------------\n");
//         printf("Input (1-13): ");
//         scanf("%d", &choice);
//         system("cls");
//         switch (choice){
//             case 1:
//                 printf("------------- INSERT NODE -------------\n");

//                 if(tree == NULL){
//                     printf("Tree kosong, masukkan info root: ");
//                     scanf("%c", &info1);
//                     AddDaunTerkiri(&tree, info1);
//                     printf("\n%c ditambahkan sebagai root\n", &info1);
//                 }else{
//                     insert:
//                     printf("Masukkan info parent: ");
//                     scanf("%c", &info1);
//                     if(Search(tree, info1)){
//                         temp = BinSearch(tree, info1);
//                         printf("Node ditemukan, keterangan:\n");
//                         printf("Info: %c\n", temp->info);
//                         if(temp->right != NULL){
//                             printf("Info node left son: %c\n", temp->right->info);
//                         }else{
//                             printf("Info node left son: (kosong)\n");
//                         }

//                         if(temp->left != NULL){
//                             printf("Info node right son: %c\n", temp->right->info);
//                         }else{
//                             printf("Info node right son: (kosong)\n", temp->right->info);
//                         }
//                         selectPosisi:
//                         printf("\n");
//                         printf("- Pilih posisi insert -\n");
//                         printf("1. Left son\n");
//                         printf("2. Right son\n");
//                         printf("Input: \n");
//                         scanf("%d", &choice);
//                         if(choice == 1){
//                             if(temp->left == NULL){
//                                 printf("Masukkan info node untuk di-insert :");
//                                 scanf("%c", &info2);
//                                 AddDaun(&tree, info1, info2, true);    
//                             }else{
//                                 printf("Posisi left son sudah terisi, pilih posisi lain\n");
//                                 goto selectPosisi;
//                             }
//                         }else if(choice == 2){
//                             if(temp->right == NULL){
//                                 printf("Masukkan info node untuk di-insert :");
//                                 scanf("%c", &info2);
//                                 AddDaun(&tree, info1, info2, false);    
//                             }else{
//                                 printf("Posisi right son sudah terisi, pilih posisi lain\n");
//                                 goto selectPosisi;
//                             }
                            
//                         }
//                     }else{
//                         printf("Node parent tidak ditemukan\n");
//                         goto insert;
//                     }
//                 }
//                 break;
//             case 14:
//                 isLoop = false;
//                 break;
//             default:
//                 printf("Opsi tidak valid.\n");
//                 break;
//         }
//     }