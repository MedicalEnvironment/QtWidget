#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>

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
    QPixmap mGreenCircle;
    QPixmap mYellowCircle;
    QPixmap mRedCircle;
};

ColorfulCircle::ColorfulCircle(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(200, 250);

    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 100);

    connect(slider, &QSlider::valueChanged, this, &ColorfulCircle::setColor);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(this);

    setLayout(layout);

    mGreenCircle.load("/Users/gasoline/Downloads/green_circle.png");
    mYellowCircle.load("/Users/gasoline/Downloads/yellow_circle.png");
    mRedCircle.load("/Users/gasoline/Downloads/red_circle.png");
}

void ColorfulCircle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int circleSize = qMin(width(), height()) - 20;
    int xOffset = (width() - circleSize) / 2;
    int yOffset = (height() - circleSize) / 2;
    QRect circleRect(xOffset, yOffset, circleSize, circleSize);

    QColor color = calculateColor(mSliderValue);

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
    window.setFixedSize(200, 300);

    ColorfulCircle circle(&window);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(&circle);

    QPushButton button;
    QPixmap buttonImage("/Users/gasoline/Downloads/red_button.png");
    button.setIcon(buttonImage);
    button.setIconSize(buttonImage.size());
    layout->addWidget(&button);

    QObject::connect(&button, &QPushButton::clicked, [&circle]() {
        circle.setColor(qrand() % 101); // Randomly set the color
    });

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    QObject::connect(slider, &QSlider::valueChanged, &circle, &ColorfulCircle::setColor);

    layout->addWidget(slider);

    window.show();

    return app.exec();
}

#include "main.moc"
v
