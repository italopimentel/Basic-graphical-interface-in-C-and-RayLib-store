#include <raylib.h>
#include "aux_library.c"
#include "user.c"
#include "register_screen.c"
#include <string.h>
#include <stdio.h>

//Gera o arquivo que mostra os usuarios cadastrados, caso não exista na memória
static void gerar_arquivo(){
    
    FILE* arquivo;
    arquivo = fopen("Data\\user_list.cfg", "r");
    
    if(arquivo == NULL)
    {
        arquivo = fopen("Data\\user_list.cfg", "w");
        fclose(arquivo);
    }
    
    fclose(arquivo);
    
}


static void login_screen(){
    
    //Cria váriaveis responsáveis pelo tamanho da janela
    const int WindowWidth = 450;
    const int WindowHeight = 600;
    //Função que Cria uma janela
    InitWindow(WindowWidth,WindowHeight,"Aplicativo");
    //Define a quantidade de FPS
    SetTargetFPS(60);
    
    char user_text[16] = "";
    char password_text[9] = "";
    char masked_password_text[9] = "";
    char Error_Message[50] = "";
    
    int option = 1;
    int* p_option = &option;
    
    bool password_switch = false;
    bool* p_password_switch = &password_switch;
    
    //Struct Retangulo{x, y, width, height}
    Rectangle Login_Text = {20, 220, 400, 40};
    Rectangle Password_Text = {20, 300, 400, 40};
    
    Rectangle Login_Button = {WindowWidth/2 - 90, 400, 180, 40};
    Rectangle Register_Button = {WindowWidth/2 - 90, 460, 180, 40};
    Rectangle Show_Password = {Password_Text.x + 370, Password_Text.y + 10, 20, 20};
    
    Rectangle Forgot_Password = {260,Password_Text.y + 50, 160, 20};
    
    //Change Password Screen Variables
    /********************************************************************************************************************************/
    Rectangle User_CPF = {20,160, 180, 40};
    Rectangle User_User = {20,90, 250, 40};
    Rectangle User_BirthDay = {220,160, 180, 40};
    Rectangle User_NewPassword = {20,230, 250, 40};
    Rectangle User_RepitNewPassword = {20,300, 250, 40};
    
    Rectangle Apply_Button = {WindowWidth/2 - 90,400, 180,40};
    Rectangle Return_Button = {WindowWidth/2 - 90,470, 180,40};
    
    Rectangle Default_button = {250,350,25,2};
    
    
    // Varáveis tela de recadastro
    char cpf[13] = "";
    char usuario[16]= "";
    char data_de_nascimento[13] = "";
    char nova_senha[12] = "";
    char repetir_senha[12] = "";
    
    char masked_nova_senha[12] = "";
    char masked_repetir_senha[12] = "";
    
    char error_message[40] = "";
    
    bool on_off = false;
    bool* p_on_off = &on_off;
    
    
    while(!WindowShouldClose()){
        
        switch(option)
        {
        //Tela princpal
        case 1: 
            
            BeginDrawing();
                ClearBackground(MAROON);
                
                
                //Desenha Texto na tela
                DrawText("Bem vindo a Loja Online", 45, 100, 30, WHITE);
                DrawText("Usuário :", Login_Text.x , Login_Text.y -20, 15, RAYWHITE);
                DrawText("Senha :", Password_Text.x , Password_Text.y -20, 15, RAYWHITE);
                
                //Desenha um retangulo na tela
                DrawRectangleRec(Login_Text, WHITE);
                DrawRectangleRec(Password_Text, WHITE);
                DrawRectangleRec(Login_Button, WHITE);
                DrawRectangleRec(Register_Button, WHITE);
                
                if(password_switch == true){
                    DrawRectangleRec(Show_Password, GREEN);
                    DrawText(password_text, Password_Text.x + 8, Password_Text.y + 15, 20, BLACK);
                }
                else{
                   DrawRectangleRec(Show_Password, WHITE); 
                   DrawText(masked_password_text, Password_Text.x + 8, Password_Text.y + 15, 20, BLACK);
                }
                
                DrawRectangleRec(Forgot_Password, MAROON);
                
                //Desenha um envoltório do retangulo
                DrawRectangleLines(Login_Text.x, Login_Text.y, Login_Text.width ,Login_Text.height, BLACK);
                DrawRectangleLines(Password_Text.x, Password_Text.y, Password_Text.width ,Password_Text.height, BLACK);
                DrawRectangleLines(Login_Button.x, Login_Button.y, Login_Button.width, Login_Button.height, BLACK);
                DrawRectangleLines(Register_Button.x, Register_Button.y, Register_Button.width, Register_Button.height, BLACK);
                DrawRectangleLines(Show_Password.x, Show_Password.y, Show_Password.width, Show_Password.height, BLACK);
                
                //Desenha os textos dos botões
                DrawText("Logar",(Login_Button.x + (Login_Button.width /2 - 25)), (Login_Button.y + (Login_Button.height/2 -10)), 20, BLACK);
                DrawText("Registrar",(Register_Button.x + (Register_Button.width /2 - 42.5)), (Register_Button.y + (Register_Button.height/2 -10)), 20, BLACK);
                DrawText(user_text, Login_Text.x + 8, Login_Text.y + 15, 20, BLACK);
                DrawText(Error_Message, Password_Text.x, Password_Text.y + 52, 15, BLACK);
                DrawText("Esqueci minha senha", Forgot_Password.x + 5, Forgot_Password.y + 2, 16, BLACK);
                
                Check_if_is_on_textbox(Login_Text, user_text, 0, 15);
                Masked_textbox(Show_Password, Password_Text, password_text, masked_password_text, p_password_switch, 1, 8);
                Check_if_is_buttonpressed_switch(Register_Button, p_option, 2);
                Check_if_is_buttonpressed_switch(Forgot_Password, p_option, 3);
                
                //Ação do botão de login
                if(CheckCollisionPointRec(GetMousePosition(), Login_Button))
                {
                    DrawRectangleLines(Login_Button.x, Login_Button.y, Login_Button.width, Login_Button.height, ORANGE);
                    
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        login(user_text, password_text, Error_Message);
                    }
                }
                
            EndDrawing();
            break;
            
            //Tela de cadastro
            case 2:
                
                cadastro_screen();
                *p_option = 1;
                      
            break;
                
            //Tela de alterar senha
            case 3 :
                
            
                BeginDrawing();
                ClearBackground(MAROON);
                    
                //Campo dos Text_box
                DrawRectangleRec(User_User, WHITE);
                DrawRectangleRec(User_CPF, WHITE);
                DrawRectangleRec(User_BirthDay, WHITE);
                DrawRectangleRec(User_NewPassword, WHITE);
                DrawRectangleRec(User_RepitNewPassword, WHITE);
                DrawRectangleRec(Apply_Button, WHITE);
                DrawRectangleRec(Return_Button, WHITE);
                
                //Contorno do textobox
                DrawRectangleLines(User_User.x, User_User.y, User_User.width, User_User.height, BLACK);
                DrawRectangleLines(User_CPF.x, User_CPF.y, User_CPF.width, User_CPF.height, BLACK);
                DrawRectangleLines(User_BirthDay.x, User_BirthDay.y, User_BirthDay.width, User_BirthDay.height, BLACK);
                DrawRectangleLines(User_NewPassword.x, User_NewPassword.y, User_NewPassword.width, User_NewPassword.height, BLACK);
                DrawRectangleLines(User_RepitNewPassword.x, User_RepitNewPassword.y, User_RepitNewPassword.width, User_RepitNewPassword.height, BLACK);
                DrawRectangleLines(Apply_Button.x, Apply_Button.y, Apply_Button.width, Apply_Button.height, BLACK);
                DrawRectangleLines(Return_Button.x, Return_Button.y, Return_Button.width, Return_Button.height, BLACK);
                
                
                //Campo dos textos
                DrawText("Alterar senha", 20, 30, 30, WHITE);
                DrawText("Usuário: ", User_User.x, User_User.y - 15, 15, WHITE);
                DrawText("CPF:", User_CPF.x, User_CPF.y - 15, 15, WHITE);
                DrawText("Data de nascimento: ", User_BirthDay.x, User_BirthDay.y - 15, 15, WHITE);
                DrawText("Nova senha: ", User_NewPassword.x, User_NewPassword.y - 15, 15, WHITE);
                DrawText("Repitir senha: ", User_RepitNewPassword.x, User_RepitNewPassword.y - 15, 15, WHITE);
                DrawText("Recadastrar", Apply_Button.x + 30, Apply_Button.y + 10, 20, BLACK);
                DrawText("Retornar", Return_Button.x + 45, Return_Button.y + 10, 20, BLACK);
                
                DrawText(usuario, User_User.x + 5, User_User.y +15, 20, BLACK);
                DrawText(cpf, User_CPF.x + 5, User_CPF.y +15, 20, BLACK);
                DrawText(data_de_nascimento, User_BirthDay.x + 5, User_BirthDay.y +15, 20, BLACK);
                DrawText(masked_nova_senha, User_NewPassword.x + 5, User_NewPassword.y +15, 20, BLACK);
                DrawText(masked_repetir_senha, User_RepitNewPassword.x + 5, User_RepitNewPassword.y +15, 20, BLACK);
                DrawText(error_message, User_RepitNewPassword.x, User_RepitNewPassword.y + 60, 20, BLACK);
                
                Check_if_is_buttonpressed_switch(Return_Button, p_option, 1);
                Check_if_is_on_textbox(User_User, usuario, 2, 16);
                Check_if_is_on_textbox(User_CPF, cpf, 3, 11);
                Check_if_is_on_textbox(User_BirthDay, data_de_nascimento, 4, 10);
                Masked_textbox(Default_button, User_NewPassword, nova_senha, masked_nova_senha,p_on_off, 5, 8);
                Masked_textbox(Default_button, User_RepitNewPassword, repetir_senha, masked_repetir_senha, p_on_off, 6, 8);
                
                 if(CheckCollisionPointRec(GetMousePosition(), Apply_Button))
                {
                    DrawRectangleLines(Apply_Button.x, Apply_Button.y, Apply_Button.width, Apply_Button.height, ORANGE);
                    
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        int retorno = alterar_senha(usuario, cpf, data_de_nascimento, nova_senha, repetir_senha, error_message);
                        if(retorno == 0)
                        {
                            strcpy(masked_nova_senha, ""); strcpy(masked_repetir_senha, "");
                            
                        }
                    }
                    
                }
                
                EndDrawing();
            
            break;
        }
    }
    return;
    
}


