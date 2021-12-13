/*
 * image.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>

/**
 * Jet Fighter
 */
extern const uint8_t jet_fighterBitmaps[];
extern const uint8_t jet_fighterWidthPixels;
extern const uint8_t jet_fighterHeightPixels;

/**
 * UFO1
 */
extern const uint8_t ufo1Bitmaps[];
extern const uint8_t ufo1WidthPixels;
extern const uint8_t ufo1HeightPixels;

/**
 * UFO2
 */
extern const uint8_t ufo2Bitmaps[];
extern const uint8_t ufo2WidthPixels;
extern const uint8_t ufo2HeightPixels;

/**
 * Bullet
 */
extern const uint8_t bulletBitmaps[];
extern const uint8_t bulletWidthPixels;
extern const uint8_t bulletHeightPixels;

/**
 * Welcome Screen
 */
extern const uint8_t skyfighter0Bitmaps[];
extern const uint8_t skyfighter0WidthPixels;
extern const uint8_t skyfighter0HeightPixels;

/**
 * Press to start
 */
extern const uint8_t pressstartBitmaps[];
extern const uint8_t pressstartWidthPixels;
extern const uint8_t pressstartHeightPixels;

/**
 * explosion
 */
extern const uint8_t explosionBitmaps[];
extern const uint8_t explosionWidthPixels;
extern const uint8_t explosionHeightPixels;


/**
 * Game over (lose)
 */
extern const uint8_t game_overBitmaps[];
extern const uint8_t game_overWidthPixels;
extern const uint8_t game_overHeightPixels;

/**
 * Game over (you win)
 */
extern const uint8_t you_winBitmaps[];
extern const uint8_t you_winWidthPixels;
extern const uint8_t you_winHeightPixels;

/**
 * Color index for COLOR_CODE
 */
typedef enum {
    RED1 = 0,//!< RED1
    RED2,    //!< RED2
    YELLOW1, //!< YELLOW1
    YELLOW2, //!< YELLOW2
    ORANGE1, //!< ORANGE1
    ORANGE2, //!< ORANGE2
    PURPLE1, //!< PURPLE1
    PURPLE2, //!< PURPLE2
    BLUE1,   //!< BLUE1
    BLUE2,   //!< BLUE2
    GREEN1,  //!< GREEN1
    GREEN2,  //!< GREEN2
    WHITE,   //!< WHITE
    BLACK    //!< BLACK
} COLOR_INDEX;

/**
 * Store a list of color in uint16_t
 */
extern const uint16_t COLOR_CODE[14];

#endif /* IMAGE_H_ */
