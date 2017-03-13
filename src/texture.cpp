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
  		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

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

void LTexture::render(IOContext & io,int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {

  SDL_Renderer* gRenderer = io.getRenderer();

  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
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
