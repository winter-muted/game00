#include "texture.hpp"

LTexture::LTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

void LTexture::loadFromFile(std::string path, IOContext & io) {
    //Get rid of preexisting texture
  	free();

    // get pointers to rendering context
    SDL_Renderer* gRenderer = io.getRenderer();

  	//The final texture
  	SDL_Texture* newTexture = NULL;

  	//Load image at specified path
  	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  	if( loadedSurface == NULL )
  	{
  		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  	}
  	else
  	{
  		//Color key image
  		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xEE, 0xEE, 0xEE ) );

  		//Create texture from surface pixels
          newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
  		if( newTexture == NULL )
  		{
  			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  		}
  		else
  		{
  			//Get image dimensions
  			mWidth = loadedSurface->w;
  			mHeight = loadedSurface->h;
  		}

  		//Get rid of old loaded surface
  		SDL_FreeSurface( loadedSurface );
  	}

  	//Return success
  	mTexture = newTexture;
 //  	return mTexture != NULL;
}
void
LTexture::render(IOContext & io,int x, int y,Rect* sprite = NULL)
{
    if (mTexture == NULL) {
        std::cout << "Tried to render NULL texture!\n";
        exit(3);
    }

    SDL_Rect* clip;

    if (sprite != NULL)
    {
        // std::cout << sprite->x << "\n";
        SDL_Rect newclip;
        newclip.x = sprite->x;
        newclip.y = sprite->y;
        newclip.h = sprite->h;
        newclip.w = sprite->w;
        clip = &newclip;
    }
    else
    {
        clip = NULL;
    }
    // if (clip != NULL)
    //     std::cout << "got good clip.\n";

    renderTexture(io,x,y,clip);
}

void LTexture::renderTexture(IOContext & io,int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {

  SDL_Renderer* gRenderer = io.getRenderer();

  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;

    // std::cout << "going to render" << renderQuad.w << "\n";
  }

  SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
