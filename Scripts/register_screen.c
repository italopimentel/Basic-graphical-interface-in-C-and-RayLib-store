#include <raylib.h>
#include "aux_library.c"
#include <string.h>

    //Cria um retângulo(x,y,largura,altura)
    Rectangle Nome_c = {25,50,400,40};
    Rectangle Cpf = {25, 140,200,40};
    Rectangle Data_n = {275,140,150,40};
    Rectangle Login = {25,230,190,40};
    Rectangle Senha = {235,230,190,40};
    Rectangle Rua = {25, 320,400,40};
    Rectangle Bairro = {25, 410,240,40};
    Rectangle Cep = {290, 410,135,40};
    Rectangle Cidade = {25, 500,200,40};
    Rectangle Cadastrar = {300, 500, 120, 40};
    
    Rectangle Default_button = {300,500,1,1};
    Rectangle Voltar = {300, 550, 120, 40};
    
    
    char nome_c[30] = "";
    char fake_nome_c[30] = "";
    char cpf[13] = "";
    char data_n[11] = "";
    char rua[41] = "";
    char fake_rua[41] = "";
    char cep[10] = "";
    char cidade[25] = "";
    char fake_cidade[25] = "";
    char bairro[15] = "";
    char fake_bairro[15] = "";
    char senha[10] = "";
    char usuario[16] = "";
    char error_message[40] = "";
    
    char masked_senha[10] = "";
    
    bool on_off = true;
    bool* p_on_off = &on_off;
    
    bool retornar_para_login = false;
    
static void Cadastro_do_usuario(char* user_user, char* password, char* nome_c, char* cpf, char* data_n, char*rua, char* cep, char* cidade, char* bairro,char* Error_message)
{
    
bool usuario_cadastrado = false;

FILE* arquivo;
arquivo = fopen("Data\\user_list.cfg", "r");

char user_aux[20] = "";
char senha_aux[16] = "";
char nome_c_aux [40] = "";
char cpf_aux[14] = "";

while(!feof(arquivo))
{
    fscanf(arquivo, "%s -%s -%s -%s\n", user_aux, senha_aux, nome_c_aux, cpf_aux);
    
    if(strcmp(user_user, user_aux) == 0)
    {
        strcpy(Error_message,"Usuário já cadastrado");
        fclose(arquivo);
        usuario_cadastrado = true;
        return;
    }
    else if (strcmp(cpf,cpf_aux) == 0)
    {
        strcpy(Error_message,"Já existe uma conta com esse cpf");
        fclose(arquivo);
        usuario_cadastrado = true;
        return;
    }
    
}
fclose(arquivo);

if (usuario_cadastrado == false)
{
    
    if(strcmp(user_user, "") != 0 && strcmp(password, "") != 0 && strcmp(nome_c, "") != 0 && strcmp(cpf,"") != 0 && strcmp(data_n,"") != 0 && strcmp(rua, "") != 0 && strcmp(cep, "") != 0 && strcmp(cidade, "") != 0 && strcmp(bairro, "") != 0)
    {
        FILE* archive;
        archive = fopen("Data\\user_list.cfg", "a");
        fprintf(archive,"%s -%s -%s -%s -%s -%s -%s -%s -%s\n", user_user, password, nome_c, cpf, data_n, rua, bairro, cidade, cep);
        fclose(archive);
        strcpy(Error_message, "Usuário cadastrado com sucesso!");
        
        strcpy(user_user,""); strcpy(password,""); strcpy(nome_c,""); strcpy(cpf,""); strcpy(data_n,""); strcpy(rua,""); strcpy(bairro,""); strcpy(cidade,""); strcpy(cep,"");
        strcpy(masked_senha, ""); strcpy(fake_bairro, ""); strcpy(fake_cidade, ""); strcpy(fake_nome_c, ""); strcpy(fake_rua, "");
        return;
    }
    else
    {
        strcpy(Error_message, "Campos obrigratórios não preenchidos!");
        return;
    }
}
}
       

static void cadastro_screen()
{ 

    while(retornar_para_login == false)
    {
 
        //Inicia o processo gráfico
        BeginDrawing();
        
            ClearBackground(MAROON);
            //Função que desenha o retângulo
            DrawRectangleRec(Nome_c, WHITE);
            DrawRectangleRec(Cpf, WHITE);
            DrawRectangleRec(Data_n, WHITE);
            DrawRectangleRec(Login, WHITE);            
            DrawRectangleRec(Senha, WHITE);
            DrawRectangleRec(Rua, WHITE);
            DrawRectangleRec(Bairro, WHITE);
            DrawRectangleRec(Cep, WHITE);
            DrawRectangleRec(Cidade, WHITE);
            DrawRectangleRec(Cadastrar, WHITE);
            DrawRectangleRec(Voltar, WHITE);

            //Desenha o envoltório do retângulo
            DrawRectangleLines(Nome_c.x, Nome_c.y, Nome_c.width, Nome_c.height, BLACK);
            DrawRectangleLines(Cpf.x, Cpf.y, Cpf.width, Cpf.height, BLACK);
            DrawRectangleLines(Data_n.x, Data_n.y, Data_n.width, Data_n.height, BLACK);
            DrawRectangleLines(Login.x, Login.y, Login.width, Login.height, BLACK);
            DrawRectangleLines(Senha.x, Senha.y, Senha.width, Senha.height, BLACK);
            DrawRectangleLines(Rua.x, Rua.y, Rua.width, Rua.height, BLACK);
            DrawRectangleLines(Bairro.x, Bairro.y, Bairro.width, Bairro.height, BLACK);
            DrawRectangleLines(Cep.x, Cep.y, Cep.width, Cep.height, BLACK);
            DrawRectangleLines(Cidade.x, Cidade.y, Cidade.width, Cidade.height, BLACK);
            DrawRectangleLines(Cadastrar.x, Cadastrar.y, Cadastrar.width, Cadastrar.height, BLACK);
            DrawRectangleLines(Voltar.x, Voltar.y, Voltar.width, Voltar.height, BLACK);

            //Desenha um texto na tela
            DrawText("Nome completo:", Nome_c.x, Nome_c.y - 15, 15, WHITE);
            DrawText("CPF:", Cpf.x, Cpf.y - 15, 15, WHITE);
            DrawText("Data de nascimento:", Data_n.x, Data_n.y - 15, 15, WHITE);
            DrawText("Nome de usuário:", Login.x, Login.y - 15, 15, WHITE);
            DrawText("Senha:", Senha.x, Senha.y - 15, 15, WHITE);            
            DrawText("Rua:", Rua.x, Rua.y - 15, 15, WHITE);
            DrawText("Bairro:", Bairro.x, Bairro.y - 15, 15, WHITE);
            DrawText("CEP:", Cep.x, Cep.y - 15, 15, WHITE);
            DrawText("Cidade/UF:", Cidade.x, Cidade.y - 15, 15, WHITE);
            DrawText("Cadastrar", Cadastrar.x + 10, Cadastrar.y + 10, 20, BLACK);
            DrawText("Voltar", Voltar.x + 27.5, Voltar.y + 10, 20, BLACK);
            
            DrawText(fake_nome_c, Nome_c.x + 5, Nome_c.y + 15, 20, BLACK);
            DrawText(cpf, Cpf.x + 5, Cpf.y + 15, 20, BLACK);
            DrawText(data_n, Data_n.x + 5, Data_n.y + 15, 20, BLACK);
            DrawText(usuario, Login.x + 5, Login.y + 15, 20, BLACK);
            DrawText(masked_senha, Senha.x + 5, Senha.y + 15, 20, BLACK);
            DrawText(fake_rua, Rua.x + 5, Rua.y + 15, 20, BLACK);
            DrawText(fake_bairro, Bairro.x + 5, Bairro.y + 15, 20, BLACK);
            DrawText(cep, Cep.x + 5, Cep.y + 15, 20, BLACK);
            DrawText(fake_cidade, Cidade.x + 5, Cidade.y + 15, 20, BLACK);
            
            DrawText(error_message, Cidade.x, Cidade.y + 60, 12, BLACK);
            
            Check_if_is_on_textbox_space(Nome_c, nome_c,fake_nome_c, 8, 30);
            Check_if_is_on_textbox(Cpf, cpf, 9, 11);
            Check_if_is_on_textbox(Data_n, data_n, 10, 10);
            Check_if_is_on_textbox(Login, usuario, 11, 10);
            Masked_textbox(Default_button, Senha, senha, masked_senha, p_on_off, 12, 8);
            Check_if_is_on_textbox_space(Rua, rua, fake_rua, 13, 40);
            Check_if_is_on_textbox(Cep, cep, 14, 8);
            Check_if_is_on_textbox_space(Cidade, cidade,fake_cidade, 15, 25); 
            Check_if_is_on_textbox_space(Bairro, bairro, fake_bairro, 16, 15);
            
            //Colisão do botão cadastrar
            if(CheckCollisionPointRec(GetMousePosition(), Cadastrar))
            {
                DrawRectangleLines(Cadastrar.x, Cadastrar.y, Cadastrar.width, Cadastrar.height, ORANGE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Cadastro_do_usuario(usuario, senha, nome_c, cpf, data_n, rua, cep, cidade, bairro, error_message);
                }
            }
            
            //Colisão do botão voltar
            if(CheckCollisionPointRec(GetMousePosition(), Voltar))
            {
                DrawRectangleLines(Voltar.x, Voltar.y, Voltar.width, Voltar.height, ORANGE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    retornar_para_login = true;
                }
            }

        //Termina o processo gráfico
        EndDrawing();

    }
    retornar_para_login = false;
}
