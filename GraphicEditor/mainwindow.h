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
    CustomScene* scene;        
    QGraphicsView* view;       

    QPushButton* btnLine;
    QPushButton* btnRect;
    QPushButton* btnEllipse;
    QPushButton* btnSelection;
};
