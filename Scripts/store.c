#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "user_info.c"

#define N_GRIDS 50

typedef struct
{
    int id_real;
    int estoque;
    int preco;

    char nome_produto[40];
    char descricao_produto[200];
    
    Image imagem_produto;
    Texture2D textura_imagem;
    
}Produto;

Produto produto[N_GRIDS];
Rectangle grid[N_GRIDS];

Rectangle grid_carrinho[5];
Rectangle botao_mais[10];
Rectangle botao_menos[10];
Rectangle botao_excluir[5];

int pos_x = 45;
int pos_y = 150;

int pos_x_carrinho = 10;
int pos_y_carrinho = 180;

int i = 1;

bool close = false;

bool retornar_id = false;

int contar_id[5];
int contador_id = 0;
int n_compras = 0;
int quantidade_produtos[5];

int preco_total;
int preco_total_produto[5];

int vetor_id_real[N_GRIDS];

char caminho[20] = "Imagens/";

Image imagem_tela_produto;
Texture2D image_tela;

long int n_pedido;

//Gera o caminho das imagens

static void generate_path()
{
    
    for(int i = 1; i <= N_GRIDS; i++)
    {
        strcat(caminho,FormatText("%i.png",vetor_id_real[i]));
        produto[i].imagem_produto = LoadImage(caminho);
        ImageResize(&produto[i].imagem_produto, 100, 100);
        produto[i].textura_imagem = LoadTextureFromImage(produto[i].imagem_produto);
        UnloadImage(produto[i].imagem_produto);
        strcpy(caminho, "Imagens/");
        
    }
    
}


static void gerar_arquivo_leitura()
{
    FILE* arquivo;
    arquivo = fopen("Data\\print_products.cfg", "w");
    fclose(arquivo);
    
    
}
static void gerar_valores_grid()
{
    int pular_linha = 0;
    pos_x = 45;
    pos_y = 150;
    i = 1;
    for(int l = 0; l < N_GRIDS/5; l++)
    {
        pos_x = 50;
        for(; i <= 5 + pular_linha; i++)
        {
            grid[i].x = pos_x;
            grid[i].y = pos_y;
            grid[i].width = 160;
            grid[i].height = 230;
            pos_x += 200;
        }
    pular_linha += 5;
    pos_y += 280;
 
    } 
    
}

static void carregar_produtos_grid()
{
 
        int id_real;
        
        int estoque;
        int preco;
        
        int contador = 0;

        char nome_produto[40];
        char descricao_produto[200];
      
        FILE* arquivo;
        arquivo = fopen("Data\\print_products.cfg", "r");
        
        FILE* arquivo_product_list;
        arquivo_product_list = fopen("Data\\products_list.cfg", "r");
        
        
        while(!feof(arquivo_product_list))
        {
            fscanf(arquivo_product_list, "%d -%s -%d -%d -%s\n", &id_real, nome_produto, &estoque, &preco, descricao_produto);
            contador++;
            
            if(estoque > 0)
            {  
                fclose(arquivo);
                arquivo = fopen("Data\\print_products.cfg", "a");
                fprintf(arquivo, "%d -%s -%d -%d -%s\n", contador, nome_produto, estoque, preco, descricao_produto);
                tratar_string(nome_produto); tratar_string(descricao_produto); 
                vetor_id_real[contador] = id_real;
                strcpy(produto[contador].nome_produto, nome_produto); produto[contador].estoque = estoque; produto[contador].preco = preco; strcpy(produto[contador].descricao_produto, descricao_produto);
                fclose(arquivo);
                arquivo = fopen("Data\\print_products.cfg", "r");
            }
            
            if(estoque == 0)
            {
                fclose(arquivo);
                arquivo = fopen("Data\\print_products.cfg", "a");
                fprintf(arquivo, "%d -%s -%d -%d -%s\n", contador, nome_produto, estoque, preco, descricao_produto);
                tratar_string(nome_produto); tratar_string(descricao_produto); 
                vetor_id_real[contador] = id_real;
                strcpy(produto[contador].nome_produto, nome_produto); produto[contador].estoque = estoque; produto[contador].preco = preco; strcpy(produto[contador].descricao_produto, descricao_produto);
                fclose(arquivo);
                arquivo = fopen("Data\\print_products.cfg", "r");
            }
            
        }
        
    fclose(arquivo);
    fclose(arquivo_product_list);
    return;
}

static int printar_grid(int id, int* pointer)
{
   
    DrawRectangleRec(grid[id], WHITE);
    DrawTexture(produto[id].textura_imagem, grid[id].x + 23, grid[id].y + 25, WHITE);
    DrawRectangleLines(grid[id].x, grid[id].y, grid[id].width, grid[id].height, GRAY);
    DrawText(produto[id].nome_produto,grid[id].x + 10, grid[id].y + grid[id].height/2 + 20, 16, BLACK);
    DrawText(FormatText("%iR$",produto[id].preco), (grid[id].x + grid[id].width/2 + 40) - MeasureText(FormatText("%iR$",produto[id].preco),22), grid[id].y + grid[id].height/2 + 90, 22, BLACK);
    
    produto[id].nome_produto[18] = '\n';
    if(CheckCollisionPointRec(GetMousePosition(), grid[id]))
    {
        DrawRectangleLines(grid[id].x, grid[id].y, grid[id].width, grid[id].height, ORANGE);
        
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            retornar_id = true;
            
        }
        
    }
    
    if(retornar_id == true)
    {
        *pointer = 5;
        retornar_id = false;
        imagem_tela_produto = LoadImage(FormatText("Imagens/%i.png", vetor_id_real[id]));
        ImageResize(&imagem_tela_produto, 345, 345);
        image_tela = LoadTextureFromImage(imagem_tela_produto);
        UnloadImage(imagem_tela_produto);
        return id;
    }
    else
    {
       return 0; 
    }
    
}

static int pesquisar(char* campo_de_pesquisa, int* vetor_pesquisados)
{
    
    int id_real;
    int id_aux;
    
    int contador = 0;
    int estoque;
    int preco;

    char nome_produto[40];
    char descricao_produto[200];
    
       FILE* arquivo;
       arquivo = fopen("Data\\print_products.cfg", "r");
  
       
       while(!feof(arquivo))
       {
           fscanf(arquivo, "%d -%s -%d -%d -%s\n", &id_real, nome_produto, &estoque, &preco, descricao_produto);
           tratar_string(nome_produto); tratar_string(descricao_produto); 
           if(strncmp(campo_de_pesquisa, nome_produto, strlen(campo_de_pesquisa)) == 0)
           {
               contador++;
               strcpy(produto[id_real].nome_produto, nome_produto); produto[id_real].estoque = estoque; produto[id_real].preco = preco; strcpy(produto[id_real].descricao_produto, descricao_produto);
               vetor_pesquisados[contador] = id_real;
               grid[id_real].x = grid[contador].x;
               grid[id_real].y = grid[contador].y;
               
           }
       }
       
       fclose(arquivo);
    
    return contador;
 
}

static void load_product_to_page(int id, char* nome_produto, int* preco, int* estoque, char* descricao_produto, Rectangle local_da_imagem)
{
    
    strcpy(nome_produto, produto[id].nome_produto);
    *preco = produto[id].preco;
    *estoque = produto[id].estoque;
    strcpy(descricao_produto, produto[id].descricao_produto);
    retornar_id = false;
    DrawTexture(image_tela, local_da_imagem.x + 2.5, local_da_imagem.y +2.5, WHITE);
    
    if(*estoque == 0)
    {
        DrawText("Produto esgotado", 620, 500, 20, MAROON);
    }
    
}

static void gerar_grid_carrinho()
{
    for(int j = 0; j < 5; j++)
    {
        grid_carrinho[j].x = pos_x_carrinho;
        grid_carrinho[j].y = pos_y_carrinho;
        grid_carrinho[j].width = 1060;
        grid_carrinho[j].height = 100;
        pos_y_carrinho += 101;
    }
    
    pos_x_carrinho = 750;
    pos_y_carrinho = 225;
    
    for(int k = 0; k < 5; k++)
    {
        botao_mais[k].x = pos_x_carrinho;
        botao_menos[k].x = pos_x_carrinho + 62;
        
        botao_mais[k].y = pos_y_carrinho;
        botao_menos[k].y = pos_y_carrinho;
        
        botao_mais[k].width = 30;
        botao_menos[k].width = 30;
        
        botao_mais[k].height = 30;
        botao_menos[k].height = 30;
        
        pos_y_carrinho += 101;
        
        
    }
    pos_x_carrinho = 425;
    pos_y_carrinho = 220;
    
    for(int t = 0; t < 5; t++)
    {
        
        botao_excluir[t].x = pos_x_carrinho;
        botao_excluir[t].y = pos_y_carrinho;
        botao_excluir[t].width = 120;
        botao_excluir[t].height = 40;
        
        pos_y_carrinho += 101;
        quantidade_produtos[t] = 1;
    }
    
    
    
}

static void comprar(Rectangle button_comprar, int id_real)
{
    if(CheckCollisionPointRec(GetMousePosition(),button_comprar))
            {
                DrawRectangleLines(button_comprar.x, button_comprar.y, button_comprar.width, button_comprar.height, ORANGE);

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if(n_compras < 5)
                    {
                        if(id_real == contar_id[contador_id])
                        {
                            n_compras = n_compras;
                        }
                        else if(id_real != contar_id[contador_id])
                        {
                            for(int j = 0; j < 5; j++)
                            {
                                if(id_real == contar_id[j])
                                {
                                    return;
                                }
                            
                            }
                            if(produto[id_real].estoque > 0)
                            {
                                n_compras++;
                                contar_id[contador_id] = id_real;
                                contador_id++;
                            }
                           
                        }
                       
                    }
                }
            }
            
    
}

static void desenhar_compra()
{
    
    for(int j = 0; j < n_compras; j++)
    {
        
        DrawRectangleRec(grid_carrinho[j], WHITE);
        DrawRectangleLines(grid_carrinho[j].x, grid_carrinho[j].y, grid_carrinho[j].width, grid_carrinho[j].height, DARKGRAY);
        DrawRectangleRec(botao_mais[j], DARKGREEN);
        DrawRectangleRec(botao_menos[j], MAROON);
        DrawRectangleRec(botao_excluir[j], MAROON);
        
        DrawText(produto[contar_id[j]].nome_produto, grid_carrinho[j].x + 20, grid_carrinho[j].y + 50 - 12, 22, BLACK);
        DrawText(TextFormat("R$%i",produto[contar_id[j]].preco * quantidade_produtos[j]), grid_carrinho[j].x + 950, grid_carrinho[j].y + 50, 25, BLACK);
        DrawText(TextFormat("%i",quantidade_produtos[j]), grid_carrinho[j].x + 780, grid_carrinho[j].y + 50 , 25, BLACK);
        DrawText("Quantidade", grid_carrinho[j].x + 742, grid_carrinho[j].y + 10, 18, BLACK);
        DrawText("Preço", grid_carrinho[j].x + 978, grid_carrinho[j].y + 10, 18, BLACK);
        DrawText(FormatText("R$%i", preco_total), 765, 130, 23, BLACK);
        DrawText("+", botao_mais[j].x + 10, botao_mais[j].y + 7, 20, WHITE);
        DrawText("-", botao_menos[j].x + 10, botao_menos[j].y + 7, 20, WHITE);
        DrawText("Remover", botao_excluir[j].x + 20, botao_excluir[j].y + 10, 20, WHITE);
        
        preco_total_produto[j] = produto[contar_id[j]].preco * quantidade_produtos[j];
        preco_total = preco_total_produto[0] + preco_total_produto[1] + preco_total_produto[2] + preco_total_produto[3] + preco_total_produto[4];
        
        //Checa o toque no botão +
        if(CheckCollisionPointRec(GetMousePosition(), botao_mais[j]))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if(quantidade_produtos[j] < produto[contar_id[j]].estoque)
                {
                quantidade_produtos[j]++; 
                }                
  
            }
        }
         //Checa o toque no botão -
        if(CheckCollisionPointRec(GetMousePosition(), botao_menos[j]))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if(quantidade_produtos[j] > 1)
                {
                quantidade_produtos[j]--;
                }

            }
        }
        //Checa o toque no botão remover
        if(CheckCollisionPointRec(GetMousePosition(), botao_excluir[j]))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
             n_compras--;
             preco_total_produto[n_compras] = 0;
             quantidade_produtos[n_compras] = 1;
             contar_id[n_compras] = 0;
             contador_id--;
            }
        }
        
    }
    
}

static void finalizar_compra(int* p_opcao, char* error_mensagem)
{
  if(n_compras > 0)
  {
    for(int g = 0; g < n_compras; g++)
    {
        if(quantidade_produtos[g] == 0)
        {
            strcpy(error_mensagem,"A quantidade do produto não pode ser 0");
            return;
        }
        
    }
    
    for(int h = 0; h < n_compras; h++)
    {
      produto[contar_id[h]].estoque -= quantidade_produtos[h];
    }
    
    *p_opcao = 6;
  }
  else
  {
      strcpy(error_mensagem,"Não há nenhum produto no carrinho");
  }
    
   n_pedido = 10000 + rand() % 100001;
}

static void printar_itens_comprados()
{
    for(int j = 0; j < n_compras; j++)
    {
        
        DrawRectangleRec(grid_carrinho[j], WHITE);
        DrawRectangleLines(grid_carrinho[j].x, grid_carrinho[j].y, grid_carrinho[j].width, grid_carrinho[j].height, DARKGRAY);
        
        DrawText(produto[contar_id[j]].nome_produto, grid_carrinho[j].x + 20, grid_carrinho[j].y + 50 - 12, 22, BLACK);
        DrawText(TextFormat("R$%i",produto[contar_id[j]].preco * quantidade_produtos[j]), grid_carrinho[j].x + 950, grid_carrinho[j].y + 50, 25, BLACK);
        DrawText(TextFormat("%i",quantidade_produtos[j]), grid_carrinho[j].x + 780, grid_carrinho[j].y + 50 , 25, BLACK);
        DrawText("Quantidade", grid_carrinho[j].x + 742, grid_carrinho[j].y + 10, 18, BLACK);
        DrawText("Preço", grid_carrinho[j].x + 978, grid_carrinho[j].y + 10, 18, BLACK);
        DrawText(FormatText("Valor total a pagar: R$ %i", preco_total), 755, 150, 20, BLACK);
        DrawText(FormatText("N° PEDIDO: %li", n_pedido), 20, 85, 20, WHITE);
        
        preco_total_produto[j] = produto[contar_id[j]].preco * quantidade_produtos[j];
        preco_total = preco_total_produto[0] + preco_total_produto[1] + preco_total_produto[2] + preco_total_produto[3] + preco_total_produto[4];
    }
}

static void atualizar_arquivo_pos_compra()
{
    int id_real;
    
    int estoque;
    int preco;
    int contador = 0;
    int produtos_comprados = 0;

    char nome_produto[40];
    char descricao_produto[200];
    
    FILE* arquivo;
    arquivo = fopen("Data\\products_list.cfg", "r");
    
    FILE* new_arquivo;
    new_arquivo = fopen("Data\\products_list_temp.cfg", "w");
    fclose(new_arquivo);
    
    new_arquivo = fopen("Data\\products_list_temp.cfg", "a");
    
    FILE* arq_prod_admin;
    arq_prod_admin = fopen("Data\\request_list.cfg", "a");
    
    if(arq_prod_admin == NULL)
    {
        fclose(arq_prod_admin);
        arq_prod_admin = fopen("Data\\request_list.cfg", "w");
    }
    
    while(!feof(arquivo))
    {
        fscanf(arquivo, "%d -%s -%d -%d -%s\n", &id_real, nome_produto, &estoque, &preco, descricao_produto);
        contador++;
        destratar_string(produto[contador].nome_produto);
        
        if(strcmp(nome_produto, produto[contador].nome_produto) == 0 && produto[contador].estoque != estoque)
        {
            fprintf(new_arquivo, "%d -%s -%d -%d -%s\n", id_real, nome_produto, produto[contador].estoque, preco, descricao_produto);
            fprintf(arq_prod_admin, "%li -%s -%d -%d -%s -%d\n", n_pedido, set_usuario(), id_real, quantidade_produtos[produtos_comprados], nome_produto, preco_total_produto[produtos_comprados]);
            produtos_comprados++;
        }
        else
        {
            fprintf(new_arquivo, "%d -%s -%d -%d -%s\n", id_real, nome_produto, estoque, preco, descricao_produto);
        }
        
    }
    fclose(arquivo);
    fclose(new_arquivo);
    fclose(arq_prod_admin);
    remove("Data\\products_list.cfg");
    rename("Data\\products_list_temp.cfg", "Data\\products_list.cfg");
    
    
}

static void gerar_comprovante()
{
    FILE* arquivo;
    arquivo = fopen("Comprovante de compra.txt", "w");
    
    fprintf(arquivo,"NOME: %s\nN°PEDIDO: %li\nVALOR TOTAL DA NOTA: R$ %i\n\nPRODUTOS COMPRADOS:\n", set_user_name(), n_pedido, preco_total);
    
    int contador_t = 0;
    
    for(;contador_t < n_compras; contador_t++)
    {
        fprintf(arquivo,"%s %dU R$%d\n", produto[contar_id[contador_t]].nome_produto,quantidade_produtos[contador_t], preco_total_produto[contador_t]);
       
    }
    
    fclose(arquivo);
    
}


  

 


