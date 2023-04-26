/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row = theSource.getRows();
    int col = theSource.getColumns();

    MosaicCanvas * canvas = new MosaicCanvas(row, col);

    
    vector<Point<3>> avg_C;
    map<Point<3>, unsigned> M_avg_C;


    populateAvgColorsMapAndVector(theTiles, M_avg_C, avg_C);

    KDTree<3> tileTree(avg_C);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Point<3> nearest = tileTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)));
            unsigned tileInd = M_avg_C[nearest];
            canvas->setTile(i, j, &(theTiles[tileInd]));
        }
    }

    return canvas;
}

void populateAvgColorsMapAndVector(const vector<TileImage> & theTiles,
                                   map<Point<3>, unsigned> & avgColors_Map,
                                   vector<Point<3>> & avgColors) {
    unsigned index = 0;
    for (auto & tile : theTiles) {
        Point<3> avgColor = convertToXYZ(tile.getAverageColor());
        avgColors_Map[avgColor] = index;
        avgColors.push_back(avgColor);
        index++;
    }
}