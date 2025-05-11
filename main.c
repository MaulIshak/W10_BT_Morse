#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bintree.h"

#define MAX_LEN 100
typedef char* string;
int FindMorsePath(BinTree P, infotype target, char* path, int depth);
void BuildMorseTree(BinTree *P);
void TeksToMorse(BinTree P, char* teks);
void MorseToTeks(BinTree P, char* morseStr);

int main()
{
    BinTree tree = NULL;
    string teks = ".---  -  -.-  .-.-.  .--. ---  .-..  ..  -  .  -.-  -.  ..  -.-  .-.-.  -.  .  --.  .  .-.  ..  .-.-. -...  .-  -.  -..  ..-  -.  --.";
    BuildMorseTree(&tree);

    printf("\nIni Level Order Traversal:\n");
    LevelOrder(tree);

    printf("\nIni Post Order Traversal:\n");
    PostOrder(tree);

    printf("\nIni Pre Order Traversal:\n");
    PreOrder(tree);

    printf("\nIni In Order Traversal:\n");
    InOrder(tree);
    printf("\n");
    // PrintTree(tree, 0);
    // TeksToMorse(tree, teks);
    MorseToTeks(tree, teks);
    
    return 0;
}

// Fungsi rekursif untuk mencari huruf dan mencetak kode morse-nya
// path: string sementara yang menampung simbol arah ('•' atau '−')
// depth: posisi karakter berikutnya dalam path
int FindMorsePath(BinTree P, infotype target, char* path, int depth) {
    if (P == Nil) return 0;

    if (Info(P) == target) {
        path[depth] = '\0';  // Akhiri string path
        return 1;            // Ditemukan
    }
    path[depth] = '-';  // titik mewakili kiri
    if (FindMorsePath(Left(P), target, path, depth + 1)) {
        return 1;
    }
    path[depth] = '.';  
    if (FindMorsePath(Right(P), target, path, depth + 1)) {
        return 1;
    }

    return 0;  // Tidak ditemukan di subtree ini
}

void TeksToMorse(BinTree P, char* teks) {
    char path[MAX_LEN];
    for (int i = 0; teks[i] != '\0'; i++) {
        char ch = tolower(teks[i]);  // Anggap huruf besar dan kecil sama

            // Cari kode morse untuk huruf
            if (FindMorsePath(P, ch, path, 0)) {
                printf("%s", path);
                printf("  ");  // 2 spasi antar huruf
            } else {
                printf("?  ");  // Jika huruf tidak ditemukan
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
            if (kode[j] == '-') {
                current = Left(current);
            } else if (kode[j] == '.') {
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

void BuildMorseTree(BinTree *tree) {
    *tree = N(
            N(
                N(
                    N(
                        N(
                            NULL, 
                            '_',
                            N(
                                NULL, 
                                '9', 
                                NULL
                            )
                        ),
                        'o',
                        N(
                            NULL,
                            '0',
                            N(
                                NULL,
                                '8',
                                NULL  
                            )
                        )
                    ),
                    'm',
                    N(
                        N(
                            NULL,
                            'q',
                            NULL
                        ),
                        'g',
                        N(
                            NULL,
                            'z',
                            N(
                                NULL,
                                '7',
                                NULL
                            )
                        )
                    )
                ),
                't',
                N(
                    N(
                        N(
                            NULL,
                            'y',
                            NULL
                        ),
                        'k',
                        N(
                            NULL,
                            'c',
                            NULL
                        )
                    ),
                    'n',
                    N(
                        N(
                            NULL,
                            'x',
                            NULL
                        ),
                        'd',
                        N(
                            NULL,
                            'b',
                            N(
                                NULL,
                                '6',
                                NULL
                            )
                        )
                    )
                )
            ),
        '_',
        N(
            N(
                N(
                    N(
                        N(
                            NULL,
                            '1',
                            NULL
                        ),
                        'j',
                        NULL
                    ),
                    'w',
                    N(
                        NULL,
                        'p',
                        NULL
                    )
                ),
                'a',
                N(
                    N(
                        NULL,
                        '_',
                        N(
                            NULL,
                            ' ',
                            NULL
                        )
                    ),
                    'r',
                    N(
                        NULL,
                        'l',
                        NULL
                    )
                )
            ),
            'e',
            N(
                N(
                    N(
                        N(
                            NULL,
                            '2',
                            NULL
                        ),
                        '_',
                        NULL
                    ),
                    'u',
                    N(
                        NULL,
                        'f',
                        NULL
                    )
                ),
                'i',
                N(
                    N(
                        N(
                            NULL,
                            '3',
                            NULL
                        ),
                        'v',
                        NULL
                    ),
                    's',
                    N(
                        N(
                            NULL,
                            '4',
                            NULL
                        ),
                        'h',
                        N(
                            NULL,
                            '5',
                            NULL
                        )
                    )
                )
            )
        )
    );
}