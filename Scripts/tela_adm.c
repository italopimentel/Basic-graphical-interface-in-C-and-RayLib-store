#include <raylib.h>
#include <stdio.h>
#include "aux_library.c"
#include "products.c"

//variavel do switch
  int opcao = 1;
  int* p_opcao = &opcao;
  
  
//varial de cadastro do produto
  char id_produto[5] = "";
  char nome_produto[60] = "";
  char ficha_produto[200] = "";
  char preco_produto[6] = "";
  char estoque_produto[5] = "";
  
 //varial de alterar do produto
  char id_prod_al[5] = "";
  char nome_prod_al[60] = "";
  char ficha_prod_al[200] = "";
  char preco_prod_al[6] = "";
  char estoque_prod_al[5] = "";

//variavel para buscar produto
  char bu_nome_produto[120] = "";

//variavel para banir usuario
  char cpf_cliente[13] = ""; 
  char nome_cliente[40] = "";
  char data_nasc [13] = "";

//variavel para exibir mensagem
  char mensagem_c[30] = "";
  char mensagem_al[30] = "";
  char mensagem_b[30] = "";
  
  Image imagem_produto_tela;
  Texture2D textura_produto_tela;

    static int interface_admin()
    {
        
     const int largura = 600;
     const int altura = 600;


     SetTargetFPS(60);

     //tela do adm

        InitWindow(largura, altura, "Tela de Adiministrador");
        Rectangle cadastro_produtos = {45,120,210,40};
        Rectangle modificar_produtos ={345,120,210,40};
        Rectangle Receber_pedidos ={45,280,210,40};
        Rectangle Banir_usuario ={345,280,210,40};
        Rectangle Logout ={195,450,210,40};

     //tela de cadastro_produtos

        Rectangle id_produto_c ={25,110,100,40};
        Rectangle nome_produto_c ={25,195,550,40};
        Rectangle ficha_produto_c ={25,280,550,80};
        Rectangle preco_produto_c ={25,405,110,40};
        Rectangle estoque_produto_c ={165,405,110,40};
        Rectangle confirmacao_c ={310,530,125,40};
        Rectangle cancelamento_c ={465,530,110,40};

     //tela de alterar produtos

        Rectangle id_produto_al = {50,80,100,40};
        Rectangle nome_produto_al = {25,165,320,80};
        Rectangle imagem_al = {375,30,200,200};
        Rectangle ficha_al = {25,290,550,80};
        Rectangle preco_al = {25,415,100,40};
        Rectangle estoque_al = {155,415,100,40};
        Rectangle lupa_al = {180,80,40,40};
        Rectangle excluir_al = {175,530,115,40};
        Rectangle confirmar_al = {320,530,115,40};
        Rectangle cancelar_al = {465,530,110,40};
        
        Texture2D lupa = LoadTexture("Imagens/lupa 40px.png");

     //tela de receber pedido
     
        Rectangle voltar_r = {440,30,100,40};

     //tela de banir usuário

        Rectangle cpf_ba = {25,110,285,40};
        Rectangle nome_usuario_ba = {25,195,365,40};
        Rectangle data_nasc_ba = {25,280,140,40};
        Rectangle banir_ba = {365,530,70,40};
        Rectangle cancelar_ba = {465,530,110,40};
        Rectangle usuario_lupa_bu = {330,110,40,40};

        Texture2D u_lupa = LoadTexture("Imagens/lupa 40px.png");


     while(!WindowShouldClose())
     {
      switch(opcao)
      {
         //tela admin
        case 1:

         BeginDrawing();

          ClearBackground(MAROON);

          DrawText("Gestão da loja", 25,25,30,BLACK);

          //Desenha os botões 
          DrawRectangleRec(cadastro_produtos,WHITE);
          DrawRectangleRec(modificar_produtos,WHITE);  
          DrawRectangleRec(Receber_pedidos,WHITE);
          DrawRectangleRec(Banir_usuario,WHITE);
          DrawRectangleRec(Logout,WHITE);

          //Desenha txto nos botões
          DrawText("Cadastrar produto",cadastro_produtos.x+7, cadastro_produtos.y+10, 20, BLACK);
          DrawText("Alterar produtos",modificar_produtos.x+7, modificar_produtos.y+10, 20, BLACK);
          DrawText("Receber pedidos",Receber_pedidos.x+20, Receber_pedidos.y+10, 20, BLACK);
          DrawText("Banir usuario",Banir_usuario.x+35, Banir_usuario.y+10, 20, BLACK);
          DrawText("Sair",Logout.x+90, Logout.y+10, 20, BLACK);

          //Verifica qual botão foi precionado
          Check_if_is_buttonpressed_switch(cadastro_produtos, p_opcao, 2);
          Check_if_is_buttonpressed_switch(modificar_produtos, p_opcao, 3);
          Check_if_is_buttonpressed_switch(Receber_pedidos, p_opcao, 4);
          Check_if_is_buttonpressed_switch(Banir_usuario, p_opcao, 5);
          Check_if_is_buttonpressed_switch(Logout, p_opcao, 6);

         EndDrawing();

         break;

         //tela cadastro de produtos
        case 2:

         BeginDrawing();

          ClearBackground(MAROON);

          DrawText("Cadastro de novos produtos", 25,25,30,BLACK);

          //Desenha botões ou caixas de texto
          DrawRectangleRec(id_produto_c,WHITE);
          DrawRectangleRec(nome_produto_c,WHITE);
          DrawRectangleRec(ficha_produto_c,WHITE);
          DrawRectangleRec(preco_produto_c,WHITE);
          DrawRectangleRec(estoque_produto_c,WHITE);
          DrawRectangleRec(confirmacao_c,WHITE);
          DrawRectangleRec(cancelamento_c,WHITE);

          //Desenha titulo das caixas de texto ou texto dos botões
          DrawText("ID",id_produto_c.x,id_produto_c.y-25,20,BLACK);
          DrawText("Nome do produto",nome_produto_c.x,nome_produto_c.y-25,20,BLACK);
          DrawText("Ficha técnica do produto",ficha_produto_c.x,ficha_produto_c.y-25,20,BLACK);
          DrawText("Preço",preco_produto_c.x,preco_produto_c.y-25,20,BLACK);
          DrawText("Estoque",estoque_produto_c.x,estoque_produto_c.y-25,20,BLACK);
          DrawText("Cadastrar",confirmacao_c.x+10,confirmacao_c.y+8,20,BLACK);
          DrawText("Cancelar",cancelamento_c.x+10,cancelamento_c.y+8,20,BLACK);
          DrawText(mensagem_c,25,460,20,BLACK);

          //Checa se o mause esta em uma caixa de texto e mostra o caracter digitado
          Check_if_is_on_textbox(id_produto_c,id_produto,17,4);
          Check_if_is_on_textbox(nome_produto_c,nome_produto,18,119);
          Check_if_is_on_textbox(ficha_produto_c,ficha_produto,19,499);
          Check_if_is_on_textbox(preco_produto_c,preco_produto,20,5);
          Check_if_is_on_textbox(estoque_produto_c,estoque_produto,21,4);
          
          DrawText(id_produto,id_produto_c.x+5,id_produto_c.y+15,20,BLACK);
          DrawText(nome_produto,nome_produto_c.x+5,nome_produto_c.y+15,20,BLACK);
          DrawText(ficha_produto,ficha_produto_c.x+5,ficha_produto_c.y+15,20,BLACK);
          DrawText(preco_produto,preco_produto_c.x+5,preco_produto_c.y+15,20,BLACK);
          DrawText(estoque_produto,estoque_produto_c.x+5,estoque_produto_c.y+15,20,BLACK);

          //Verifica qual botão foi precionado
          Check_if_is_buttonpressed_switch(cancelamento_c, p_opcao, 1);          
          
          //Botão de cadastro do produto
          if(CheckCollisionPointRec(GetMousePosition(),confirmacao_c))
          {
            DrawRectangleLines(confirmacao_c.x,confirmacao_c.y,confirmacao_c.width, confirmacao_c.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              add_produto(id_produto, nome_produto, estoque_produto, preco_produto,ficha_produto, mensagem_c);
              limpar_campo(id_produto,17); limpar_campo(nome_produto,18); limpar_campo(estoque_produto,21); limpar_campo(preco_produto,20); limpar_campo(ficha_produto,19); 

            }
          }

         EndDrawing();

         break;

         //tela de alterar produtos
        case 3:

         BeginDrawing();
          
          ClearBackground(MAROON);
            
          DrawText("Alterar produto", 25,30,30,BLACK);

          //Desenha botões ou caixas de texto
          DrawRectangleRec(id_produto_al,WHITE);
          DrawRectangleRec(imagem_al,WHITE);
          DrawRectangleRec(nome_produto_al,WHITE);
          DrawRectangleRec(ficha_al,WHITE);
          DrawRectangleRec(preco_al,WHITE);
          DrawRectangleRec(estoque_al,WHITE);
          DrawRectangleRec(lupa_al,WHITE);
          DrawRectangleRec(excluir_al,WHITE);
          DrawRectangleRec(confirmar_al,WHITE);
          DrawRectangleRec(cancelar_al,WHITE);
          
          //Desenha titulo das caixas de texto ou texto dos botões
          DrawText("ID",id_produto_al.x-25,id_produto_al.y+5,20,BLACK);
          DrawText("Nome do Produto", nome_produto_al.x,nome_produto_al.y-25,20,BLACK);
          DrawText("Ficha técnica",ficha_al.x,ficha_al.y-25,20,BLACK);
          DrawText("Preço", preco_al.x,preco_al.y-25,20,BLACK);
          DrawText("Estoque", estoque_al.x,estoque_al.y-25,20,BLACK);
          DrawText("Excluir",excluir_al.x+10,excluir_al.y+8,20,BLACK);
          DrawText("Confirmar",confirmar_al.x+10,confirmar_al.y+8,20,BLACK);
          DrawText("Cancelar",cancelar_al.x+10,cancelar_al.y+8,20,BLACK);
          DrawText(mensagem_al,25,475,20,BLACK);
          
          DrawTexture(lupa,lupa_al.x,lupa_al.y,WHITE);

          //Checa se o mause esta em uma caixa de texto e mostra o caracter digitado
          Check_if_is_on_textbox(id_produto_al,id_prod_al,23,5); 
          Check_if_is_on_textbox(nome_produto_al,nome_prod_al,24,119);
          Check_if_is_on_textbox(ficha_al,ficha_prod_al,25,499);
          Check_if_is_on_textbox(preco_al,preco_prod_al,26,5);
          Check_if_is_on_textbox(estoque_al,estoque_prod_al,27,4);
          

          DrawText(id_prod_al,id_produto_al.x+5,id_produto_al.y+15,20,BLACK); 
          DrawText(nome_prod_al,nome_produto_al.x+5,nome_produto_al.y+15,20,BLACK);
          DrawText(ficha_prod_al,ficha_al.x+5,ficha_al.y+15,20,BLACK);
          DrawText(preco_prod_al,preco_al.x+5,preco_al.y+15,20,BLACK);
          DrawText(estoque_prod_al,estoque_al.x+5,estoque_al.y+15,20,BLACK);
          DrawTexture(textura_produto_tela, imagem_al.x, imagem_al.y, WHITE);
          
          
          //Verifica qual botão foi precionado
          Check_if_is_buttonpressed_switch(cancelar_al, p_opcao, 1);
          
          //Busca produto pelo ID
          if(CheckCollisionPointRec(GetMousePosition(),lupa_al))
          {
            DrawRectangleLines(lupa_al.x,lupa_al.y,lupa_al.width, lupa_al.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              carregar_produto(id_prod_al, nome_prod_al, estoque_prod_al, preco_prod_al,ficha_prod_al);//falta imagem
              copiar_num_caracteres(id_prod_al,23); copiar_num_caracteres(nome_prod_al,24); copiar_num_caracteres(estoque_prod_al,27); copiar_num_caracteres(preco_prod_al,26); copiar_num_caracteres(ficha_prod_al,25); 
              imagem_produto_tela = LoadImage(FormatText("Imagens/%s.png", id_prod_al));
              ImageResize(&imagem_produto_tela, 200, 200);
              textura_produto_tela = LoadTextureFromImage(imagem_produto_tela);
              UnloadImage(imagem_produto_tela);
            }
          }
          
           //Cadastra Produto
          if(CheckCollisionPointRec(GetMousePosition(),confirmar_al))
          {
            DrawRectangleLines(confirmar_al.x,confirmar_al.y,confirmar_al.width, confirmar_al.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              modif_produto(id_prod_al, nome_prod_al, estoque_prod_al, preco_prod_al,ficha_prod_al,mensagem_al);
              limpar_campo(id_prod_al,23); limpar_campo(nome_prod_al,24); limpar_campo(estoque_prod_al,27); limpar_campo(preco_prod_al,26);  limpar_campo(ficha_prod_al,25); 
            }
          }
          
          //Exclui produto
          if(CheckCollisionPointRec(GetMousePosition(),excluir_al))
          {
            DrawRectangleLines(excluir_al.x,excluir_al.y,excluir_al.width, excluir_al.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              excluir_produto(id_prod_al,mensagem_al);
              limpar_campo(id_prod_al,23); limpar_campo(nome_prod_al,24); limpar_campo(estoque_prod_al,27); limpar_campo(preco_prod_al,26);  limpar_campo(ficha_prod_al,25); 
            }
          }

         EndDrawing();

         break;

         //tela de receber pedido
        case 4:

         BeginDrawing();

          ClearBackground(MAROON);

          DrawText("Pedidos realizados",25,30,30,BLACK);

          //Desenha botões ou caixas de texto
          DrawRectangleRec(voltar_r,WHITE);

          //Desenha titulo das caixas de texto ou texto dos botões
          DrawText("Voltar",voltar_r.x+18,voltar_r.y+5,20,BLACK);

          //Verifica qual botão foi precionado
          Check_if_is_buttonpressed_switch(voltar_r, p_opcao, 1);
          
          DrawRectangle(18,95, 500, 460, RAYWHITE);
          
          printar_pedidos();
          
         EndDrawing();

         break;

         //tela de banir usuário
        case 5:
    
         BeginDrawing();
          
          ClearBackground(MAROON);

          DrawText("Banimento de usuário", 25,30,30,BLACK);
           
          //Desenha botões e caixas de texto           
          DrawRectangleRec(cpf_ba,WHITE);
          DrawRectangleRec(usuario_lupa_bu,WHITE);
          DrawRectangleRec(nome_usuario_ba,WHITE);
          DrawRectangleRec(data_nasc_ba,WHITE);
          DrawRectangleRec(banir_ba,YELLOW);
          DrawRectangleRec(cancelar_ba,WHITE);

          //Desenha titulo das caixas de texto ou texto dos botões
          DrawText("Buscar usuário pelo CPF ",cpf_ba.x,cpf_ba.y-25,20,BLACK);
          DrawText("Nome do usuário",nome_usuario_ba.x,nome_usuario_ba.y-25,20,BLACK);
          DrawText("Data de Nascimento",data_nasc_ba.x,data_nasc_ba.y-25,20,BLACK);
          DrawText("Banir",banir_ba.x+10,banir_ba.y+8,20,BLACK);
          DrawText("Cancelar",cancelar_ba.x+10,cancelar_ba.y+8,20,BLACK);
          DrawText(mensagem_b,25,350,20,BLACK);
          DrawText(nome_cliente,nome_usuario_ba.x+5,nome_usuario_ba.y+15,20,BLACK);
          DrawText(data_nasc,data_nasc_ba.x+5,data_nasc_ba.y+15,20,BLACK);
          
          DrawTexture(u_lupa,usuario_lupa_bu.x,usuario_lupa_bu.y,WHITE);

          //Checa se o mause esta em uma caixa de texto e mostra o caracter digitado
          Check_if_is_on_textbox(cpf_ba,cpf_cliente,29,12);
          
          DrawText(cpf_cliente,cpf_ba.x+5,cpf_ba.y+15,20,BLACK);

          //Verifica qual botão foi precionado
          Check_if_is_buttonpressed_switch(cancelar_ba, p_opcao, 1);
          
          //Busca usuario pelo CPF
          if(CheckCollisionPointRec(GetMousePosition(),usuario_lupa_bu))
          {
            DrawRectangleLines(usuario_lupa_bu.x,usuario_lupa_bu.y,usuario_lupa_bu.width, usuario_lupa_bu.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              carregar_usuario(cpf_cliente,nome_cliente, data_nasc,mensagem_b);
            }
          }
          
          //
          if(CheckCollisionPointRec(GetMousePosition(),banir_ba))
          {
            DrawRectangleLines(banir_ba.x,banir_ba.y,banir_ba.width, banir_ba.height, ORANGE);
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
              excluir_usuario(cpf_cliente,nome_cliente, data_nasc,mensagem_b);
            }
          }

         EndDrawing();

         break;

         //logout
        case 6: 
        
         CloseWindow();
         break;

      }
     }   
    }