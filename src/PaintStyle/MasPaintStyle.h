#ifndef MERKAARTOR_EDITPAINTSTYLE_H_
#define MERKAARTOR_EDITPAINTSTYLE_H_

#include "IPaintStyle.h"
#include "Painter.h"

class MapView;

#include <QList>

class MasPaintStyle : public IPaintStyle
{
public:
    MasPaintStyle();
    virtual ~MasPaintStyle();

    int painterSize();
    const GlobalPainter& getGlobalPainter() const;
    void setGlobalPainter(GlobalPainter aGlobalPainter);
    const Painter* getPainter(int i) const;
    QList<Painter> getPainters() const;
    void setPainters(QList<Painter> aPainters);
    bool isDirty();

    QString getFilename();
    void savePainters(const QString& filename);
    void loadPainters(const QString& filename);

private:
    bool m_isDirty;
    QString m_filename;
    QList<Painter> Painters;
    GlobalPainter globalPainter;
};

#endif
