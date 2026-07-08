#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include "customscene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QPushButton* btnLine;
    QPushButton* btnRect;
    QPushButton* btnEllipse;
    QPushButton* btnSelection;
    QPushButton* btnClear;
    QPushButton* btnSave;
    QPushButton* btnLoad;
    QPushButton* btnLineColor;  
    QPushButton* btnFillColor;   
    QPushButton* btnEraser;
    QPushButton* btnThick;
    QPushButton* btnThin;

private:
    CustomScene* scene;
    QGraphicsView* view;

    QColor currentLineColor;    
    QColor currentFillColor;     

};
