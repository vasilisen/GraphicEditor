#include "mainwindow.h"
#include "customscene.h"
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QColorDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    currentLineColor = Qt::black;
    currentFillColor = Qt::transparent;

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    btnLine = new QPushButton("Линия", this);
    btnRect = new QPushButton("Прямоугольник", this);
    btnEllipse = new QPushButton("Овал", this);
    btnSelection = new QPushButton("Курсор", this);
    btnClear = new QPushButton("Очистить всё", this);
    btnSave = new QPushButton("Сохранить", this);
    btnLoad = new QPushButton("Открыть", this);
    btnLineColor = new QPushButton("Цвет линии", this);
    btnFillColor = new QPushButton("Цвет заливки", this);

    buttonLayout->addWidget(btnLine);
    buttonLayout->addWidget(btnRect);
    buttonLayout->addWidget(btnEllipse);
    buttonLayout->addWidget(btnSelection);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addWidget(btnSave);
    buttonLayout->addWidget(btnLoad);
    buttonLayout->addWidget(btnLineColor);
    buttonLayout->addWidget(btnFillColor);
    buttonLayout->addStretch();

    scene = new CustomScene(this);
    scene->setSceneRect(0, 0, 800, 600);

    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing); 

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(view);

    connect(btnLine, &QPushButton::clicked, [this]() {
        scene->setDrawingType(FigureType::Line);
        });

    connect(btnRect, &QPushButton::clicked, [this]() {
        scene->setDrawingType(FigureType::Rectangle);
        });

    connect(btnEllipse, &QPushButton::clicked, [this]() {
        scene->setDrawingType(FigureType::Ellipse);
        });

    connect(btnSelection, &QPushButton::clicked, [this]() {
        scene->setDrawingType(FigureType::None);
        });
    connect(btnClear, &QPushButton::clicked, [this]() {
        scene->clear();
        });
    connect(btnSave, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить проект", "", "Векторный редактор (*.ved)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) return;

        QDataStream out(&file);

        QList<QGraphicsItem*> items = scene->items();

        out << static_cast<int>(items.size());

        for (QGraphicsItem* item : items) {
            if (auto line = qgraphicsitem_cast<QGraphicsLineItem*>(item)) {
                out << static_cast<int>(FigureType::Line);
                out << line->line();
            }
            else if (auto rect = qgraphicsitem_cast<QGraphicsRectItem*>(item)) {
                out << static_cast<int>(FigureType::Rectangle);
                out << rect->rect();
            }
            else if (auto ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item)) {
                out << static_cast<int>(FigureType::Ellipse);
                out << ellipse->rect();
            }
        }
        file.close();
        });

    connect(btnLoad, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Открыть проект", "", "Векторный редактор (*.ved)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) return;

        QDataStream in(&file);

        scene->clear();

        int count = 0;
        in >> count; 

        QPen pen(Qt::black, 2);
        QBrush brush(Qt::transparent);

        for (int i = 0; i < count; ++i) {
            int typeInt;
            in >> typeInt;
            FigureType type = static_cast<FigureType>(typeInt);

            if (type == FigureType::Line) {
                QLineF lineGeom;
                in >> lineGeom;
                scene->addLine(lineGeom, pen);
            }
            else if (type == FigureType::Rectangle) {
                QRectF rectGeom;
                in >> rectGeom;
                scene->addRect(rectGeom, pen, brush);
            }
            else if (type == FigureType::Ellipse) {
                QRectF ellipseGeom;
                in >> ellipseGeom;
                scene->addEllipse(ellipseGeom, pen, brush);
            }
        }
        file.close();
        });
    connect(btnLineColor, &QPushButton::clicked, [this]() {
        QColor color = QColorDialog::getColor(currentLineColor, this, "Выберите цвет линии");
        if (color.isValid()) {
            currentLineColor = color;
            scene->setColors(currentLineColor, currentFillColor); 
        }
        });

    connect(btnFillColor, &QPushButton::clicked, [this]() {
        QColor color = QColorDialog::getColor(currentFillColor, this, "Выберите цвет заливки");
        if (color.isValid()) {
            currentFillColor = color;
            scene->setColors(currentLineColor, currentFillColor); 
        }
        });
    btnEraser = new QPushButton("Ластик", this);
    btnThick = new QPushButton("Толще (+)", this);
    btnThin = new QPushButton("Тоньше (-)", this);

    buttonLayout->addWidget(btnEraser);
    buttonLayout->addWidget(btnThick);
    buttonLayout->addWidget(btnThin);

    static int currentWidth = 2;
    connect(btnThick, &QPushButton::clicked, [this]() {
        if (currentWidth < 20) {
            currentWidth += 2;
            scene->setLineWidth(currentWidth);
        }
        });

    connect(btnThin, &QPushButton::clicked, [this]() {
        if (currentWidth > 2) {
            currentWidth -= 2;
            scene->setLineWidth(currentWidth);
        }
        });

    connect(btnEraser, &QPushButton::clicked, [this]() {
        scene->setDrawingType(FigureType::Eraser);
        });


    resize(900, 700);
}

MainWindow::~MainWindow() {
}
