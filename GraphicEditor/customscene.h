#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

enum class FigureType { None, Line, Rectangle, Ellipse };

class CustomScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit CustomScene(QObject* parent = nullptr);
    void setDrawingType(FigureType type);

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

    void updateDrawing(QPointF currentPoint);
};
