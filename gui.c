#include "gui.h"
#include <string.h> //strlen

GUI_Button** arrayGui = NULL;   //Array of pointers to gui elements/objects.
int16_t arrayGuiSize = 0;

//The gui will be drawed inside of this surface:
SDL_Surface* whereToDrawTheGui = NULL;

void GUI_Init(SDL_Surface* destSurface)
{
//The newly created gui will be drawn inside of this surface:
    whereToDrawTheGui = destSurface;
}

void GUI_Quit()
{
    for(int i = 0; i < arrayGuiSize; i++)
    {
        SDL_FreeSurface(arrayGui[i]->drawThisSurface);//    SDL_FreeSurface(button->textSurface); //free(button->text);
        free(arrayGui[i]);
        //arrayGuiSize--;
    }
    free(arrayGui);
    arrayGui = NULL;
    arrayGuiSize = 0;
    whereToDrawTheGui = NULL;
}

GUI_Button* GUI_CreateTextButton(  void (*WhenClicked)(),
                        const char* text, TTF_Font* textFont, uint16_t x, uint16_t y,
                        uint16_t w, uint16_t h, uint32_t color)
{
    //Make the array bigger to hold the pointer to the new gui element:
    arrayGui = (GUI_Button*)realloc(arrayGui, (arrayGuiSize + 1) * sizeof(GUI_Button*) );
    //Add one button to the array.
    arrayGui[arrayGuiSize] = (GUI_Button*) malloc(sizeof(GUI_Button));

    //button->text = (char*) malloc(strlen(text) + 1);

    arrayGui[arrayGuiSize]->x = x;    arrayGui[arrayGuiSize]->y = y;
    arrayGui[arrayGuiSize]->w = w;    arrayGui[arrayGuiSize]->h = h;
    arrayGui[arrayGuiSize]->WhenClicked = WhenClicked;
    //button->color = color;
//    button->whereToDrawSurface = surface;

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(textFont, text, (SDL_Color){255, 255, 255,255}, w);
//    SDL_Surface* tempTextSurface = TTF_RenderText_Solid(textFont, text, (SDL_Color){255, 255, 255,255});
//    button->textSurface = SDL_ConvertSurface(tempTextSurface, surface->format, 0);
//    SDL_FreeSurface(tempTextSurface);

    //Final surface to draw each frame:
    //SDL_Rect rect = {x, y, w, h};

    arrayGui[arrayGuiSize]->drawThisSurface = SDL_CreateRGBSurface(0, w, h, whereToDrawTheGui->format->BitsPerPixel,
                                        whereToDrawTheGui->format->Rmask, whereToDrawTheGui->format->Gmask,
                                        whereToDrawTheGui->format->Bmask, whereToDrawTheGui->format->Amask);

    //SDL_Surface* textSurfaceOptimized = SDL_ConvertSurface(textSurface, button->drawThisSurface->format, 0);

    SDL_FillRect(arrayGui[arrayGuiSize]->drawThisSurface, NULL, color);

    //SDL_Rect srcRect = {0, 0, textSurface->w, textSurface->h};
    //That +3 is just to separate the text a little from the left margin.
    SDL_Rect dstRect = {    (w - textSurface->w) / 2 + 3, (h - textSurface->h) / 2,
                            textSurface->w, textSurface->h};

    //SDL_BlitScaled(textSurfaceOptimized, NULL, button->drawThisSurface, NULL);
    SDL_BlitSurface(textSurface, NULL, arrayGui[arrayGuiSize]->drawThisSurface, &dstRect);
    SDL_FreeSurface(textSurface);
    //SDL_FreeSurface(textSurfaceOptimized);
    //printf("%d - %s\n", button->drawThisSurface    , SDL_GetError()    );

    LineBresenham(0, 0, w-1, 0, 0xFFFFFFFF, arrayGui[arrayGuiSize]->drawThisSurface);
    LineBresenham(w-1, 0, w-1, h-1, 0xFFFFFFFF, arrayGui[arrayGuiSize]->drawThisSurface);
    LineBresenham(0, 0, 0, h-1, 0xFFFFFFFF, arrayGui[arrayGuiSize]->drawThisSurface);
    LineBresenham(0, h-1, w-1, h-1, 0xFFFFFFFF, arrayGui[arrayGuiSize]->drawThisSurface);

    arrayGuiSize++;
    return arrayGui[arrayGuiSize];
}
//void ChangeTextOfButton(Button* button, TTF_Font* textFont, const char* text)       //Add text color.
//{
//    //button->text = (char*) realloc(button->text, strlen(text) + 1);
////    button->textSurface = TTF_RenderText_Solid(textFont, text, (SDL_Color){255, 255, 255, 255});
//}
int8_t GUI_EventButtons(SDL_Event* e)   //Eliminate the second parameter. That function should be specified inside of the button struct.
{
     //Get mouse position
     int x, y;
     SDL_GetMouseState( &x, &y );

    for(int i = 0; i < arrayGuiSize; i++)
    {
         if(e->type == SDL_MOUSEBUTTONDOWN &&
                x < (arrayGui[i]->w + arrayGui[i]->x) && x > arrayGui[i]->x &&
                y < (arrayGui[i]->h + arrayGui[i]->y) && y > arrayGui[i]->y)
        {
            arrayGui[i]->WhenClicked();
            return 1;
        }
    }
    return 0;
}

void GUI_DrawButtons()
{
    SDL_Rect destRect;
    for(int i = 0; i < arrayGuiSize; i++)
    {
        destRect.x = arrayGui[i]->x; destRect.y = arrayGui[i]->y;
        destRect.w = arrayGui[i]->w; destRect.h = arrayGui[i]->h;
        SDL_BlitSurface(arrayGui[i]->drawThisSurface, NULL, whereToDrawTheGui, &destRect);
    }
}













