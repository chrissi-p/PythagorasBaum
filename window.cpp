#include "window.h"
#include "renderarea.h"

#include <QtWidgets>

const int IdRole = Qt::UserRole;


Window::Window()
{
    // Zeichenfeld
    renderArea = new RenderArea;

    // Einstellung für Zoom
    zoomSlider = new QSlider;
    zoomSlider->setOrientation(Qt::Horizontal);
    zoomSlider->setRange(2, 100);
    zoomSlider->setSliderPosition(STARTZOOM);
    zoomSlider->setInvertedAppearance(true);

    zoomLabel = new QLabel(tr("Zoom:"));
    zoomLabel->setBuddy(zoomSlider);

    // Einstellung für den Winkel
    winkelSlider = new QSlider;
    winkelSlider->setOrientation(Qt::Horizontal);
    winkelSlider->setRange(1, 89);
    winkelSlider->setSliderPosition(STARTWINKEL);
    winkelSlider->setInvertedAppearance(true);

    winkelLabel = new QLabel(tr("Winkel:"));
    winkelLabel->setBuddy(winkelSlider);

    // Einstellungen für die Zeichentiefe
    depthValue = new QSpinBox;
    depthValue->setRange(1, 20);
    depthValue->setValue(STARTDEPTH);

    depthLabel = new QLabel("Tiefe:");
    depthLabel->setBuddy(depthValue);

    // Einstellungen für Mutationen
    mutationComboBox = new QComboBox;

    mutationLabel = new QLabel(tr("Mutation:"));
    mutationLabel->setBuddy(mutationComboBox);

    // Andere Einstellungen
    otherOptionsLabel = new QLabel(tr("Optionen:"));

    antialiasingCheckBox = new QCheckBox(tr("Antialiasing"));
    mutationCheckBox = new QCheckBox(tr("Mutation"));

    // Beenden Button
    quitButton = new QPushButton;
    quitButton->setText("&Beenden");


    // Slots und Signale
    connect(zoomSlider, SIGNAL(valueChanged(int)), renderArea, SLOT(setZoom(int)));
    connect(winkelSlider, SIGNAL(valueChanged(int)), renderArea, SLOT(setLeftWinkel(int)));
    connect(depthValue, SIGNAL(valueChanged(int)), renderArea, SLOT(setDepth(int)));
    connect(antialiasingCheckBox, SIGNAL(clicked(bool)), renderArea, SLOT(setAntialiased(bool)));
    connect(mutationCheckBox, SIGNAL(clicked(bool)), renderArea, SLOT(setMutation(bool)));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


    // Layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 2);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 2);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);

    mainLayout->addWidget(zoomLabel, 1, 0, Qt::AlignRight);
    mainLayout->addWidget(zoomSlider, 1, 1, 1, 3);
    mainLayout->addWidget(winkelLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(winkelSlider, 2, 1, 1, 3);
    mainLayout->addWidget(depthLabel, 3, 0, Qt::AlignRight);
    mainLayout->addWidget(depthValue, 3, 1);
    mainLayout->addWidget(mutationLabel, 3, 2, Qt::AlignRight);
    mainLayout->addWidget(mutationComboBox, 3, 3);
    mainLayout->addWidget(otherOptionsLabel, 4, 0, Qt::AlignRight);
    mainLayout->addWidget(antialiasingCheckBox, 4, 1);
    mainLayout->addWidget(mutationCheckBox, 4, 3);

    mainLayout->addWidget(quitButton, 5, 3);
    setLayout(mainLayout);
}
