#include "renderarea.h"

#include <iostream>
#include <QPainter>
#include <cmath>
#include <QThread>

// Konstruktor
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    antialiased = false;
    zoom = (sqrt(STARTZOOM*8.0)+10.0)*1.0/4.0;
    leftWinkel = STARTWINKEL;
    maxDepth = STARTDEPTH;
    mutation = false;

    //QColor
    pen = QPen(Qt::red, 1, /*Qt::SolidLine*/Qt::NoPen, Qt::FlatCap, Qt::MiterJoin);
    brush = QBrush(Qt::blue, /*Qt::NoBrush*/Qt::SolidPattern);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

// Minimale größe drawin Widget
QSize RenderArea::minimumSizeHint() const
{
    return QSize(200, 100);
}

// Standardgröße drawing Widget
QSize RenderArea::sizeHint() const
{
    return QSize(600, 400);
}

// Antialiasing aktivieren
void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void RenderArea::setMutation(bool mutation)
{
    this->mutation = mutation;
    update();
}

// Zoom ändern
void RenderArea::setZoom(int zoom)
{
    this->zoom = (sqrt(zoom*8.0)+10.0)*1.0/4.0;
    update();
}

// Linke Zeichenwinkel ändern
void RenderArea::setLeftWinkel(int leftWinkel)
{
    this->leftWinkel = leftWinkel;
    update();
}

// Zeichentieve für Baum ändern
void RenderArea::setDepth(int depth)
{
    maxDepth = depth;
    update();
}

// Rekursive Methode zum Zeichnen des Baumes
void RenderArea::drawRect(double leftPointX, double leftPointY, double topPointX, double topPointY, int depth)
{
    double leftWinkel = this->leftWinkel;
    if(depth%2 && mutation == true)
    {
        leftWinkel = 90.0-leftWinkel;
    }

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if(antialiased == true)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    double dx = topPointX - leftPointX;
    double dy = leftPointY - topPointY;
    double x3 = leftPointX - dy;
    double y3 = leftPointY - dx;
    double x4 = topPointX - dy;
    double y4 = topPointY - dx;

    double abs_dx = abs(topPointX - leftPointX);
    double abs_dy = abs(leftPointY - topPointY);

    // Abbruchbedingung, wenn die einzelnen Quadrate zu klein werden
    if(abs_dx <= 0 && abs_dy <= 0)
    {
        return;
    }

    QPoint polygon[4] = {
        QPoint(x3, y3),
        QPoint(x4, y4),
        QPoint(topPointX, topPointY),
        QPoint(leftPointX, leftPointY)
    };

    painter.drawPolygon(polygon, 4);

    // Abbruchbedingung
    depth--;
    if(depth == 0)
    {
        return;
    }

    // Berechnen des neuen Punktes
    double beta = (atan(abs_dy/abs_dx))*180.0/M_PI;
    double ht = sqrt(abs_dx*abs_dx+abs_dy*abs_dy);
    double newHt = cos(leftWinkel*M_PI/180.0) * ht;
    double gama;
    if((x4>=x3 && y4<=y3) || (x4<x3 && y4>y3))
    {
        gama = leftWinkel + beta;
    }
    else
    {
        gama = leftWinkel - beta;
    }
    double dzx = cos(gama*M_PI/180.0) * newHt;
    double dzy = sin(gama*M_PI/180.0) * newHt;

    double zx = 0, zy = 0;
    if(x4>=x3)
    {
        zx = x3 + dzx;
        zy = y3 - dzy;
    }
    else
    {
        zx = x3 - dzx;
        zy = y3 + dzy;
    }

    // Debug
    //std::cout << "dzx / dzy: \t" << dzx << " / " << dzy;
    //std::cout << "\t\tzx / zy: \t\t" << zx << " / " << zy << std::endl;

    // Funktion erneut aufrufen
    drawRect(x3, y3, zx, zy, depth);
    drawRect(zx, zy, x4, y4, depth);

}

// Standard Zeichenevent
void RenderArea::paintEvent(QPaintEvent *)
{

    // Kantenlänge des Basisquadrats in abhängigkeit des Zooms
    double rectWidth;
    if(width() <= height())
    {
        rectWidth = width()/zoom;
    }
    else
    {
        rectWidth = height()/zoom;
    }


    // Punkte für Polygon
    double x1 = width()/2-rectWidth/2,  y1 = height()-5;    // bottom left
    double x3 = x1+rectWidth;                               // top right
    double x4 = x3,                     y4 = y1;            // bottom right

    // Debug
    std::cout << "*-------------  ---------------*" << std::endl;
    std::cout << "Zoom: " << zoom << std::endl;

    // erster aufruf der Funktion zum zeichnen
    drawRect(x1, y1, x4, y4, maxDepth);
}
