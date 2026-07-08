#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

enum class FigureType { None, Line, Rectangle, Ellipse, Eraser};

class CustomScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit CustomScene(QObject* parent = nullptr);
    void setDrawingType(FigureType type);
    void setColors(QColor line, QColor fill);
    void setLineWidth(int width);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    FigureType currentType;
    QPointF startPoint;

    QGraphicsLineItem* tempLine;
    QGraphicsRectItem* tempRect;
    QGraphicsEllipseItem* tempEllipse;
    QColor lineColor = Qt::black;
    QColor fillColor = Qt::transparent;
    int lineWidth = 2; 


    void updateDrawing(QPointF currentPoint);
};
