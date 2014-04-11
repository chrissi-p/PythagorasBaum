#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QPainter>

#define STARTDEPTH 5.0
#define STARTZOOM 51.0
#define STARTWINKEL 45.0

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void drawRect(double centerPointX, double centerPointY, double leftPointX, double leftPointY, int depth);

    void setAntialiased(bool antialiased);
    void setMutation(bool mutation);

    void setZoom(int zoom);
    void setLeftWinkel(int leftWinkel);
    void setDepth(int depth);


protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter painter;
    QPen pen;
    QBrush brush;
    // Atributes
    double zoom;
    double leftWinkel;
    bool antialiased;
    int maxDepth;
    bool mutation;
};

#endif // RENDERAREA_H
