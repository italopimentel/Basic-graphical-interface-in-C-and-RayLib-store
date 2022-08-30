#include <stdio.h>
#include <string.h>
#include <raylib.h>

#ifndef products.c
#define products.c


static void gerar_lista_produtos()
{

  FILE *arquivo;
  arquivo = fopen("Data\\products_list.cfg", "r");
 
  if (arquivo == NULL)
  {
    arquivo = fopen("Data\\products_list.cfg", "w");
    fclose(arquivo);
  }

  fclose(arquivo);

}

static void add_produto(char* id, char* nome_do_produto, char* estoque, char* preco_do_prod, char* ficha_tec_prod, char* mensagem)
{
  char aux_id[4] = "";
  bool cadastrado = false;
  FILE* arquivo;
  arquivo = fopen("Data\\products_list.cfg", "r");
  
  while(!feof(arquivo))
  {
      fscanf(arquivo, "%s\n", aux_id);
      
      if(strcmp(aux_id,id) == 0)
      {
          fclose(arquivo);
          cadastrado = true;
          strcpy(mensagem,"Produto já cadastrado");
          return;
      }
  }
  
  if(cadastrado == false)
  {
    fclose(arquivo);
    
    arquivo = fopen("Data\\products_list.cfg", "a");

    fprintf(arquivo,"%s -%s -%s -%s -%s\n", id, nome_do_produto, estoque, preco_do_prod, ficha_tec_prod);

    fclose(arquivo);

    strcpy(mensagem,"Produto cadastrado com sucesso!");

    return;
    }

}

static void modif_produto(char* id, char* nome_do_produto, char* estoque, char* preco_do_prod, char* ficha_tec_prod, char* mensagem)
{
    char aux_nome_do_produto[20] = "";
    char aux_estoque[10] = "";
    char aux_preco_do_prod[6] = "";
    char aux_ficha_tec_prod[100] = "";
    char aux_id[5] = "";
    
  FILE *arquivo;
  arquivo = fopen("Data\\products_list.cfg", "r+");
    
  FILE *new_arquivo;
  new_arquivo = fopen("Data\\products_list_temporally.cfg", "w");
  fclose(new_arquivo);

  new_arquivo = fopen("Data\\products_list_temporally.cfg", "a");
  
  while(!feof(arquivo))
  {
     fscanf(arquivo,"%s -%s -%s -%s -%s\n", aux_id, aux_nome_do_produto, aux_estoque, aux_preco_do_prod, aux_ficha_tec_prod);
     if(strcmp(aux_id,id) == 0)
    {
        fprintf(new_arquivo,"%s -%s -%s -%s -%s\n", id, nome_do_produto, estoque, preco_do_prod, ficha_tec_prod);
        strcpy(mensagem,"Produto modificado com sucesso!");
    }
    else if (strcmp(aux_id,id) != 0)
    {
      fprintf(new_arquivo,"%s -%s -%s -%s -%s\n", aux_id, aux_nome_do_produto, aux_estoque, aux_preco_do_prod, aux_ficha_tec_prod);
    }
  }
  
  fclose(arquivo);
  fclose(new_arquivo);
  remove("Data\\products_list.cfg");
  rename("Data\\products_list_temporally.cfg","Data\\products_list.cfg");

  return;
  
}

static void carregar_produto(char* id, char* nome_do_produto, char* estoque, char* preco_do_prod, char* ficha_tec_prod)
{
    FILE* arquivo;
    arquivo = fopen("Data\\products_list.cfg", "r");
    
    char aux_nome_do_produto[20] = "";
    char aux_estoque[10] = "";
    char aux_preco_do_prod[6] = "";
    char aux_ficha_tec_prod[100] = "";
    char aux_id[5] = ""; 
    
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s -%s -%s -%s -%s\n", aux_id, aux_nome_do_produto, aux_estoque, aux_preco_do_prod, aux_ficha_tec_prod);
        
        if(strcmp(aux_id,id) == 0)
        {
            strcpy(id,aux_id); strcpy(nome_do_produto,aux_nome_do_produto); strcpy(estoque,aux_estoque); strcpy(preco_do_prod,aux_preco_do_prod); strcpy(ficha_tec_prod, aux_ficha_tec_prod); 
        }
    }
    
    fclose(arquivo);
    return;
    
}

static void excluir_produto(char* id, char* mensagem)
{
    
    char aux_nome_do_produto[20] = "";
    char aux_estoque[10] = "";
    char aux_preco_do_prod[6] = "";
    char aux_ficha_tec_prod[100] = "";
    char aux_id[5] = "";

  FILE *arquivo;
  arquivo = fopen("Data\\products_list.cfg", "r+");
    
  FILE *new_arquivo;
  new_arquivo = fopen("Data\\products_list_temporally.cfg", "w");
  fclose(new_arquivo);

  new_arquivo = fopen("Data\\products_list_temporally.cfg", "a");
  
  while(!feof(arquivo))
  {
     fscanf(arquivo,"%s -%s -%s -%s -%s\n", aux_id, aux_nome_do_produto, aux_estoque, aux_preco_do_prod, aux_ficha_tec_prod);
     
     if(strcmp(id,aux_id) != 0)
     {
        fprintf(new_arquivo,"%s -%s -%s -%s -%s\n", aux_id, aux_nome_do_produto, aux_estoque, aux_preco_do_prod, aux_ficha_tec_prod);
        strcpy(mensagem, "Produto excluído com sucesso!");
     }
     
  }
  
  fclose(arquivo);
  fclose(new_arquivo);
  remove("Data\\products_list.cfg");
  rename("Data\\products_list_temporally.cfg","Data\\products_list.cfg");
  return;
}

static void carregar_usuario (char* cpf, char* nome_c, char* data_nascimento, char* mensagem)
{
    char aux_usuario[20] = "";
    char aux_senha[12] = "";
    char aux_nome_c[50] = "";
    char aux_cpf[14] = "";
    char aux_data_nascimento[13] = "";
    
    FILE* arquivo;
    arquivo = fopen("Data\\user_list.cfg", "r");

    
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s -%s -%s -%s -%s\n", aux_usuario, aux_senha, aux_nome_c, aux_cpf, aux_data_nascimento);
        
        if(strcmp(aux_cpf, cpf) == 0)
        {
            strcpy(cpf, aux_cpf); strcpy(nome_c, aux_nome_c); strcpy(data_nascimento, aux_data_nascimento);  
            fclose(arquivo);
            return;
        }
    }
    
    strcpy(mensagem, "CPF não cadastrado");
    fclose(arquivo);
    return;
    
}

static void excluir_usuario(char* cpf, char* nome_c, char* data_nascimento, char* mensagem)
{
    char aux_usuario[20] = "";
    char aux_senha[12] = "";
    char aux_nome_c[50] = "";
    char aux_cpf[14] = "";
    char aux_data_nascimento[13] = "";
    char aux_rua[40] ="";
    char aux_bairro[20] = "";
    char aux_cidade[20] = "";
    char aux_cep[12] = "";
    
    
  FILE *arquivo;
  arquivo = fopen("Data\\user_list.cfg", "r+");
    
  FILE *new_arquivo;
  new_arquivo = fopen("Data\\user_list_temporally.cfg", "w");
  fclose(new_arquivo);

  new_arquivo = fopen("Data\\user_list_temporally.cfg", "a");
  
  while(!feof(arquivo))
  {
      fscanf(arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, aux_senha, aux_nome_c, aux_cpf, aux_data_nascimento, aux_rua, aux_bairro, aux_cidade, aux_cep);
     
     if(strcmp(aux_cpf, cpf) != 0)
     {
         fprintf(new_arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, aux_senha, aux_nome_c, aux_cpf, aux_data_nascimento, aux_rua, aux_bairro, aux_cidade, aux_cep);
     }
     else
     {
        strcpy(mensagem, "Cadastro excluído com sucesso!");
     }
     
   }
  
  fclose(arquivo);
  fclose(new_arquivo);
  remove("Data\\user_list.cfg");
  rename("Data\\user_list_temporally.cfg","Data\\user_list.cfg");
}

static void printar_pedidos()
{
    int n_pedido;
    char usuario_print[16];
    int id_real;
    int quantidade_prod;
    char nome_poduto[30];
    int preco_produto_print;
    int contador = 0;
    
    FILE* arquivo;
    arquivo = fopen("Data\\request_list.cfg", "r+");
  
    int pos_x = 20;
    int pos_y = 130;
    
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%d -%s -%d -%d -%s -%d\n", &n_pedido, usuario_print, &id_real, &quantidade_prod, nome_poduto, &preco_produto_print);
        contador++;
    }
    
    fseek(arquivo, 0, SEEK_SET);
    
    for(int i = 0; i < contador; i++)
    {
        fscanf(arquivo,"%d -%s -%d -%d -%s -%d\n", &n_pedido, usuario_print, &id_real, &quantidade_prod, nome_poduto, &preco_produto_print);
        DrawText("N°Pedido", pos_x, 100, 15, BLACK); DrawText("Usuario", pos_x + 80, 100, 15, BLACK); DrawText("ID", pos_x + 165, 100, 15, BLACK); DrawText("U", pos_x + 200, 100, 15, BLACK); DrawText("Nome do produto", pos_x + 230, 100, 15, BLACK); DrawText("Preço", pos_x + 420, 100, 15, BLACK); 
        DrawText(FormatText("%d", n_pedido), pos_x, pos_y, 20, BLACK);
        DrawText(usuario_print, pos_x + 80, pos_y, 20, BLACK);
        DrawText(FormatText("%d", id_real), pos_x + 165, pos_y, 20, BLACK);
        DrawText(FormatText("%d", quantidade_prod), pos_x + 200, pos_y, 20, BLACK);
        DrawText(nome_poduto, pos_x + 230, pos_y, 20, BLACK);
        DrawText(FormatText("%dR$", preco_produto_print), pos_x + 420, pos_y, 20, BLACK);
        pos_y += 30;
    }
    fclose(arquivo);
    
}
  
#endif /* products.c */