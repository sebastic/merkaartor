#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDomElement>

#include "Maps/Coord.h"
#include "Maps/Projection.h"

class MapViewPrivate;

class MapView : public QWidget
{
Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    ~MapView();

public:
    void drawScale(QPainter & P);
    void drawGPS(QPainter & P);

    void setViewport(const CoordBox & TargetMap);
    void setViewport(const CoordBox & TargetMap, const QRect & Screen);
    CoordBox viewport() const;
    void viewportRecalc(const QRect & Screen);
    QPoint toView(const Coord& aCoord) const;

    double pixelPerM() const;
    void setCenter(Coord & Center, const QRect & /*Screen*/);

    void zoom(double d, const QPoint & Around);
    void zoom(double d, const QPoint & Around, const QRect & Screen);

    void resize(QSize oldS, QSize newS);

    bool toXML(QDomElement xParent);
    void fromXML(const QDomElement p);

    void invalidate();

protected slots:
    void panScreen(QPoint delta);

protected:
    MapViewPrivate* p;

    void paintEvent(QPaintEvent * anEvent);
    void transformCalc(QTransform& theTransform, const Projection& theProjection, const CoordBox& TargetMap, const QRect& Screen);

private:
    void updateStaticBuffer();

signals:

public slots:
    virtual void on_MoveLeft_activated();
    virtual void on_MoveRight_activated();
    virtual void on_MoveUp_activated();
    virtual void on_MoveDown_activated();
    virtual void on_ZoomIn_activated();
    virtual void on_ZoomOut_activated();

};

#endif // MAPVIEW_H
