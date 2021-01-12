#ifndef FORMSD_H
#define FORMSD_H

#include <QWidget>

namespace Ui {
class Formsd;
}

class Formsd : public QWidget
{
    Q_OBJECT

public:
    explicit Formsd(QWidget *parent = nullptr);
    ~Formsd();

private slots:
    void on_Formsd_windowTitleChanged(const QString &title);

private:
    Ui::Formsd *ui;
};

#endif // FORMSD_H
