#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QCheckBox;
class QComboBox;
class QSlider;
class QSpinBox;
class QLabel;
QT_END_NAMESPACE

class RenderArea;

class Window : public QWidget
{
    Q_OBJECT
    
public:
    Window();

private slots:

private:
    RenderArea *renderArea;

    QLabel *zoomLabel;
    QLabel *winkelLabel;
    QLabel *depthLabel;
    QLabel *mutationLabel;
    QLabel *otherOptionsLabel;

    QSlider *zoomSlider;
    QSlider *winkelSlider;
    QSpinBox *depthValue;
    QComboBox *mutationComboBox;
    QCheckBox *antialiasingCheckBox;
    QCheckBox *mutationCheckBox;
    QPushButton *quitButton;
};

#endif // WINDOW_H
