//
//  warpImage.h
//  warpImage
//
//  Created by Ruikun Luo on 11/16/13.
//  Copyright (c) 2013 Ruikun Luo. All rights reserved.
//  Function: warp Face to another image
//  Version: V0.1
//  Modified Date: Nov /17 /2013  21:32
//
#ifndef warpImage_warpImage_h
#define warpImage_warpImage_h
#include "yspng.h"

//warpImage : size the size of area to calculate average color, thredshold: thredshold of similar color
//deBackgroundState:  1: run deBackgroud Algorithm, 0: don't run deBackground Alogrithm
void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation,int size, int thredshold);
void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation);
void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation,int deBackgroundState);
void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation,int deBackgroundState, int size, int thredshold);

#endif
