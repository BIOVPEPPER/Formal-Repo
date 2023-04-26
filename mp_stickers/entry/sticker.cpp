#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image penguin;
  penguin.readFromFile("../data/penguin.png");

  Image alma;
  alma.readFromFile("../data/alma.png");
  
  Image I;
  I.readFromFile("../data/i.png");

  I.scale(0.5);
  StickerSheet alma_sheet(alma,3);
  alma_sheet.addSticker(penguin,100,100);
  alma_sheet.addSticker(I,300,350);
  alma_sheet.addSticker(penguin,750,250);

  alma_sheet.render().writeToFile("myImage.png");

  return 0;
}
