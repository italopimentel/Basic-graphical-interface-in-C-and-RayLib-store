#include <raylib.h>
#include "aux_library.c"
#include "store.c"
#include "user_info.c"

#define MAX_BU 50

int opcao_store = 1;
char busca_produto[60]= "";

bool desativar_botoes = false;

int counter;

int id_retornado;
int pointer_return;

int max_bu = MAX_BU;

bool atualizar_valores = true;


int vetor_pesquisados[10];


static void store_screen()
{
    gerar_arquivo_leitura();
    gerar_valores_grid();
    carregar_produtos_grid();
    gerar_grid_carrinho();
 
    //Define o tamnho da janela
    const int largura = 1080;
    const int altura = 700;
    
    //InitWindow(Inicia uma janela a partir dos paramêtros digitados)
    InitWindow(largura, altura, "usuario");
    

    //Taxa de atualização da tela
    SetTargetFPS(60);
    
    //Cria um retângulo(x,y,largura,altura)
    Rectangle cabecalho = {0,0,1080,130};
    Rectangle caixa_de_pesquisa = {380,70,350,40};
    Rectangle caixa_de_lupa = {730,70,40,40};
    Rectangle caixa_carrinho = {890,30,45,45};
    Rectangle caixa_layout = {950,33,90,40};
    
    //Retangulos da tela do produto
     Rectangle cabecalho_prod = {0,0,1080,130};
     Rectangle add_carrinho = {600,430,200,60};
     Rectangle produto = {50,150,350,350};
     Rectangle nome_do_produto = {525,150,425,80};
     Rectangle preco = {525,310,100,40};
     Rectangle quantidade = {820,325,100,40};
     Rectangle descricao = {50,535,980,120};
     Rectangle b_home = {30,30,40,40};
     
    // RETANGULO DO CARRINHO
    Rectangle cabecalho_c = {0,0,1080,100};
    Rectangle voltar = {30,33,40,40};
    Rectangle compra_finalizada = {865,120,185,40};
    Rectangle valor_total = {760,120,100,40};
    Rectangle confimacao_de_compra = {350,500,600,200};
    
    //Retangulos da tela de pesquisa
    Rectangle cabecalho_pesquisa = {0,0,1080,130};
    Rectangle home_pesquisa = {30,30,40,40};
    Rectangle tela_de_pesquisa = {380,70,350,40};
    Rectangle lupa_tela_pesquisa = {730,70,40,40};
    
    //Tela do comprovante de compra
    Rectangle concluir_compra = {900,80,170,40};
    Rectangle baixar_comprovante = {720, 80, 170, 40};
     
     
    int preco_prod;
    int quantidade_prod;
    char descricao_prod [100];
    char nome_prod[60];
    
    int id_retornado_real = 0;
    
    //mensagem de erro no carrinho
    char mensagem_de_erro_carrinho[60] = "";
    
    // Desenha a lupa
    
    Texture2D lupa = LoadTexture("Imagens/lupa 40px.png");
    
    // Desenha Images da tela do produto
    
     Texture2D carrinho = LoadTexture("Imagens/cesta 40px.png");
     Texture2D home = LoadTexture("Imagens/home2.png");
     
     generate_path();
     
     //Desenho tela de pesquisa
     Texture2D lupa_pesquisa = LoadTexture("Imagens/lupa 40px.png");
     Texture2D home_pesq = LoadTexture("Imagens/home2.png");
    
    // Desenha Images da tela do produto
    
     //Texture2D carrinho = LoadTexture("Imagens/cesta 40px.png");
     Texture2D carrinho_prod = LoadTexture("Imagens/cesta 64px.png");
     Texture2D home_prod = LoadTexture("Imagens/home2.png");
     
       
    //Continua rodando até que aperte o botão "x"
    while(!WindowShouldClose()){
       
        switch(opcao_store){
           
            
        case 1:
        
        if(atualizar_valores == true)
        {
        gerar_valores_grid();
        atualizar_valores = false;
        }
        
         //Inicia o processo gráfico
         BeginDrawing();
        
         Check_if_is_buttonpressed_switch(caixa_layout,&opcao_store,2);
         Check_if_is_buttonpressed_switch(caixa_de_lupa,&opcao_store,4);
         Check_if_is_buttonpressed_switch(caixa_carrinho, &opcao_store, 3);
  
        
            ClearBackground(RAYWHITE);
  
            //Função que desenha o retângulo
            DrawRectangleRec(cabecalho,MAROON);
            DrawRectangleRec(caixa_de_pesquisa, WHITE);
            DrawRectangleRec(caixa_carrinho, WHITE);
            DrawRectangleRec(caixa_layout, WHITE);
            DrawRectangleRec(caixa_de_lupa, WHITE);
            
            //Desenha um envoltório do retangulo
            DrawRectangleLines(caixa_carrinho.x, caixa_carrinho.y, caixa_carrinho.width ,caixa_carrinho.height, GRAY);
            DrawRectangleLines(caixa_layout.x, caixa_layout.y, caixa_layout.width ,caixa_layout.height, GRAY);               
            
            //Desenha um texto na tela
            if(busca_produto[0] == '\0')
            {
                DrawText("pesquise aqui seu produto", caixa_de_pesquisa.x+55, caixa_de_pesquisa.y +10, 20, GRAY); 
            }
            //DrawText("pesquise aqui seu produto", caixa_de_pesquisa.x+55, caixa_de_pesquisa.y +10, 20, GRAY);        
            DrawText("sair", caixa_layout.x +25, caixa_layout.y+8 , 20, BLACK);
            DrawText(FormatText("Bem vindo Sr(a) %s a nossa loja online.", set_user_name()), +50, +25, 20, BLACK);
            
            //Checa se o mouse esta em uma caixa de texto e mostra o caracter digitado
            Check_if_is_on_textbox_allowspace(caixa_de_pesquisa,busca_produto,50,30);            
            DrawText(busca_produto,caixa_de_pesquisa.x+5,caixa_de_pesquisa.y+15,20,BLACK);
               
            
            // Desenha a lupa na tela na barra de pesquisa.
            DrawTexture(lupa,caixa_de_lupa.x,caixa_de_lupa.y,WHITE);
            
            // Desenha o carrinho na tela na barra de pesquisa.            
            DrawTexture(carrinho,caixa_carrinho.x+3,caixa_carrinho.y+3,WHITE);
            
            //Busca produto pelo nome
            
            
              if(CheckCollisionPointRec(GetMousePosition(),caixa_de_lupa))
              {
                DrawRectangleLines(caixa_de_lupa.x,caixa_de_lupa.y,caixa_de_lupa.width, caixa_de_lupa.height, ORANGE);
                
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                   counter = pesquisar(busca_produto, &vetor_pesquisados);
                }
              }
             
              
                for(int i = 1; i <= max_bu; i++)
                { 
                 id_retornado = printar_grid(i, &opcao_store);  
                 if(id_retornado != 0)
                 {
                     id_retornado_real = id_retornado;
                 }
                }
                
              
        
        //Termina o processo gráfico
        EndDrawing();
        
        break;
        
        case 2 :
            CloseWindow();
         break;
         
        //Tela do carrinho
        case 3: 
      
        Check_if_is_buttonpressed_switch(voltar, &opcao_store, 1);
  
           
       
         BeginDrawing();
         
            //Finalizar a compra
           
           if(CheckCollisionPointRec(GetMousePosition(),compra_finalizada)){
               
               if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
               {
                    finalizar_compra(&opcao_store, mensagem_de_erro_carrinho);
               }
           }
    
         ClearBackground(RAYWHITE);
         //Desenaha Retangulos
         DrawRectangleRec(cabecalho_c,MAROON);
         DrawText("Carrinho de Compras",+100,+20,20,RAYWHITE);
        
         //botao voltar
         DrawRectangleRec(voltar,RAYWHITE);
         DrawRectangleLines(voltar.x,voltar.y,voltar.width,voltar.height, BLACK);
         DrawTexture(home,voltar.x,voltar.y,MAROON);
 
              
         //butao finalizar compra
         DrawRectangleRec(compra_finalizada,MAROON);
         DrawRectangleLines(compra_finalizada.x,compra_finalizada.y,compra_finalizada.width,compra_finalizada.height, BLACK);
         DrawText("Finalizar compra",compra_finalizada.x+10 ,compra_finalizada.y+10, 20,WHITE);
         
         //valor total
         DrawRectangleRec(valor_total,WHITE);
         DrawRectangleLines(valor_total.x,valor_total.y,valor_total.width,valor_total.height, BLACK);
         DrawText("Valor total:",valor_total.x-125 ,valor_total.y+10, 20, BLACK);
         
         DrawText(mensagem_de_erro_carrinho, 10, 120, 20, BLACK);
        
         desenhar_compra();
         EndDrawing();
         
         break;
        
        //Tela de pesquisa
        case 4:
            
            BeginDrawing();
            Check_if_is_buttonpressed_switch(home_pesquisa,&opcao_store,1);
            atualizar_valores = true;
            
            ClearBackground(RAYWHITE);
            //Função que desenha o retângulo
            
            DrawRectangleRec(cabecalho_pesquisa,MAROON);
            //botão home_pesquisa
            
            DrawRectangleLines(home_pesquisa.x, home_pesquisa.y, home_pesquisa.width, home_pesquisa.height, BLACK);
            DrawTexture(home_pesq, home_pesquisa.x, home_pesquisa.y, MAROON);
            
            //botão lupa_pesquisa
            DrawRectangleRec(lupa_tela_pesquisa,RAYWHITE);
            DrawRectangleLines(lupa_tela_pesquisa.x, lupa_tela_pesquisa.y, lupa_tela_pesquisa.width, lupa_tela_pesquisa.height, BLACK);
            DrawTexture(lupa_pesquisa,lupa_tela_pesquisa.x,lupa_tela_pesquisa.y,WHITE);
            
             //Função que desenha o retângulo
            DrawRectangleRec(tela_de_pesquisa, WHITE);
            
            //Checa se o mouse esta em uma caixa de texto e mostra o caracter digitado
            Check_if_is_on_textbox_allowspace(tela_de_pesquisa,busca_produto,50,30);            
            DrawText(busca_produto,tela_de_pesquisa.x+5,tela_de_pesquisa.y+15,20,BLACK);

            
           //Desenha um texto na tela
           
            if(busca_produto[0] == '\0')
            {
                DrawText("pesquise aqui seu produto", tela_de_pesquisa.x+55, tela_de_pesquisa.y +10, 20, GRAY); 
            }
            
             //Busca produto pelo nome
            
              if(CheckCollisionPointRec(GetMousePosition(),lupa_tela_pesquisa))
              {
                DrawRectangleLines(lupa_tela_pesquisa.x,lupa_tela_pesquisa.y,lupa_tela_pesquisa.width, lupa_tela_pesquisa.height, ORANGE);
                
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                   counter = pesquisar(busca_produto, &vetor_pesquisados);
                }
              }
            
            for(int i = 1; i <= counter; i++)
            {
                 id_retornado = printar_grid(vetor_pesquisados[i], &opcao_store);
                 if(id_retornado != 0)
                 {
                   id_retornado_real = id_retornado;
                 }
            }
            
            EndDrawing();
            
        break;
        
        //Tela produto
        case 5:
         
            
        
        BeginDrawing();
        
         ClearBackground(RAYWHITE);
         
        
        comprar(add_carrinho, id_retornado_real);
        Check_if_is_buttonpressed_switch(b_home, &opcao_store,1);
            
    
         ClearBackground(RAYWHITE);
         DrawRectangleRec(cabecalho_prod,MAROON);
        
         
          //botão home
         DrawRectangleRec(b_home,RAYWHITE);
         DrawRectangleLines(b_home.x, b_home.y, b_home.width, b_home.height, BLACK);
         DrawTexture(home_prod,b_home.x,b_home.y,MAROON);
         
         //Nome do produto
         //DrawRectangleLines(nome_do_produto.x -2, nome_do_produto.y -2, nome_do_produto.width +5, nome_do_produto.height +5, BLACK);
         DrawRectangleRec(nome_do_produto,RAYWHITE);
         DrawText(nome_prod,nome_do_produto.x+10,nome_do_produto.y+10, 30,BLACK);
        
         //Imagem do produto
         DrawRectangleRec(produto,WHITE);
         DrawRectangleLines(produto.x,produto.y,produto.width,produto.height, BLACK);
         
         load_product_to_page(id_retornado_real, nome_prod, &preco_prod, &quantidade_prod, descricao_prod, produto);
         
         //Quantidade
         DrawText("Estoque:",quantidade.x-90,quantidade.y,20,BLACK);
         DrawText(FormatText("%i",quantidade_prod),quantidade.x,quantidade.y, 20,BLACK);
         
         //Botao comprar
         DrawRectangleRec(add_carrinho,DARKGREEN);
         DrawRectangleLines(add_carrinho.x,add_carrinho.y,add_carrinho.width,add_carrinho.height, BLACK);
         DrawText("comprar",add_carrinho.x+10 ,add_carrinho.y+14, 30,WHITE);
         DrawTexture(carrinho_prod, add_carrinho.x+135, add_carrinho.y,WHITE);
        
         //descriçao
         DrawRectangleRec(descricao,WHITE);
         DrawRectangleLines(descricao.x,descricao.y,descricao.width,descricao.height, BLACK);
         DrawText("descriçao:",descricao.x+5 ,descricao.y+10, 20,BLACK);
         DrawText(descricao_prod,descricao.x+15, descricao.y+40,20,BLACK);
        
        
         //Preço
         DrawText(FormatText("R$%i",preco_prod),preco.x,preco.y, 40,BLACK);
         
        
         EndDrawing();
        
        break;
        
        case 6:
        
            BeginDrawing();
            
            DrawRectangleRec(cabecalho,MAROON);
            ClearBackground(RAYWHITE);
            DrawText("Compra realizada com sucesso, você comprou os seguintes itens:", 20, 50, 20, WHITE);
            printar_itens_comprados();
            DrawRectangleRec(concluir_compra, DARKGREEN);
            DrawRectangleRec(baixar_comprovante, DARKGREEN);
            DrawText("OK",concluir_compra.x + 72 ,concluir_compra.y +10, 20,WHITE);
            DrawText("Baixar comprovante", baixar_comprovante.x + 7.5, baixar_comprovante.y + 12, 16, WHITE);
            
            EndDrawing();
            
            if(CheckCollisionPointRec(GetMousePosition(),concluir_compra))
            {
               
               if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
               {
                    atualizar_arquivo_pos_compra();
                    CloseWindow();
               }
            }
            //Botão de baixar comprovante
            if(CheckCollisionPointRec(GetMousePosition(),baixar_comprovante))
            {
               
               if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
               {
                    gerar_comprovante();
               }
            }
        
        break;
        }
    }
    
}