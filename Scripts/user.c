#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include "tela_adm.c"
#include "store_screen.c"
#include "user_info.c"

//Define que vários scripts podem abrir esse arquivo
#ifndef user.c
#define user.c

//Funão que verifica se o login digitado é válido ou não
static int login(char* user_text, char* password_text, char* Error_Message)
{
    //Verifica se já foi digitado alguma letra no textbox
    if(strcmp(user_text,"") != 0 && strcmp(password_text,"") != 0)
    {

        char user_aux[16];
        char password_aux[9];
        char nome_c_user[50];
        int id = 0;
        FILE* arquivo;
        arquivo = fopen("Data\\user_list.cfg", "r");
        
        while(!feof(arquivo))
        {
            
            fscanf(arquivo,"%s -%s -%s\n", user_aux, password_aux, nome_c_user);
            
            //Caso o usuário e senha seja igual
            if(strcmp(user_aux, user_text) == 0 && strcmp(password_aux, password_text) == 0)
            {
                fclose(arquivo);
                get_user_name(nome_c_user);
                get_usuario(user_aux);
                CloseWindow();
                store_screen();
                return 0;
            }
            //Caso o usuário exista na lista de cadastrados
            else if(strcmp(user_aux, user_text) == 0 && strcmp(password_aux, password_text) != 0)
            {
                fclose(arquivo);
                strcpy(Error_Message,"Senha incorreta");
                return 1;
            }
            else if(strcmp(user_text,"admin")==0 && strcmp(password_text, "admin") == 0)
            {
                fclose(arquivo);
                CloseWindow();
                interface_admin();                
                return 2;
            }
            
        }
        
        //Caso o usuaio não esteja cadastrado
        
        fclose(arquivo);
        strcpy(Error_Message,"Usuário não cadastrado");
        return 3;
    }
    else
    {
        strcpy(Error_Message,"campos não preenchidos");
        return 4;
    }
   
    
}
//Alterar senha

static int alterar_senha(char* usuario_vetor, char* cpf_vetor , char* data_nasmcimento_vetor ,char* novasenha_vetor, char* repetir_senha_vetor, char* mensagem_erro)
{
    
    char aux_usuario[20] = "";
    char aux_cpf[13] = "";
    char aux_data_nascimento[14] = "";
    char senha_antiga[20];
    char nome_c[40];
    char rua[41];
    char bairro[20];
    char cidade[25];
    char cep[13];

    if(strcmp(usuario_vetor, "") != 0, strcmp(cpf_vetor, "") != 0, strcmp(novasenha_vetor, "") != 0, strcmp(repetir_senha_vetor, "") != 0)
    {

     FILE* arquivo;
     arquivo = fopen("Data\\user_list.cfg", "r");
     
     FILE* new_arquivo;
     new_arquivo = fopen("Data\\user_list_temp.cfg", "w");
     fclose(new_arquivo);
      
     new_arquivo = fopen("Data\\user_list_temp.cfg", "a");
     
     
     while(!feof(arquivo))
     {
         fscanf(arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, senha_antiga ,nome_c ,aux_cpf ,aux_data_nascimento, rua, bairro, cidade, cep);
         
         if(strcmp(aux_usuario,usuario_vetor) == 0 && strcmp(aux_cpf,cpf_vetor) == 0 && strcmp(aux_data_nascimento,data_nasmcimento_vetor) == 0 && strcmp(novasenha_vetor, repetir_senha_vetor) == 0)
         {
             fseek(arquivo, 0, SEEK_SET);
             while(!feof(arquivo))
             {
                 fscanf(arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, senha_antiga ,nome_c ,aux_cpf ,aux_data_nascimento, rua, bairro, cidade, cep);
                 
                 if(strcmp(aux_usuario,usuario_vetor) == 0)
                 {
                     fprintf(new_arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, novasenha_vetor ,nome_c ,aux_cpf ,aux_data_nascimento, rua, bairro, cidade, cep);
                     strcpy(mensagem_erro, "Senha alterada com sucesso!");
 
                 }
                 else
                 {
                     fprintf(new_arquivo,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", aux_usuario, senha_antiga ,nome_c ,aux_cpf ,aux_data_nascimento, rua, bairro, cidade, cep);
                 }
             }
             fclose(arquivo);
             fclose(new_arquivo);
             
             strcpy(usuario_vetor, ""); strcpy(cpf_vetor, ""); strcpy(data_nasmcimento_vetor, ""); strcpy(novasenha_vetor, ""); strcpy(repetir_senha_vetor, ""); 
             
             remove("Data\\user_list.cfg");
             
             rename("Data\\user_list_temp.cfg","Data\\user_list.cfg");
             return 0;
         }
         
         else if(strcmp(aux_usuario,usuario_vetor) == 0 && (strcmp(aux_cpf,cpf_vetor) != 0 || strcmp(aux_data_nascimento,data_nasmcimento_vetor) != 0))
         {
             strcpy(mensagem_erro,"Dados incorretos!");
             fclose(arquivo);
             fclose(new_arquivo);
             return 1;
         }
         else if(strcmp(aux_usuario,usuario_vetor) == 0 && strcmp(novasenha_vetor,repetir_senha_vetor) != 0)
         {
             strcpy(mensagem_erro,"As senhas não coincidem!");
             fclose(arquivo);
             fclose(new_arquivo);
             return 2;
         } 
               
     }
     
        strcpy(mensagem_erro,"usuário não cadastrado!");
        fclose(arquivo);
        fclose(new_arquivo);
        return 3;
       
    }
  
}

#endif /* user.c */