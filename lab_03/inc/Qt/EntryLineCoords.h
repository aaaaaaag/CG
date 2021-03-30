//
// Created by denis on 14.03.2021.
//

#ifndef LAB_03_ENTRYLINECOORDS_H
#define LAB_03_ENTRYLINECOORDS_H

#include "QGridLayout"
#include "ICoordsGetter.h"
#include "Qt/IConverter.h"

class EntryLineCoords: public QGridLayout, public ICoordsGetter{
public:

    explicit EntryLineCoords();

    bool GetStartCoord(dot& res) override;

    bool GetEndCoord(dot& res) override;

    IConverter* mXStartLine;
    IConverter* mYStartLine;
    IConverter* mXEndLine;
    IConverter* mYEndLine;
};


#endif //LAB_03_ENTRYLINECOORDS_H
