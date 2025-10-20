#include "drawingcanvas.h"
#include "CustomMatrix.h" // Ensure CustomMatrix is included
#include <qapplication.h>

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent) {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
    setAutoFillBackground(true);
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_intersectionPoints.clear();
    m_intersectionCount = 0;
    m_isScannerActive = false;
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    // This is primarily used to trigger the initial drawing of lines
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    // 1. Toggle the scanner state
    m_isScannerActive = !m_isScannerActive;
    m_intersectionCount = 0;
    m_intersectionPoints.clear();

    if (!m_isScannerActive) {
        cout << "Line segment detection scanner deactivated." << endl;
        update(); // Trigger repaint to remove visual markers
        return;
    }

    cout << "Line segment detection scanner activated." << endl;

    // We must ensure the lines are drawn before grabbing the pixmap
    if (!isPaintLinesClicked) {
        paintLines(); // Ensures lines are drawn on the next update() cycle
    }

    // Force immediate painting and grab the rendered image (important for accuracy)
    QApplication::processEvents();
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "Canvas resolution: " << image.width() << "x" << image.height() << endl;

    const int WINDOW_SIZE = CustomMatrix::SIZE; // 5
    const int HALF_SIZE = WINDOW_SIZE / 2;     // 2
    // Heuristic: require at least 10 drawn pixels (out of 25) for a potential crossing
    const int PIXEL_THRESHOLD = 10;

    // Define a minimal distance to avoid counting the same intersection multiple times
    const int MIN_DIST_SQ = (5 * 5); // 5 pixels squared

    // Iterate over the image, skipping the margins equal to HALF_SIZE
    for(int i = HALF_SIZE; i < image.width() - HALF_SIZE; i++){
        for(int j = HALF_SIZE; j < image.height() - HALF_SIZE; j++){

            int drawnPixelCount = 0;

            // Optimization: Skip if the center pixel is white background
            if (image.pixel(i, j) == 0xffffffff) {
                continue;
            }

            // Scan the 5x5 window centered at (i, j)
            for(int m = -HALF_SIZE; m <= HALF_SIZE; m++){
                for(int n = -HALF_SIZE; n <= HALF_SIZE; n++){
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    // Check if the pixel is not the white background (0xffffffff)
                    if (rgbValue != 0xffffffff){
                        drawnPixelCount++;
                    }
                }
            }

            // Apply Intersection Heuristic
            // Condition: Center is drawn (checked above) AND enough density for a crossing
            if (drawnPixelCount >= PIXEL_THRESHOLD) {

                // Check if this point is too close to an already counted intersection (de-duplication)
                bool alreadyCounted = false;
                QPoint currentPoint(i, j);
                for (const QPoint& p : std::as_const(m_intersectionPoints)) {
                    // Use squared distance for faster comparison
                    int dist_sq = QPoint::dotProduct(currentPoint - p, currentPoint - p);
                    if (dist_sq < MIN_DIST_SQ) {
                        alreadyCounted = true;
                        break;
                    }
                }

                if (!alreadyCounted) {
                    m_intersectionCount++;
                    m_intersectionPoints.append(currentPoint); // Stores the center (i, j)
                    cout << "Intersection detected at (" << i << ", " << j << ")" << endl;

                }
            }
        }
    }

    cout << "Total intersections found: " << m_intersectionCount << endl;

    // 5. Trigger repaint to draw intersection markers
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);  // fill entire widget rect with white
    painter.setRenderHint(QPainter::Antialiasing);

    // --- 1. Draw Lines (Persistently) ---
    QPen pen(Qt::red, 4);
    painter.setPen(pen);

    // Draw lines if we have points, regardless of isPaintLinesClicked state
    for(int i = 0; i < m_points.size() - 1; i += 2){
        painter.drawLine(m_points[i], m_points[i+1]);
    }

    // --- 2. Draw Points ---
    QPen pointPen(Qt::blue, 5);
    painter.setPen(pointPen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    // --- 3. Draw Intersections (if scanner is active) ---
    if (m_isScannerActive) {
        QPen intersectionPen(Qt::green, 2);
        painter.setPen(intersectionPen);
        painter.setBrush(QBrush(Qt::green));

        for (const QPoint& p : std::as_const(m_intersectionPoints)) {
            // This draws the large green circle exactly at the stored center point (i, j)
            painter.drawEllipse(p, 5, 5);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Disable scanner when drawing new points
    if (m_isScannerActive) {
        m_isScannerActive = false;
        m_intersectionPoints.clear();
        m_intersectionCount = 0;
    }

    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}
