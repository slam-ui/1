#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QScrollBar>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        // Создаем виджеты
        QSlider *slider = new QSlider(Qt::Horizontal);
        QScrollBar *scrollBar = new QScrollBar(Qt::Horizontal);
        QLabel *label = new QLabel("Volume: 0%");
        QLineEdit *lineEdit = new QLineEdit();
        QComboBox *comboBox = new QComboBox();

        // Настройка QComboBox
        comboBox->addItem("Quiet (25%)");
        comboBox->addItem("Medium (50%)");
        comboBox->addItem("Loud (75%)");
        comboBox->addItem("Max (100%)");

        // Настройка диапазона для QSlider и QScrollBar
        slider->setRange(0, 100);
        scrollBar->setRange(0, 100);

        // Настройка QLineEdit для ввода чисел
        lineEdit->setValidator(new QIntValidator(0, 100, this));
        lineEdit->setText("0");

        // Добавляем виджеты в компоновщики
        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *topLayout = new QHBoxLayout;

        topLayout->addWidget(slider);
        topLayout->addWidget(scrollBar);

        mainLayout->addLayout(topLayout);
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
        mainLayout->addWidget(comboBox);

        setLayout(mainLayout);

        // Связываем сигналы и слоты
        connect(slider, &QSlider::valueChanged, scrollBar, &QScrollBar::setValue);
        connect(scrollBar, &QScrollBar::valueChanged, slider, &QSlider::setValue);

        connect(slider, &QSlider::valueChanged, this, [label](int value) {
            label->setText(QString("Volume: %1%").arg(value));
        });

        connect(lineEdit, &QLineEdit::textChanged, this, [slider, scrollBar, label](const QString &text) {
            bool ok;
            int value = text.toInt(&ok);
            if (ok && value >= 0 && value <= 100) {
                slider->setValue(value);
                scrollBar->setValue(value);
                label->setText(QString("Volume: %1%").arg(value));
            }
        });

        connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, [slider, scrollBar, label, lineEdit](int index) {
            int value = 0;
            switch (index) {
                case 0: value = 25; break; // Quiet
                case 1: value = 50; break; // Medium
                case 2: value = 75; break; // Loud
                case 3: value = 100; break; // Max
            }
            slider->setValue(value);
            scrollBar->setValue(value);
            label->setText(QString("Volume: %1%").arg(value));
            lineEdit->setText(QString::number(value));
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(400, 300);
    window.show();
    return app.exec();
}

#include "main.moc"