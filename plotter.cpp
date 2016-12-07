#include "plotter.h"
#include <algorithm>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>

/**
 * @brief Plotter::Plotter é a função construtora da classe. Ela inicia as variáveis privadas da classe.
 */

Plotter::Plotter(QWidget *parent) : QWidget(parent){
    mdados.push_back(0);
    mdados.push_back(0);
    mtempo.push_back(0);
    mtempo.push_back(1);
}

/**
 * @brief Plotter::putData é a função que recebe os vetores a serem plotados.
 */

void Plotter::putData(vector<float> dados, vector<float> tempo){
    mdados=dados;
    mtempo=tempo;
    for(int i=1; i<mdados.size(); i++){
        qDebug() << "mdados=" << mtempo[i] ;
    }
    repaint();
}

/**
 * @brief Plotter::paintEvent é a função que gerencia a plotagem dos dados.
 */

void Plotter::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QBrush brush;
    QPen pen;
    float x1, y1, x2, y2;
    painter.setRenderHint(QPainter::Antialiasing);
    brush.setColor(QColor(255,255,100));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    painter.setBrush(brush);
    painter.drawRect(0,0,width(),height());

    painter.setPen(pen);
    x1 = mtempo[0];
    y1 = mdados[0];
    for(int i=1; i<mdados.size(); i++){
        qDebug() << x1 << y1 << x2 << y2;
        x2 = mtempo[i];
        y2 = mdados[i];
        painter.drawLine(x1*width(), (1-y1)*height(), x2*width(), (1-y2)*height());
        x1 = x2;
        y1 = y2;
    }
}

