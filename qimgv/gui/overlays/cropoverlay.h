#ifndef CROPOVERLAY_H
#define CROPOVERLAY_H

#include "gui/customwidgets/overlaywidget.h"
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

enum CursorAction {
    NO_DRAG,          // 0
    SELECTION_START,  // 1
    DRAG_SELECT,      // 2
    DRAG_MOVE,        // 3
    DRAG_LEFT,        // 4
    DRAG_RIGHT,       // 5
    DRAG_TOP,         // 6
    DRAG_BOTTOM,      // 7
    DRAG_TOPLEFT,     // 8
    DRAG_TOPRIGHT,    // 9
    DRAG_BOTTOMLEFT,  // 10
    DRAG_BOTTOMRIGHT  // 11
};

class CropOverlay : public OverlayWidget
{
    Q_OBJECT
public:
    explicit CropOverlay(OverlayContainerWidget *parent = nullptr);
    void setImageDrawRect(QRect);
    void setImageRealSize(QSize);
    void setButtonText(QString text);
    void setImageScale(float scale);
    void clearSelection();

signals:
    void positionChanged(float x, float y);
    void selectionChanged(QRect);
    void escPressed();
    void enterPressed();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QPoint startPos, endPos, moveStartPos, resizeAnchor;
    QRect imageRect, imageDrawRect, selectionRect, selectionDrawRect, handles[8];
    bool lockAspectRatio;
    float scale;
    QBrush brushInactiveTint, brushDarkGray, brushGray, brushLightGray;
    QRectF selectionDrawRectDpi, handlesDpi[8];
    int handleSize;
    QImage *drawBuffer;
    CursorAction cursorAction;
    QPen selectionOutlinePen;
    qreal dpr;
    QPointF ar;

    QPoint setInsidePoint(QPoint, QRect);
    QRect placeInside(QRect what, QRect where);
    void drawSelection(QPainter*);
    void drawHandles(QBrush&, QPainter*);
    void updateHandlePositions();
    void prepareDrawElements();
    CursorAction hoverTarget(QPoint pos);
    void resizeSelection(QPoint d);
    void resizeSelectionAR(QPoint d);
    void resizeSelectionFree(QPoint d);
    void recalculateGeometry();
    QPoint mapPointToImage(QPoint p);
    void updateSelectionDrawRect();
    void setCursorAction(CursorAction action);
    void setResizeAnchor(CursorAction action);
    bool hasSelection();
public slots:
    void show();
    void hide();
    void onSelectionOutsideChange(QRect selection);
    void selectAll();
    void setAspectRatio(QPointF);
    void setLockAspectRatio(bool mode);
};

#endif // CROPOVERLAY_H
