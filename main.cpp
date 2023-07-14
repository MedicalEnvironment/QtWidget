#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QPainter>
#include <QPixmap>

class ColorfulCircle : public QWidget
{
Q_OBJECT
public:
    ColorfulCircle(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

public slots:
    void setColor(int value);

private:
    QColor calculateColor(int value);

    int mSliderValue = 0;
};

ColorfulCircle::ColorfulCircle(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(200, 250);
}

void ColorfulCircle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int circleSize = qMin(width(), height()) - 20;
    int xOffset = (width() - circleSize) / 2;
    int yOffset = (height() - circleSize) / 2;
    QRect circleRect(xOffset, yOffset, circleSize, circleSize);

    QColor color = calculateColor(mSliderValue);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    painter.drawEllipse(circleRect);
}

QSize ColorfulCircle::sizeHint() const
{
    return QSize(100, 100);
}

void ColorfulCircle::setColor(int value)
{
    mSliderValue = value;
    update();
}

QColor ColorfulCircle::calculateColor(int value)
{
    if (value <= 33)
        return Qt::green;
    else if (value <= 66)
        return Qt::yellow;
    else
        return Qt::red;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(300, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    ColorfulCircle *circle = new ColorfulCircle(&window);  // Specify the parent widget
    layout->addWidget(circle);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    layout->addWidget(slider);  // Add the slider to the layout

    QObject::connect(slider, &QSlider::valueChanged, circle, &ColorfulCircle::setColor);

    window.show();

    return app.exec();
}

#include "main.moc"
