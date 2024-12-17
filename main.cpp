#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>


const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 520;

// Drawing area boundaries
const float X_ORIGIN = (float)SCREEN_WIDTH/4;
const float X_END = (float)SCREEN_WIDTH*3/4;
const float Y_ORIGIN = (float)SCREEN_HEIGHT/5;
const float Y_END = (float)SCREEN_HEIGHT*4/5;
const float CENTER_X = (float)SCREEN_WIDTH/2;
const float CENTER_Y = (float)SCREEN_HEIGHT/2;
const int INNER_WIDTH = 350;
const int INNER_HEIGHT = 312;

bool init();
void close();

SDL_Window* gWin=NULL;
SDL_Renderer* gRend=NULL;



int main (int argc, char *argv[]) 
{
   if (!init()) 
   {
      std::cout << "Failed to init app" << std::endl;
   }
   else 
   {
      bool quit=false;
      SDL_Event e;

      while (!quit) 
      {
         while (SDL_PollEvent(&e)!=0) 
         {
            if (e.type==SDL_QUIT)
            {
               quit = true;
            }
         }
         
         // clear screen
         SDL_SetRenderDrawColor(gRend, 0xff, 0xff, 0xff, 0xff);
         SDL_RenderClear(gRend);
         
         

         for (int i=0; i<=INNER_WIDTH; i+=10) 
         {
            SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
            SDL_RenderDrawLine(gRend, CENTER_X, Y_END, X_ORIGIN+i, CENTER_Y-50);

         }
         
         // top part
         // -------------- oblique
         for (int i = 0; i <= 170; i+=10) 
         {
            SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
            SDL_RenderDrawLine(gRend, X_ORIGIN+i, CENTER_Y-50, (X_ORIGIN+70), Y_ORIGIN);
         }
         for (int i = 170; i>=0; i-=10) 
         {
            SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
            SDL_RenderDrawLine(gRend, X_END-i, CENTER_Y-50, X_END-70, Y_ORIGIN);
         }
         
         // ------------------- horizontal
         SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
         SDL_RenderDrawLine(gRend, X_ORIGIN+70, Y_ORIGIN, X_ORIGIN+120, Y_ORIGIN);
         SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
         SDL_RenderDrawLine(gRend, X_END-70, Y_ORIGIN, X_END-120, Y_ORIGIN);
         // --------------- in oblique
         SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
         SDL_RenderDrawLine(gRend, CENTER_X, Y_END-262, X_ORIGIN+120, Y_ORIGIN);
         SDL_SetRenderDrawColor(gRend, 0xff, 0, 0, 250);
         SDL_RenderDrawLine(gRend, CENTER_X, Y_END-262, X_END-120, Y_ORIGIN);



         
         //SDL_RenderDrawLine(gRend, SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT);

         // update screen
         SDL_RenderPresent(gRend);
      }
   }
   close();
   return 0;
}

// ------------------------------------------------------------------------------------------------------

bool init()
{
   bool success=true;

   if (SDL_Init(SDL_INIT_VIDEO)<0) 
   {
      std::cout << "Couldnt initialise SDL. Error: " << SDL_GetError() << std::endl;
      success=false;
   }
   else 
   {
      if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 
      {
         std::cout << "Warning: linear texture filtering off." << std::endl;
      }

      gWin=SDL_CreateWindow("Heart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (gWin==NULL) 
      {
         std::cout << "Couldnt create window. Error: " << SDL_GetError() << std::endl;
         success=false;
      }
      else 
      {
         gRend=SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);
         if (gRend==NULL)
         {
            std::cout << "Couldnt create renderer. Error: " << SDL_GetError() << std::endl;
            success=false;
         }
         else 
         {
            SDL_SetRenderDrawColor(gRend,0xff, 0xff, 0xff, 0xff);

         }
      }

   }
   
   
   return success;
}

void close()
{
   
   SDL_DestroyRenderer(gRend);
SDL_DestroyWindow(gWin);
   gWin=NULL;
   gRend=NULL;

   SDL_Quit();
}
