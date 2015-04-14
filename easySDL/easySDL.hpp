#ifndef EASYSDL_HPP
#define EASYSDL_HPP

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdexcept>
#include <string>

//Window Struct to simplify the use of windows
struct Window{
    SDL_Window * window;
    SDL_Surface* surface;
    std::string name;
    
    //Initializes SDL and creates a window which is set to the window member
    //them gets that windows 
    Window( int width, int height, const char *);
    
    //Destructor
    //Frees destroys the window
    ~Window();
    
    //updates the window surface
    void update();
    
};

//Image stuct to wrap and simplify images as surfaces
struct Image
{
private:
    //can't default construct
    Image() {}
public:
    //surface member to hold an image
    SDL_Surface * image;
    std::string fname;

    //Only valid constructor requires a path to an image
    Image(const char * path);
    
    //Frees the surface and kills itself
    ~Image();
    
    //Uses easyblit to blit itself
    int blit(SDL_Surface * , int, int);
};



//Sets up SDL and returns a window
//ACcepts a width and height
SDL_Window * init( int, int, const char *);

//Loads an Image to a surface and returns the surface
//accepts the file path to the image
SDL_Surface * loadImage( const char *);

//Simplified blitting using SDL_BlitSurfaces
int easyblit(SDL_Surface *, SDL_Surface *, int x = 0, int y = 0);


//Pauses SDL for time seconds
void pause( int time);

// Quits SDL and SDL_image
//Does not free surfaces must be done by user!
void cleanup();


#endif
