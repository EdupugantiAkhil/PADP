// use gd to change an image to black and white
// compile with: g++ 4.cpp -o 4 `pkg-config --cflags --libs opencv`

#include<bits/stdc++.h>
#include<gd.h>
#include<omp.h>

using namespace std;

int main()
{
    FILE *in, *out; 
    gdImagePtr im;

    in = fopen("image.png", "rb");
    out = fopen("image-out.jpg", "wb");

    im = gdImageCreateFromPng(in);
    int width = gdImageSX(im);
    int height = gdImageSY(im);
    int color;
    int red, green, blue;
    int gray;
    #pragma omp parallel for
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            color = gdImageGetPixel(im, i, j);
            red = gdImageRed(im, color);
            green = gdImageGreen(im, color);
            blue = gdImageBlue(im, color);
            gray = (red+green+blue)/3;
            color = gdImageColorAllocate(im, gray, gray, gray);
            gdImageSetPixel(im, i, j, color);
        }
    }
    gdImageJpeg(im, out, -1);
    fclose(in);
    fclose(out);
    return 0;
}
