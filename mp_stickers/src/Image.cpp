#include "Image.h"
#include <cmath>
using namespace cs225;

Image::Image():PNG(){};

Image::Image(unsigned int width,unsigned int height):PNG(width,height){
};

// Image::~Image(){
//     delete[] imageData_; 
// }

void Image::lighten(){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.l = std::fmin(thispixel.l+0.1,1);

        }
    }
}

void Image::lighten(double amount){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.l = std::fmin(thispixel.l+amount,1);

        }
    }
}

void Image::darken(){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.l = std::fmax(thispixel.l-0.1,0);

        }
    }
}


void Image::darken(double amount){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.l = std::fmax(thispixel.l-amount,0);

        }
    }
}

void Image::saturate(){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.s = std::fmin(thispixel.s+0.1,1);
        }
    }
}

void Image::saturate(double amount){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.s = std::fmin(thispixel.s+amount,1);
        }
    }
}


void Image::desaturate(){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.s = std::fmax(thispixel.s-0.1,0);
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.s = std::fmax(thispixel.s-amount,0);
        }
    }
}


void Image::grayscale(){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            thispixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned i =0;i < this->width();i++){
        for(unsigned j = 0;j<this->height();j++){
            HSLAPixel & thispixel = this->getPixel(i,j);
            double tmp = thispixel.h + degrees;
            if(tmp > 360){
                //positive rotate
                int ad = tmp / 360;
                tmp -= ad * 360;

            }else if(tmp < 0){
                //negative rotate 
                int ad = std::abs(tmp) / 360;
                tmp += (ad)*360;
                tmp += 360;
            }
            thispixel.h = tmp;
        }
    }
}

void Image::illinify(){
for(unsigned i =0;i < this->width();i++){
    for(unsigned j = 0;j<this->height();j++){
        HSLAPixel & thispixel = this->getPixel(i,j);
        int orange = fmin(std::abs(thispixel.h-11),std::abs(360-std::abs(thispixel.h-11)));
        int blue = fmin(std::abs(thispixel.h-216),std::abs(360-std::abs(thispixel.h-216)));
        //which is smaller, illinify to which
        if(blue < orange){
            thispixel.h = 216;
        }else{
            thispixel.h = 11;
        }
    }
}
}

void Image::scale(double factor){
    unsigned width_new = this->width() * factor;
    unsigned height_new = this->height() * factor;
    HSLAPixel *pixels = new HSLAPixel[width_new * height_new];
    for (unsigned i = 0; i < width_new;i++){
        for (unsigned j = 0; j < height_new;j++){
            int original_i = i/factor;
            int original_j = j/factor;
            HSLAPixel & original_pixel = this->getPixel(original_i,original_j);
            int tobeadd = j*width_new;
            HSLAPixel & new_pixel = pixels[i+tobeadd];
            new_pixel = original_pixel;
        }
    }
    this->resize(width_new,height_new);
    for(unsigned x =0; x < width_new;x++){
        for(unsigned y = 0; y < height_new;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            int tobeadd_2 = y*width_new;
             HSLAPixel & new2_pixel_ = pixels[x+tobeadd_2];
             pixel = new2_pixel_;
        }
    }
    delete[] pixels;
}

void Image::scale(unsigned w,unsigned h){
    double factor;
    unsigned width_new;
    unsigned height_new;
    unsigned width_tbd;
    unsigned height_tbd;
    std::cout << "This is original height" << std::endl;
    std::cout << double(this->height()) << std::endl;
    std::cout << "This is original width" << std::endl;
    std::cout << double(this->width()) << std::endl;
    double ratio_w = double(w)/double(this->width());
    double ratio_h = double(h)/double(this->height());
    if(ratio_w * double(this->height()) <= h){
        width_new = w;
        height_new = ratio_w * double(this->height());
        if(ratio_h * double(this->width()) <= w){
            width_tbd = ratio_h * double(this->width());
            height_tbd = h;
            if(width_tbd * height_tbd > width_new * height_new){
                width_new = width_tbd;
                height_new = height_tbd;
                factor = ratio_h;
            }else{
                factor = ratio_w;
            }
        }else{
            factor = ratio_w;
        }
    }else{
        width_new = ratio_h * double(this->width());
        height_new = h;
        factor = ratio_h;
    }
    // double compare_w;
    // double compare_h;
    // // double dist_w = std::abs(ratio_w - 1);
    // // double dist_h = std::abs(ratio_h - 1);
    // if(ratio_w < 1){
    //     compare_w = 1/ ratio_w;
    // } else{
    //     compare_w = ratio_w / 1;
    // }

    // if(ratio_h < 1){
    //     compare_h = 1 / ratio_h;
    // }else{
    //     compare_h = ratio_h /1;
    // }
    // double factor;
    // unsigned width_new;
    // unsigned height_new;
    // if(compare_w < compare_h){
    //     factor = ratio_w;
    //     width_new = w;
    //     height_new = unsigned(this->height() * ratio_w);
    // }else{
    //     factor = ratio_h;
    //     width_new = unsigned(this->width()*ratio_h);
    //     height_new = h;
    // }

    std::cout << "This is height_new" << std::endl;
    std::cout << height_new << std::endl;
    std::cout <<"This is width_new" << std::endl;
    std::cout << width_new << std::endl;
    std::cout <<"This is factor" << std::endl;
    std::cout << factor << std::endl;
    HSLAPixel *pixels = new HSLAPixel[width_new * height_new];
    for (unsigned i = 0; i < width_new;i++){
        for (unsigned j = 0; j < height_new;j++){
            unsigned original_i = i/factor;
            unsigned original_j = j/factor;
            HSLAPixel & original_pixel = this->getPixel(original_i,original_j);
            int tobeadd = j*width_new;
            HSLAPixel & new_pixel = pixels[i+tobeadd];
            new_pixel = original_pixel;
        }
    }
    this->resize(width_new,height_new);
    for(unsigned x =0; x < width_new;x++){
        for(unsigned y = 0; y < height_new;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            unsigned tobeadd_2 = y*width_new;
            pixel = pixels[x+tobeadd_2];
        }
    }
    delete[] pixels;


}