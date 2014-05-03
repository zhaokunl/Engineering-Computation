//
//  warpImage.cpp
//  warpImage
//
//  Created by Ruikun Luo on 11/16/13.
//  Copyright (c) 2013 Ruikun Luo. All rights reserved.
//  Function: warp Face to another image
//  Version: V0.2
//  Modified Date: Nov /19 /2013  21:32
//  Add: deBackground

//  Version: V0.3
//  Modified Data: Nov /23 /2013  15:14
//  Add: refine and flood fill

//  Version: V0.4
//  Modified Data: Nov /23 /2013   18:15
//  Add: parameter of warp image for the upper level to use
//  Edit: flood fill

//  Version: V0.5
//  Modified Date: Nov /23 /2013  20:35
//  Add: debackground state

#include <stdio.h>
#include <math.h>
#include "warpImage.h"

#define PI 3.141592


bool isSimularColor(unsigned int tempColor[], unsigned char dat[], int threshold){
    int check=0;
    unsigned char *pix=dat;
    for (int i=0; i<3; i++){
        if (fabs((int)pix[i]-(int)(tempColor[i]))>=threshold) {
            check=check+1;
        }
    }
    
    if (check==0) {
        return true;
    }
    pix=NULL;

    delete pix;
    return false;
}
void deBackground(YsRawPngDecoder &image1,int position1[], int size, int thredshold)
{
    //leave for now
    unsigned int lu[3];
    unsigned int ru[3];
    unsigned int ld[3];
    unsigned int rd[3];

    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[0]+x+(position1[1]+1)*image1.wid)*4+i]);
            }
            
        }
        lu[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[2]-x+(position1[1]+y)*image1.wid)*4+i]);
            }
        }
        ru[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[2]-x+(position1[3]-y)*image1.wid)*4+i]);
            }
        }
        rd[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size;y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[0]+x+(position1[3]-y)*image1.wid)*4+i]);
            }
        }
        ld[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    
    int face_x=position1[2]-position1[0];
    int face_y=position1[3]-position1[1];
    
    
    //left up corner
    for (int y=position1[1]; y<position1[1]+face_y/3; y++) {
        for (int x=position1[0]; x<position1[0]+face_x/4; x++) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(lu, pix, thredshold)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }
    
    //right up corner
    for (int y=position1[1]; y<position1[1]+face_y/3; y++) {
        for (int x=position1[2]; x>position1[2]-face_x/4; x--) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(ru, pix, thredshold)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }
    
    //right down corner
    for (int y=position1[3]; y>position1[3]-face_y/3; y--) {
        for (int x=position1[2]; x>position1[2]-face_x/4; x--) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(rd, pix, thredshold)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }
    
    //left down corner
    for (int y=position1[3]; y>position1[3]-face_y/3; y--) {
        for (int x=position1[0]; x<position1[0]+face_x/4; x++) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(ld, pix, thredshold)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }
    
    
    
    
}
void FloodFill(YsRawPngDecoder &image1,int position1[],unsigned int tempColor[], int threshold,int px, int py)
{
    unsigned char *pix=image1.rgba+(py*image1.wid+px)*4;
    unsigned int whiteColor[3];
    whiteColor[0]=255;
    whiteColor[1]=255;
    whiteColor[2]=255;
    if (isSimularColor(tempColor, pix, threshold)&&~isSimularColor(whiteColor, pix,0)) {
        image1.rgba[(py*image1.wid+px)*4]=255;
        image1.rgba[(py*image1.wid+px)*4+1]=255;
        image1.rgba[(py*image1.wid+px)*4+2]=255;
    }else{
        return;
    }
    
    if ((px+1)<=position1[2]) {
        FloodFill(image1, position1, tempColor, threshold, px+1, py);
    }
    if ((px-1)>=position1[0]) {
        FloodFill(image1, position1, tempColor, threshold, px-1, py);
    }
    if ((py+1)<=position1[3]) {
        FloodFill(image1, position1, tempColor, threshold, px, py+1);
    }
    if ((py-1)>=position1[1]) {
        FloodFill(image1, position1, tempColor, threshold, px, py-1);
    }
    
    pix=NULL;
    delete pix;
}
void deBackgroundFloodFill(YsRawPngDecoder &image1,int position1[],int size, int thredshold)
{
    //leave for now
    unsigned int lu[3];
    unsigned int ru[3];
    unsigned int ld[3];
    unsigned int rd[3];
    
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[0]+x+(position1[1]+1)*image1.wid)*4+i]);
            }
            
        }
        lu[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[2]-x+(position1[1]+y)*image1.wid)*4+i]);
            }
        }
        ru[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size; y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[2]-x+(position1[3]-y)*image1.wid)*4+i]);
            }
        }
        rd[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    for (int i=0;i<3;i++){
        unsigned int pp=0;
        for (int x=0; x<size; x++) {
            for (int y=0; y<size;y++) {
                pp=pp+(unsigned int)(image1.rgba[(position1[0]+x+(position1[3]-y)*image1.wid)*4+i]);
            }
        }
        ld[i]=(unsigned int)((double)pp/(size*size));
        pp=0;
    }
    
    //int face_x=position1[2]-position1[0];
    //int face_y=position1[3]-position1[1];
    
    
    //left up corner
    
    FloodFill(image1, position1, lu, thredshold, position1[0], position1[1]);
    /*for (int y=position1[1]; y<position1[1]+face_y/3; y++) {
        for (int x=position1[0]; x<position1[0]+face_x/4; x++) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(lu, pix, 5)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }*/
    
    //right up corner
    FloodFill(image1, position1, ru, thredshold, position1[2], position1[1]);
   /* for (int y=position1[1]; y<position1[1]+face_y/3; y++) {
        for (int x=position1[2]; x>position1[2]-face_x/4; x--) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(ru, pix, 5)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }*/
    
    //right down corner
    FloodFill(image1, position1, rd, thredshold, position1[2], position1[3]);
   /* for (int y=position1[3]; y>position1[3]-face_y/3; y--) {
        for (int x=position1[2]; x>position1[2]-face_x/4; x--) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(rd, pix, 5)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }*/
    
    //left down corner
    FloodFill(image1, position1, ld, thredshold, position1[0], position1[3]);
    /*
    for (int y=position1[3]; y>position1[3]-face_y/3; y--) {
        for (int x=position1[0]; x<position1[0]+face_x/4; x++) {
            unsigned char *pix=image1.rgba+(y*image1.wid+x)*4;
            if (isSimularColor(ld, pix, 5)) {
                image1.rgba[(y*image1.wid+x)*4]=255;
                image1.rgba[(y*image1.wid+x)*4+1]=255;
                image1.rgba[(y*image1.wid+x)*4+2]=255;
            }
        }
    }*/
    
    
    
    
}

/*
void refineImage(YsRawPngDecoder &image1,YsRawPngDecoder &image2,int position1[],int position2[],double rotation)
{
    //resize
    double wid1=(double)(position1[2]-position1[0]+1);
    double wid2=(double)(position2[2]-position2[0]+1);
    double hei1=(double)(position1[3]-position1[1]+1);
    double hei2=(double)(position2[3]-position2[1]+1);
    //unsigned char resizedImg[(int)(wid2*hei2*4)];
    rotation=rotation/180*PI;
    double wid_ratio=wid1/wid2;
    double hei_ratio=hei1/hei2;
    double trans2_x=-wid2/2;
    double trans2_y=-hei2;
    
    int min_x=image2.wid;
    int min_y=image2.hei;
    int max_x=0;
    int max_y=0;
    
    int x_img2=(int)((position1[0]+trans2_x)*cos(rotation)+(position1[1]+trans2_y)*sin(rotation)-trans2_x+position2[0]);
    int y_img2=(int)(-(position1[0]+trans2_x)*sin(rotation)+(position1[1]+trans2_y)*cos(rotation)-trans2_y+position2[1]);
    min_x=min_x<=x_img2?min_x:x_img2;
    min_y=min_y<=y_img2?min_y:y_img2;
    max_x=max_x>=x_img2?max_x:x_img2;
    max_y=max_y>=y_img2?max_y:y_img2;
    
    x_img2=(int)((position1[2]+trans2_x)*cos(rotation)+(position1[1]+trans2_y)*sin(rotation)-trans2_x+position2[0]);
    y_img2=(int)(-(position1[2]+trans2_x)*sin(rotation)+(position1[1]+trans2_y)*cos(rotation)-trans2_y+position2[1]);
    min_x=min_x<=x_img2?min_x:x_img2;
    min_y=min_y<=y_img2?min_y:y_img2;
    max_x=max_x>=x_img2?max_x:x_img2;
    max_y=max_y>=y_img2?max_y:y_img2;
    
    x_img2=(int)((position1[2]+trans2_x)*cos(rotation)+(position1[3]+trans2_y)*sin(rotation)-trans2_x+position2[0]);
    y_img2=(int)(-(position1[2]+trans2_x)*sin(rotation)+(position1[3]+trans2_y)*cos(rotation)-trans2_y+position2[1]);
    min_x=min_x<=x_img2?min_x:x_img2;
    min_y=min_y<=y_img2?min_y:y_img2;
    max_x=max_x>=x_img2?max_x:x_img2;
    max_y=max_y>=y_img2?max_y:y_img2;
    
    x_img2=(int)((position1[0]+trans2_x)*cos(rotation)+(position1[3]+trans2_y)*sin(rotation)-trans2_x+position2[0]);
    y_img2=(int)(-(position1[0]+trans2_x)*sin(rotation)+(position1[3]+trans2_y)*cos(rotation)-trans2_y+position2[1]);
    min_x=min_x<=x_img2?min_x:x_img2;
    min_y=min_y<=y_img2?min_y:y_img2;
    max_x=max_x>=x_img2?max_x:x_img2;
    max_y=max_y>=y_img2?max_y:y_img2;
    
    for (int x=0; x<wid2; x++) {
        for (int y=0; y<hei2; y++) {
           // if ((image2.rgba[(y*image2.wid+x)*4]==255)&&(image2.rgba[(y*image2.wid+x)*4+1]==255)&&(image2.rgba[(y*image2.wid+x)*4+2]==255)) {
            
            //int x_img2=(int)((x+trans2_x)*cos(rotation)+(y+trans2_y)*sin(rotation)-trans2_x+position2[0]);
            //int y_img2=(int)(-(x+trans2_x)*sin(rotation)+(y+trans2_y)*cos(rotation)-trans2_y+position2[1]);
            
                image2.rgba[(y*image2.wid+x)*4]=(int)((image2.rgba[(y*image2.wid+x-1)*4]+image2.rgba[(y*image2.wid+x+1)*4]+image2.rgba[((y-1)*image2.wid+x-1)*4]+image2.rgba[((y+1)*image2.wid+x-1)*4])/4);
                image2.rgba[(y*image2.wid+x)*4+1]=(int)((image2.rgba[(y*image2.wid+x-1)*4+1]+image2.rgba[(y*image2.wid+x+1)*4+1]+image2.rgba[((y-1)*image2.wid+x-1)*4+1]+image2.rgba[((y+1)*image2.wid+x-1)*4+1])/4);
                image2.rgba[(y*image2.wid+x)*4+2]=(int)((image2.rgba[(y*image2.wid+x-1)*4+2]+image2.rgba[(y*image2.wid+x+1)*4+2]+image2.rgba[((y-1)*image2.wid+x-1)*4+2]+image2.rgba[((y+1)*image2.wid+x-1)*4+2])/4);
                image2.rgba[(y*image2.wid+x)*4+3]=(int)((image2.rgba[(y*image2.wid+x-1)*4+3]+image2.rgba[(y*image2.wid+x+1)*4+3]+image2.rgba[((y-1)*image2.wid+x-1)*4+3]+image2.rgba[((y+1)*image2.wid+x-1)*4+3])/4);
                
           // }
        }
    }
    
}
 */
void warp(YsRawPngDecoder &image1,YsRawPngDecoder &image2,int position1[], int position2[],double rotation)
{
    //resize
    double wid1=(double)(position1[2]-position1[0]+1);
    double wid2=(double)(position2[2]-position2[0]+1);
    double hei1=(double)(position1[3]-position1[1]+1);
    double hei2=(double)(position2[3]-position2[1]+1);
    //unsigned char resizedImg[(int)(wid2*hei2*4)];
    rotation=rotation/180*PI;
    double wid_ratio=wid1/wid2;
    double hei_ratio=hei1/hei2;
    double trans2_x=-wid2/2;
    double trans2_y=-hei2;
    for (int y=0; y<hei2; y++) {
        for (int x=0; x<wid2; x++) {
            int x_img1=int(x*wid_ratio)+position1[0];
            int y_img1=int(y*hei_ratio)+position1[1];
            
            int x_img2=(int)((x+trans2_x)*cos(rotation)+(y+trans2_y)*sin(rotation)-trans2_x+position2[0]);
            int y_img2=(int)(-(x+trans2_x)*sin(rotation)+(y+trans2_y)*cos(rotation)-trans2_y+position2[1]);
            printf("x:%d  y:%d\n",x_img1,y_img1);
            //resizedImg[y*(int)wid2+x]=image1.rgba[y_img1*(int)wid1+x_img1];
            //resizedImg[y*(int)wid2+x+1]=image1.rgba[y_img1*(int)wid1+x_img1+1];
            //resizedImg[y*(int)wid2+x+2]=image1.rgba[y_img1*(int)wid1+x_img1+2];
            //resizedImg[y*(int)wid2+x+3]=image1.rgba[y_img1*(int)wid1+x_img1+3];
            //unsigned char *pix=image2.rgba+(y_img2*image2.wid+x_img2)*4;
            //unsigned char *pix1=image1.rgba+(y_img1*(int)wid1+x_img1)*4;
            if ((image1.rgba[(y_img1*image1.wid+x_img1)*4]!=255)||(image1.rgba[(y_img1*image1.wid+x_img1)*4+1]!=255)||(image1.rgba[(y_img1*image1.wid+x_img1)*4+2]!=255)) {
                
            
                image2.rgba[(y_img2*image2.wid+x_img2)*4]=image1.rgba[(y_img1*image1.wid+x_img1)*4];
                image2.rgba[(y_img2*image2.wid+x_img2)*4+1]=image1.rgba[(y_img1*image1.wid+x_img1)*4+1];
                image2.rgba[(y_img2*image2.wid+x_img2)*4+2]=image1.rgba[(y_img1*image1.wid+x_img1)*4+2];
                image2.rgba[(y_img2*image2.wid+x_img2)*4+3]=image1.rgba[(y_img1*image1.wid+x_img1)*4+3];
                
                image2.rgba[(y_img2*image2.wid+x_img2+1)*4]=image1.rgba[(y_img1*image1.wid+x_img1)*4];
                image2.rgba[(y_img2*image2.wid+x_img2+1)*4+1]=image1.rgba[(y_img1*image1.wid+x_img1)*4+1];
                image2.rgba[(y_img2*image2.wid+x_img2+1)*4+2]=image1.rgba[(y_img1*image1.wid+x_img1)*4+2];
                image2.rgba[(y_img2*image2.wid+x_img2+1)*4+3]=image1.rgba[(y_img1*image1.wid+x_img1)*4+3];
                
            }
            //pix[0]=image1.rgba[(y_img1*(int)wid1+x_img1)*4];
            //pix[1]=image1.rgba[(y_img1*(int)wid1+x_img1)*4+1];
            //pix[2]=image1.rgba[(y_img1*(int)wid1+x_img1)*4+2];
            //pix[3]=image1.rgba[(y_img1*(int)wid1+x_img1)*4+3];

        }
    }
    
    
    
}

void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation, int size, int thredshold)
{
    //deBackground(image1,position1, size, thredshold);
    deBackgroundFloodFill(image1, position1,size, thredshold);
    warp(image1,image2,position1,position2,rotation);
   // refineImage(image1, image2,position1, position2, rotation);
}
void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation)
{
    int thredshold=20;
    int size=5;
    //deBackground(image1,position1, size, thredshold);
    deBackgroundFloodFill(image1, position1,size, thredshold);
    warp(image1,image2,position1,position2,rotation);
    // refineImage(image1, image2,position1, position2, rotation);
}

void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation,int deBackgroundState)
{
    int thredshold=20;
    int size=5;
    if (deBackgroundState==1)
    {
        deBackgroundFloodFill(image1, position1, size, thredshold);
    }
    warp(image1,image2,position1,position2,rotation);

}

void warpImage(YsRawPngDecoder &image1, YsRawPngDecoder &image2, int position1[], int position2[], double rotation,int deBackgroundState, int size, int thredshold)
{
    
    if (deBackgroundState==1)
    {
        deBackgroundFloodFill(image1, position1, size, thredshold);
    }
    warp(image1,image2,position1,position2,rotation);
    
}

