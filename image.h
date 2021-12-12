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

extern const uint8_t bulletBitmaps[];
extern const uint8_t bulletWidthPixels;
extern const uint8_t bulletHeightPixels;

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
