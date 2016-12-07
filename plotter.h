#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>
#include "mainwindow.h"
#include <QWidget>

using namespace std;

/**
 * @brief A classe Plotter tem como funcionalidade plotar os dados coletados do servidor.
 */

class Plotter : public QWidget{
    private:
        vector<float> mdados, mtempo;
    public:
        explicit Plotter(QWidget *parent = 0);
        void putData(vector<float> dados, vector<float> tempo);
        void paintEvent(QPaintEvent *e);
public slots:
};


#endif // PLOTTER_H
