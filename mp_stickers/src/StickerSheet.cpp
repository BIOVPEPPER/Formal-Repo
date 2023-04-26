#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <cmath>
using namespace std;
using std::cout;
using std::endl;
using std::vector;

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    background = picture;
    X.resize(max);
    Y.resize(max);
    STICKER.resize(max,nullptr);
}

StickerSheet::StickerSheet(const StickerSheet & other){
    copy_(other);
}

void StickerSheet::delete_(vector<Image*> vectors){
    for(unsigned i = 0; i < vectors.size();i++){
        delete vectors[i];
    }
    vectors.clear();
}

void StickerSheet::copy_(StickerSheet const & other){
    delete_(STICKER);
    background = other.background;
    X = other.X;
    Y = other.Y;
    STICKER.resize(other.STICKER.size());
    for(unsigned i = 0; i < STICKER.size();i++){
        if (other.STICKER[i] == nullptr) { 
            break; 
            }
        STICKER[i] = other.STICKER[i];
        //STICKER[i] = other.STICKER[i];
    }
}

void StickerSheet::changeMaxStickers (unsigned max){
    if(max < STICKER.size()){
        // for(unsigned i = max; i < STICKER.size();i++){
        //     delete STICKER[i];
        // }
        STICKER.erase(STICKER.begin()+max,STICKER.begin()+STICKER.size());
    }
    STICKER.resize(max,nullptr);
    X.resize(max);
    Y.resize(max);
}

StickerSheet::~StickerSheet () {
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    int mark = 0;
    for(unsigned i = 0; i < STICKER.size();i++){
        if(i == STICKER.size()-1 && STICKER[i] != nullptr){
            int new_size = STICKER.size()+1;
            changeMaxStickers(new_size);
            mark = i+1;
            break;
        }
        if(STICKER[i] == nullptr){
            mark = i;
            break;
        }
    
    }
    // unsigned mark = 0;
    // while (STICKER[mark] != nullptr) {
    //     mark++;
    //     if (mark == STICKER.size()) {
    //         return -1;
    //     }
    // }
    STICKER[mark] = &sticker;
    std::cout << STICKER[mark] << std::endl;
    X[mark] = x;
    Y[mark] = y;
    return mark;
}

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
    if(layer < 0 || layer >= STICKER.size()){
        return -1;
    }

    for(unsigned i = 0; i < STICKER.size();i++){
         if(i == layer){
            //Image * pointer_sticker = sticker;
            STICKER[i] =&sticker;
            X[i] = x;
            Y[i] = y;
         }
    }
   return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y){
    if(STICKER[index] == nullptr || index > STICKER.size()-1){
        return false;
    }else{
        X[index] = x;
        Y[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker (unsigned index){
    if(index < 0 || index > STICKER.size()-1 || STICKER[index] == nullptr){
        std::cout << "Invalid!" << std::endl;
    }else{
        //delete STICKER[index];
        STICKER.erase(STICKER.begin()+index);
        X.erase(X.begin()+index);
        Y.erase(Y.begin()+index);
    }
}

Image * StickerSheet::getSticker (unsigned index){
    if((index > STICKER.size() -1)||(STICKER[index] == nullptr||index < 0)){
        return NULL;
    }

    return STICKER[index];
}

int StickerSheet::layers () const{
    // unsigned idx = 0;
    // int count = 0;
    // while (idx < STICKER.size()) {
    //     idx++;
    //     if(STICKER[idx] != 0){
    //         count++;
    //     }
    // }
    // std::cout << count << std::endl;
    // return count;
    return X.size();
}


Image StickerSheet::render () const{
    int width_r = background.width();
    int height_r = background.height();
    int count = 0;
    int sheetCoorX;
    int sheetCoorY;
    // if(STICKER.size() != 0){
    // for(unsigned i = 0; i < STICKER.size();i++){
    //     if(STICKER[i] == 0){
    //         count = i;
    //         break;
    //     }else{
    //         width_r = fmax(width_r, X[i]+STICKER[i]->width());
    //         height_r = fmax(height_r,Y[i]+STICKER[i]->height());
    //     }
    // }
    // }
    std::cout << "I got here, 1" << std::endl;
    //Go through all of the stickers and adjust width and length for the canvas
    if (STICKER.size() != 0) {
        while (STICKER[count] != nullptr) {
            
            int wid = STICKER[count]->width();
            int hei = STICKER[count]->height();
            int x_c = X[count];
            std::cout << x_c << std::endl;
            int y_c = Y[count];
            if(x_c >= 0){
            width_r = fmax(width_r, (std::abs(x_c) + std::abs(wid)));
            }else{
                width_r = width_r + std::abs(x_c);
            }

            if(y_c >= 0){
            height_r = fmax(height_r, (std::abs(y_c) + std::abs(hei)));
            }else{
                height_r = height_r + std::abs(y_c);
            }
            count ++;
            if (count == int(STICKER.size())) { break;}
    } 
    }
    std::cout << "I got here, 2" << std::endl;
    //Copy the background picture to the base
    std::cout << width_r << std::endl;
    std::cout << height_r << std::endl;

    Image sheet = Image(width_r,height_r);

    for(unsigned x = 0; x < background.width();x++){
        for(unsigned y = 0; y < background.height(); y++){
            const cs225::HSLAPixel & base_pixel = background.getPixel(x,y);
            int offsetx = width_r-(background.width());
            int offsety = height_r-(background.height());
            cs225::HSLAPixel & sheet_pixel = sheet.getPixel(offsetx+x,offsety+y);
            sheet_pixel = base_pixel;

        }
    }
    std::cout << "I got here, 3" << std::endl;
    //Go through the stickers, copy them on sheet
    std::cout << "This is all of the X" << std::endl;
    for (int i = 0; i < int(X.size()); i++) {
        std::cout << int(X[i]) << " ";
    }
    for(int i = 0; i < count; i++){
        for(int j = 0; j < int(STICKER[i]->width());j++){
            for(int t = 0; t < int(STICKER[i]->height());t++){
                cs225::HSLAPixel & stickerPixel = STICKER[i]->getPixel(j, t);
                if(int(X[i]) > 0){
                    // std::cout << "This is X when X[i] > 0" << std::endl;
                    // std::cout << X[i] << std::endl;
                    // std::cout << "This is j when X[i] > 0" << std::endl;
                    // std::cout << j << std::endl;
                    sheetCoorX = int(X[i])+j;
                }else{
                    // std::cout << "This is X when X[i] < 0" << std::endl;
                    // std::cout << X[i] << std::endl;
                    // std::cout << "This is j when X[i] < 0" << std::endl;
                    // std::cout << j << std::endl;
                    sheetCoorX = j;
                }

                if(int(Y[i]) > 0){
                    // std::cout << "This is Y when Y[i] > 0" << std::endl;
                    // std::cout << Y[i] << std::endl;

                    sheetCoorY = int(Y[i])+t;
                }else{
                    // std::cout << "This is Y when Y[i] < 0" << std::endl;
                    // std::cout << Y[i] << std::endl;
                    sheetCoorY = t;
                }
                // std::cout << "Reached here in Render!" << std::endl;
                // std::cout << sheetCoorX << std::endl;
                // std::cout << sheetCoorY << std::endl;
                cs225::HSLAPixel & sheetPixel_ = sheet.getPixel(sheetCoorX,sheetCoorY);
                if(stickerPixel.a != 0){
                sheetPixel_ = stickerPixel;
                }
            }
        }
    }
    std::cout << "I got here, 4" << std::endl;
    return sheet;
}

const StickerSheet & StickerSheet::operator= (const StickerSheet & other){
    if(this != &other){
        copy_(other);
    }
    return *this;
}