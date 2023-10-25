#include <stdlib.h>
#include <stdint.h>
#include <string.h>
// Fonction de hashage: calcule le hash d'une chaine de caractere.
uint32_t hash(const char *str)
{
    uint32_t hash = 5381;
    char c = str[0];
    // variable pour savoir si on est arrive a la fin de la chaine de caractere.
    int32_t comp = strcmp(&c, "\0");
    uint32_t i=1;

    while (comp!=0){
        hash = hash*33 + c;
        c = str[i];
        comp =strcmp(&c, "\0");
        i++;
    }
    return hash;
}
