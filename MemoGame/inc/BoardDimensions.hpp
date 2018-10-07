#ifndef DEF_BOARD_DIMENSIONS
#define DEF_BOARD_DIMENSIONS

/**
 * Data structure that holds board and card dimensions.
 */
struct boardDimensions {
  float cardsize, spacing, xoffset, yoffset, xcards, ycards;
  boardDimensions
    (float rspacing, float width, float height, int xcards, int ycards);
};

#endif
