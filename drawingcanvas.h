#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include <QPixmap>
#include "CustomMatrix.h" // Include the updated matrix header
#include <array>

using namespace std;

class DrawingCanvas : public QWidget
{
    Q_OBJECT
private:
    const int WINDOW_WIDTH=600;
    const int WINDOW_HEIGHT=400;

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    // Slot to clear all points from the canvas
    void clearPoints();
    void paintLines();
    void segmentDetection(); // Toggles and runs detection

protected:
    // Overridden method to handle painting on the widget
    void paintEvent(QPaintEvent *event) override;

    // Overridden method to handle mouse clicks
    void mousePressEvent(QMouseEvent *event) override;

private:
    // A vector to store all the points drawn by the user
    QVector<QPoint> m_points;

    bool isPaintLinesClicked = false;
    bool m_isScannerActive = false; // New state for scanner toggle
    int m_intersectionCount = 0; // Intersection counter
    QVector<QPoint> m_intersectionPoints; // Stores coordinates of detected intersection centers
};
#endif // DRAWINGCANVAS_H
