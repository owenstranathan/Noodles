#include "easySDL.hpp"



//////////////////////////
//WINDOW//////////////////
//////////////////////////

Window::Window(int width, int height, const char * wname)
{
    name = wname;
    window = init( width, height, wname);
    surface = SDL_GetWindowSurface(window);
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    window = NULL;
}

//updates the window surface
void Window::update()
{
    SDL_UpdateWindowSurface(window);
}



/////////////////////////
//IMAGE//////////////////
/////////////////////////

//CONSTRUCTOR
Image::Image(const char * path) : fname(path)
{
    image = loadImage(path);
}

//DESTRUCTOR
Image::~Image()
{
    SDL_FreeSurface(image);
    image = NULL;
}

int Image::blit(SDL_Surface * screen, int x, int y)
{
    return easyblit(image, screen, x, y);
}


//////////////////////////
//GENERAL PURPOSE/////////
//////////////////////////

//Initializes SDL and Makes a window , then returns it
SDL_Window * init( int WIDTH, int HEIGHT, const char * name)
{
    //The window
    SDL_Window * window = NULL;

    //Init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error( SDL_GetError() );
    }
    
    //Init SDL_Image
    if ( !IMG_Init(IMG_INIT_PNG)) {
        throw std::runtime_error(IMG_GetError());
    }
    
    //Create Window
    window =
    SDL_CreateWindow( name, SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    //If SDL fucked up and the window wasn't created successfully throw away
    if( window == NULL)
    {
        throw std::runtime_error( SDL_GetError() );
    }
    
    //return the window
    return window;
}


//Loads and optimized image to a surface and returns it
SDL_Surface * loadImage( const char * path)
{
    //the surface to be returned
    SDL_Surface * image = NULL;
    
    //load the image to the surface
    image = IMG_Load(path);
    
    //If SDL didn't load the image properly then throw
    if (image == NULL) {
        throw std::runtime_error( IMG_GetError() );
    }
    
    return image;
}

//less clunky version of SDL_BlitSurface (literally just calls SDL_BlitSurface()
int easyblit( SDL_Surface* image, SDL_Surface * screen, int x, int y)
{
    //Temporary rectangle to hold the offsets
    SDL_Rect  offset;
    
    //Get the offsets
    offset.x = x;
    offset.y = y;
    
    return SDL_BlitSurface(image, NULL, screen, &offset);

}

//Pauses SDL for time seconds
void pause( int time)
{
    SDL_Delay(time*1000);
}

void cleanup()
{
    IMG_Quit();
    SDL_Quit();
}