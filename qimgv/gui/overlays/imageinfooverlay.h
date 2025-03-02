#ifndef IMAGEINFOOVERLAY_H
#define IMAGEINFOOVERLAY_H

#include "gui/customwidgets/floatingwidget.h"
#include <QWheelEvent>

namespace Ui {
class ImageInfoOverlay;
}

class ImageInfoOverlay : public FloatingWidget
{
    Q_OBJECT

public:
    explicit ImageInfoOverlay(OverlayContainerWidget *parent = nullptr);
    ~ImageInfoOverlay();
    void setExifInfo(QMap<QString, QString>);

protected:
    void wheelEvent(QWheelEvent *event);
private:
    Ui::ImageInfoOverlay *ui;
};

#endif // IMAGEINFOOVERLAY_H
