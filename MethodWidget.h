#pragma once

#include <QWidget>

namespace Ui {
class MethodWidget;
}

class MethodWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MethodWidget(QWidget *parent = nullptr);
    ~MethodWidget();

    void setMethodName(const QString &name);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MethodWidget *ui;
};
