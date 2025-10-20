#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Create a central widget to hold the layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *subLayout = new QHBoxLayout();

    // Create and add the drawing canvas to the top of the layout
    m_canvas = new DrawingCanvas(this); // Store the canvas pointer in the member variable
    mainLayout->addWidget(m_canvas);

    // Create buttons
    m_clearButton = new QPushButton("Clear Canvas", this);
    // Renamed button text for better clarity on its function
    m_detectButton = new QPushButton("Toggle Intersection Scan", this);
    m_drawButton = new QPushButton("Draw Lines", this);

    // Add buttons to the bottom layout
    mainLayout->addLayout(subLayout, 1);
    subLayout->addWidget(m_drawButton, 0);
    subLayout->addWidget(m_detectButton, 0);
    subLayout->addWidget(m_clearButton, 0);

    // Connect the button's clicked signal to the canvas slots
    connect(m_clearButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::clearPoints);
    connect(m_drawButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::paintLines);
    // This is the core connection for the new feature
    connect(m_detectButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::segmentDetection);


    // Set the layout for the central widget and set it as the main window's central widget
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Drawing Canvas");
    setFixedSize(620, 480); // Adjusted size to fit the 600x400 canvas better
}

MainWindow::~MainWindow()
{
}
