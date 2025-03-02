#ifndef SCALERREQUEST_H
#define SCALERREQUEST_H

#include <QPixmap>
#include "sourcecontainers/image.h"
#include "settings.h" // move enums somewhere else?

class ScalerRequest {
public:
    ScalerRequest() : image(nullptr), size(QSize(0,0)), filter(FILTER_BILINEAR) { }
    ScalerRequest(Image *_image, QSize _size, QString _string, ScalingFilter _filter) : image(_image), size(_size), string(_string), filter(_filter) {}
    Image *image;
    QSize size;
    QString string;
    ScalingFilter filter;

    bool operator==(const ScalerRequest &another) const {
        if(another.image == image && another.size == size && another.filter == filter)
            return true;
        return false;
    }
};

#endif // SCALERREQUEST_H
