#include "mainwindow.h"
#include "customscene.h"
#include <QPainter>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    btnLine = new QPushButton("Линия", this);
    btnRect = new QPushButton("Прямоугольник", this);
    btnEllipse = new QPushButton("Овал", this);
    btnSelection = new QPushButton("Курсор", this);
    btnClear = new QPushButton("Очистить всё", this);

    buttonLayout->addWidget(btnLine);
    buttonLayout->addWidget(btnRect);
    buttonLayout->addWidget(btnEllipse);
    buttonLayout->addWidget(btnSelection);
    buttonLayout->addWidget(btnClear);
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
    resize(900, 700);
}

MainWindow::~MainWindow() {
}
