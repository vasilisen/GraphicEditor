#include "customscene.h"
#include <QPen>
#include <QBrush>

CustomScene::CustomScene(QObject* parent)
    : QGraphicsScene(parent), currentType(FigureType::None),
    tempLine(nullptr), tempRect(nullptr), tempEllipse(nullptr) {
}

void CustomScene::setDrawingType(FigureType type) {
    currentType = type;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() != Qt::LeftButton || currentType == FigureType::None) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    startPoint = event->scenePos();
    QPen pen(Qt::black, 2);
    QBrush brush(Qt::transparent); 

    if (currentType == FigureType::Line) {
        tempLine = addLine(QLineF(startPoint, startPoint), pen);
    }
    else if (currentType == FigureType::Rectangle) {
        tempRect = addRect(QRectF(startPoint, QSizeF(0, 0)), pen, brush);
    }
    else if (currentType == FigureType::Ellipse) {
        tempEllipse = addEllipse(QRectF(startPoint, QSizeF(0, 0)), pen, brush);
    }
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (currentType == FigureType::None) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    updateDrawing(event->scenePos());
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() != Qt::LeftButton) {
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    updateDrawing(event->scenePos());

    tempLine = nullptr;
    tempRect = nullptr;
    tempEllipse = nullptr;
}

void CustomScene::updateDrawing(QPointF currentPoint) {
    if (currentType == FigureType::Line && tempLine) {
        tempLine->setLine(QLineF(startPoint, currentPoint));
    }
    else if (currentType == FigureType::Rectangle && tempRect) {
        QRectF rect(startPoint, currentPoint);
        tempRect->setRect(rect.normalized());
    }
    else if (currentType == FigureType::Ellipse && tempEllipse) {
        QRectF rect(startPoint, currentPoint);
        tempEllipse->setRect(rect.normalized());
    }
}
