#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

#include <QWidget>

namespace Ui {
class ExplorerWidget;
}

class ExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorerWidget(QWidget *parent = nullptr);
    ~ExplorerWidget();

private:
    Ui::ExplorerWidget *ui;
};

#endif // EXPLORERWIDGET_H
