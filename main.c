#include <raylib.h>
#include <stdio.h>
#include ".\Scripts\login_screen.c"
#include ".\Scripts\products.c"

int main(void){
    
    gerar_lista_produtos();
    gerar_arquivo();
    login_screen();    
    
}
























