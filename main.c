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
void Pause() {
    printf("\nTekan enter untuk melanjutkan...");
    getchar();
}
// Fungsi membandingkan 2 subtree apakah identik struktur dan nilainya
boolean IsTreeEqual(BinTree A, BinTree B) {
    if (A == Nil && B == Nil) return true;
    if (A == Nil || B == Nil) return false;
    if (Info(A) != Info(B)) return false;
    return IsTreeEqual(Left(A), Left(B)) && IsTreeEqual(Right(A), Right(B));
}


int main()
{
    BinTree tree = NULL;
    BinTree temp = NULL;
    int choice;
    boolean isLoop = true;
    infotype info1, info2;
    char inputStr[256];

    while (isLoop) {
        system("cls");
        printf("\n==== MENU TREE SANDI MORSE ====\n");
        printf("1.\tInsert Node\n");
        printf("2.\tPrint Tree\n");
        printf("3.\tTraversal PreOrder\n");
        printf("4.\tTraversal InOrder\n");
        printf("5.\tTraversal PostOrder\n");
        printf("6.\tTraversal LevelOrder\n");
        printf("7.\tSearch Node Tree\n");
        printf("8.\tJumlah Daun/Leaf\n");
        printf("9.\tMencari Kedalaman Node Tree\n");
        printf("10.\tMembandingkan 2 Node Tree\n");
        printf("11.\tAuto Generate Morse Tree\n");
        printf("12.\tTeks To Morse\n");
        printf("13.\tMorse To Teks\n");
        printf("14.\tExit\n");
        printf("Pilih menu [1-14]: ");
        scanf("%d", &choice);
        getchar(); // hapus newline setelah input angka

        switch (choice) {
            case 1:
                if(tree == NULL){
                    printf("Tree kosong. Masukkan info root (karakter): ");
                    scanf(" %c", &info1);
                    getchar();
                    AddDaunTerkiri(&tree, info1);
                    printf("Root '%c' ditambahkan.\n", info1);
                } else {
                    printf("Masukkan info parent: ");
                    scanf(" %c", &info1);
                    getchar();
                    if(Search(tree, info1)) {
                        temp = BinSearch(tree, info1);
                        printf("Parent ditemukan :\n");
                        PrintNode(temp);
                        printf("Masukkan info anak baru: ");
                        scanf(" %c", &info2);
                        getchar();
                        printf("1. Kiri\n2. Kanan\nPilih posisi: ");
                        int pos;
                        scanf("%d", &pos);
                        getchar();
                        AddDaun(&tree, info1, info2, pos == 1);
                        printf("Node '%c' ditambahkan ke %s dari '%c'.\n", info2, (pos == 1 ? "kiri" : "kanan"), info1);
                    } else {
                        printf("Parent '%c' tidak ditemukan.\n", info1);
                    }
                }
                Pause();
                break;

            case 2:
                PrintTree(tree, 2);
                Pause();
                break;

            case 3:
                PreOrder(tree);
                printf("\n");
                Pause();
                break;

            case 4:
                InOrder(tree);
                printf("\n");
                Pause();
                break;

            case 5:
                PostOrder(tree);
                printf("\n");
                Pause();
                break;

            case 6:
                LevelOrder(tree);
                Pause();
                break;

            case 7:
                printf("Masukkan node yang ingin dicari: ");
                scanf("%c", &info1);
                getchar();
                temp = BinSearch(tree, info1);
                if (temp != NULL) {
                    printf("Node '%c' ditemukan di tree.\n", info1);
                    PrintNode(temp);
                } else {
                    printf("Node '%c' TIDAK ditemukan di tree.\n", info1);
                }
                Pause();
                break;

            case 8:
                printf("Jumlah daun: %d\n", nbDaun(tree));
                Pause();
                break;

            case 9:
                printf("Masukkan node yang ingin dicek kedalamannya: ");
                scanf("%c", &info1);
                getchar();
                printf("Level dari node '%c' adalah %d\n", info1, Level(tree, info1));
                Pause();
                break;

            case 10:
              // Bandingkan 2 subtree berdasarkan node info1 dan info2
                printf("Masukkan dua node yang ingin dibandingkan: \n");
                scanf(" %c %c", &info1, &info2);
                getchar();
                BinTree t1 = BinSearch(tree, info1);
                BinTree t2 = BinSearch(tree, info2);
                if (t1 != Nil && t2 != Nil) {
                    if (IsTreeEqual(t1, t2)) {
                        printf("Subtree dari '%c' dan '%c' identik.\n", info1, info2);
                    } else {
                        printf("Subtree dari '%c' dan '%c' berbeda.\n", info1, info2);
                    }
                } else {
                    printf("Salah satu atau kedua node tidak ditemukan.\n");
                }
                Pause();
                break;

            case 11:
                tree = MorseTree();
                printf("Morse tree berhasil dibentuk.\n");
                Pause();
                break;

            case 12:
                if (tree == NULL) {
                    printf("Tree masih kosong.\n");
                    Pause();
                    break;
                }
                printf("Masukkan teks: ");
                fgets(inputStr, sizeof(inputStr), stdin);
                inputStr[strcspn(inputStr, "\n")] = 0; // hapus newline
                TeksToMorse(tree, inputStr);
                Pause();
                break;

            case 13:
                if (tree == NULL) {
                    printf("Tree masih kosong.\n");
                    Pause();
                    break;
                }
                printf("Masukkan kode morse (gunakan . dan -): ");
                fgets(inputStr, sizeof(inputStr), stdin);
                inputStr[strcspn(inputStr, "\n")] = 0;
                MorseToTeks(tree, inputStr);
                Pause();
                break;

            case 14:
                isLoop = false;
                printf("Keluar dari program...\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan pilih 1 - 14.\n");
                Pause();
                break;
        }
    }

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