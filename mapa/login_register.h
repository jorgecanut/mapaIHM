#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}
    ~ClickableLabel() = default;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();
        QLabel::mousePressEvent(event); // opcional pero recomendable
    }
};

#endif// LOGIN_REGISTER_H
