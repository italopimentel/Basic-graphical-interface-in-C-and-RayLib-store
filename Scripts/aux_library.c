#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//Define que vários scripts podem abrir esse arquivo
#ifndef aux_library.c
#define aux_library.c

int letter_counter[60];

static void limpar_campo (char* vetor, int id_do_vetor)
{
    int n_chr = strlen(vetor);
    for(int i =0; i < n_chr; i++)
    {
        vetor[i] = '\0';
    }
    letter_counter[id_do_vetor] = strlen(vetor);
    
}
static void copiar_num_caracteres(char* vetor, int id_do_vetor)
{
    letter_counter[id_do_vetor] = strlen(vetor);
}

//Função que detecta se o mouse está em cima da caixa de texto
static void Check_if_is_on_textbox(Rectangle textbox_core, char* vetor, int id, int Max_char)
{

   if(CheckCollisionPointRec(GetMousePosition(), textbox_core))
   {
       DrawRectangleLines(textbox_core.x, textbox_core.y, textbox_core.width, textbox_core.height, ORANGE);
       DrawText("|", textbox_core.x + 8 + MeasureText(vetor,20), textbox_core.y + 15 , 20, BLACK);
       
       int key = GetKeyPressed();
       
       if(key >= 35 && key <= 125 && (letter_counter[id] < Max_char)){
         
            vetor[letter_counter[id]] = (char) key;
            letter_counter[id]++;
       }
       
       else if(IsKeyPressed(KEY_BACKSPACE) && letter_counter[id] > 0)
       {
           letter_counter[id]--;
           vetor[letter_counter[id]] = '\0';
       }
       
   }
        
}

static void Check_if_is_on_textbox_allowspace(Rectangle textbox_core, char* vetor, int id, int Max_char)
{
    
   if(CheckCollisionPointRec(GetMousePosition(), textbox_core))
   {
       DrawRectangleLines(textbox_core.x, textbox_core.y, textbox_core.width, textbox_core.height, ORANGE);
       DrawText("|", textbox_core.x + 8 + MeasureText(vetor,20), textbox_core.y + 15 , 20, BLACK);
       
       int key = GetKeyPressed();
       
       if(key >= 35 && key <= 125 && (letter_counter[id] < Max_char)){
         
            vetor[letter_counter[id]] = (char) key;
            letter_counter[id]++;
       }
       
       else if(IsKeyPressed(KEY_BACKSPACE) && letter_counter[id] > 0)
       {
           letter_counter[id]--;
           vetor[letter_counter[id]] = '\0';
       }
       
       else if(IsKeyPressed(KEY_SPACE) && letter_counter[id] > 0 && (letter_counter[id] < Max_char))
       {
           vetor[letter_counter[id]] = ' ';
           letter_counter[id]++;

       }
   }
        
}

static void Check_if_is_on_textbox_space(Rectangle textbox_core, char* vetor ,char* vetor_fake, int id, int Max_char)
{
    
   if(CheckCollisionPointRec(GetMousePosition(), textbox_core))
   {
       DrawRectangleLines(textbox_core.x, textbox_core.y, textbox_core.width, textbox_core.height, ORANGE);
       DrawText("|", textbox_core.x + 8 + MeasureText(vetor,20), textbox_core.y + 15 , 20, BLACK);
       
       int key = GetKeyPressed();
       
       if(key >= 35 && key <= 125 && (letter_counter[id] < Max_char)){
         
            vetor[letter_counter[id]] = (char) key;
            vetor_fake[letter_counter[id]] = (char) key;
            letter_counter[id]++;
       }
       
       else if(IsKeyPressed(KEY_BACKSPACE) && letter_counter[id] > 0)
       {
           letter_counter[id]--;
           vetor[letter_counter[id]] = '\0';
           vetor_fake[letter_counter[id]] = '\0';
       }
       
       else if(IsKeyPressed(KEY_SPACE) && letter_counter[id] > 0 && (letter_counter[id] < Max_char))
       {
           vetor[letter_counter[id]] = '_';
           vetor_fake[letter_counter[id]] = ' ';
           letter_counter[id]++;
       }
   }
        
}

//Função para ação de qualquer botão
static void Check_if_is_buttonpressed(Rectangle button, void func_to_play())
{
    
    if(CheckCollisionPointRec(GetMousePosition(), button))
    {
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            func_to_play();
        }
        
    }
    
}

static void Check_if_is_buttonpressed_switch(Rectangle button, int* option, int option_to_switch)
{
    
    if(CheckCollisionPointRec(GetMousePosition(), button))
    {
        DrawRectangleLines(button.x, button.y, button.width, button.height, ORANGE);
        
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            
            *option = option_to_switch;
            
        }
        
    }
    
}  

static void Masked_textbox(Rectangle button, Rectangle text_box, char* non_masked_vetor, char* masked_vetor, bool* on_off, int id, int Max_char)
{
    
    if(CheckCollisionPointRec(GetMousePosition(), button))
    {
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(*on_off == true){
                *on_off = false;
            }
            else if(*on_off == false){
                *on_off = true;
            }
            
   
        }
    }
    
   if(CheckCollisionPointRec(GetMousePosition(), text_box))
   {
       DrawRectangleLines(text_box.x, text_box.y, text_box.width, text_box.height, ORANGE);
       DrawText("|", text_box.x + 8 + MeasureText(masked_vetor,20), text_box.y + 15 , 20, BLACK);
       
       int key = GetKeyPressed();
       
       if(key >= 35 && key <= 125 && (letter_counter[id] < Max_char)){
         
            non_masked_vetor[letter_counter[id]] = (char) key;
            masked_vetor[letter_counter[id]] = '*';
            letter_counter[id]++;
       }
       
       if(IsKeyPressed(KEY_BACKSPACE) && letter_counter[id] > 0)
       {
           letter_counter[id]--;
           non_masked_vetor[letter_counter[id]] = '\0';
           masked_vetor[letter_counter[id]] = '\0';
           
       }
       
   }
    
}

#endif /* aux_library.c */
