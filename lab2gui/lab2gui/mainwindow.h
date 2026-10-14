#pragma once
#include <QMainWindow>
#include "PersonIndex.hpp"

class QLineEdit;
class QSpinBox;
class QComboBox;
class QPlainTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void onAdd();
    void onSearch();
    void onCompare();

private:
    PersonIndex index;
    QLineEdit *editFirst, *editLast;
    QSpinBox *spinYear, *spinYearTo, *spinN;
    QComboBox *comboMode, *comboOrder;
    QPlainTextEdit *textData, *textResult;
};