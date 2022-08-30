#include <raylib.h>
#include <string.h>

#ifndef user_info.c
#define user_info.c

char login_usuario[16] = "";
char nome_c_usuario[50] = "";

static char* get_user_name(char* nome_c)
{
  strcpy(nome_c_usuario,nome_c);
}

static char* get_usuario(char* login)
{
  strcpy(login_usuario,login);
}

static char* set_user_name()
{
    int n_caracteres = strlen(nome_c_usuario);
    
    
    for(int i = 0; i < n_caracteres; i++)
    {
        if(nome_c_usuario[i] == '_')
        {
           nome_c_usuario[i] = ' ';
        }
    }
    
   return  nome_c_usuario;
}

static char* set_usuario()
{ 
   return  login_usuario;
}

static void tratar_string(char* string)
{
    int tamanho = strlen(string);
    
    for(int i = 0; i < tamanho; i++)
    {
        if(string[i] == '_')
        {
           string[i] = ' ';
        }
    }
    
}

static void destratar_string(char* string)
{
    int tamanho = strlen(string);
    
    for(int i = 0; i < tamanho; i++)
    {
        if(string[i] == ' ')
        {
           string[i] = '_';
        }
        else if(string[i] == '\n')
        {
            string[i] = ' ';
        }
    }
    
}

#endif /* user_info.c */