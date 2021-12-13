/*
 * image.h
 *
 *  Created on: Sep 11, 2020
 *      Author: Joe Krachey
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>

extern const uint8_t jet_fighterBitmaps[];
extern const uint8_t jet_fighterWidthPixels;
extern const uint8_t jet_fighterHeightPixels;

extern const uint8_t ufo1Bitmaps[];
extern const uint8_t ufo1WidthPixels;
extern const uint8_t ufo1HeightPixels;

extern const uint8_t ufo2Bitmaps[];
extern const uint8_t ufo2WidthPixels;
extern const uint8_t ufo2HeightPixels;

extern const uint8_t bulletBitmaps[];
extern const uint8_t bulletWidthPixels;
extern const uint8_t bulletHeightPixels;

extern const uint8_t skyfighter0Bitmaps[];
extern const uint8_t skyfighter0WidthPixels;
extern const uint8_t skyfighter0HeightPixels;

extern const uint8_t pressstartBitmaps[];
extern const uint8_t pressstartWidthPixels;
extern const uint8_t pressstartHeightPixels;

extern const uint8_t explosionBitmaps[];
extern const uint8_t explosionWidthPixels;
extern const uint8_t explosionHeightPixels;

extern const uint8_t game_overBitmaps[];
extern const uint8_t game_overWidthPixels;
extern const uint8_t game_overHeightPixels;

extern const uint8_t you_winBitmaps[];
extern const uint8_t you_winWidthPixels;
extern const uint8_t you_winHeightPixels;

typedef enum {
    RED1 = 0,
    RED2,
    YELLOW1,
    YELLOW2,
    ORANGE1,
    ORANGE2,
    PURPLE1,
    PURPLE2,
    BLUE1,
    BLUE2,
    GREEN1,
    GREEN2,
    WHITE,
    BLACK
} COLOR_INDEX;

extern const uint16_t COLOR_CODE[14];

#endif /* IMAGE_H_ */
