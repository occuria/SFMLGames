#include <algorithm>
#include "../inc/BoardDimensions.hpp"

/* Ceci est une modification pour LittleWillow */

boardDimensions::boardDimensions
  (float rspacing, float width, float height, int xcards, int ycards)
{
	float cardsize = std::min(width/(rspacing+xcards), height/(rspacing+ycards));
	float spacing = std::min(
	  (rspacing*width)/(rspacing+xcards)*1/(xcards+1),
	  (rspacing*height)/(rspacing+ycards)*1/(ycards+1));
	float xoffset = (width-xcards*cardsize-(xcards-1)*spacing)/2;
	float yoffset = (height-ycards*cardsize-(ycards-1)*spacing)/2;

  this->spacing = spacing;
  this->cardsize = cardsize;
  this->xoffset = xoffset;
  this->yoffset = yoffset;
  this->xcards = xcards;
  this->ycards = ycards;
}
