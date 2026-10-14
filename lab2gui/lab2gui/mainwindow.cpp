#include "mainwindow.h"
#include "Compare.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <chrono>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("ЛР-2");
    resize(700, 600);

    editFirst = new QLineEdit;
    editFirst->setPlaceholderText("Имя");
    editLast = new QLineEdit;
    editLast->setPlaceholderText("Фамилия");
    spinYear = new QSpinBox;
    spinYear->setRange(1900, 2100);
    spinYear->setValue(2005);
    spinYear->setPrefix("Год: ");
    spinYearTo = new QSpinBox;
    spinYearTo->setRange(1900, 2100);
    spinYearTo->setValue(2010);
    spinYearTo->setPrefix("Год до: ");

    QPushButton* btnAdd = new QPushButton("Добавить");
    comboMode = new QComboBox;
    comboMode->addItems(QStringList() << "По фамилии" << "По году"
                        << "По имени + фамилии + году" << "Диапазон лет");
    QPushButton* btnSearch = new QPushButton("Найти");

    spinN = new QSpinBox;
    spinN->setRange(100, 10000);
    spinN->setValue(5000);
    spinN->setPrefix("n = ");
    comboOrder = new QComboBox;
    comboOrder->addItems(QStringList() << "Отсортированный" << "Обратный" << "Случайный");
    QPushButton* btnCompare = new QPushButton("Сравнить алгоритмы");

    textData = new QPlainTextEdit;
    textData->setReadOnly(true);
    textResult = new QPlainTextEdit;
    textResult->setReadOnly(true);

    QWidget* central = new QWidget;
    setCentralWidget(central);
    QVBoxLayout* main = new QVBoxLayout(central);

    auto addRow = [&](QList<QWidget*> widgets) {
        QHBoxLayout* row = new QHBoxLayout;
        for(QWidget* w : widgets) { row->addWidget(w); }
        main->addLayout(row);
    };
    addRow({editFirst, editLast, spinYear, spinYearTo});
    addRow({btnAdd, comboMode, btnSearch});
    addRow({spinN, comboOrder, btnCompare});
    main->addWidget(new QLabel("Все данные:"));
    main->addWidget(textData);
    main->addWidget(new QLabel("Результат:"));
    main->addWidget(textResult);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(btnCompare, &QPushButton::clicked, this, &MainWindow::onCompare);
}

void MainWindow::onAdd() {
    std::string first = editFirst->text().toStdString();
    std::string last = editLast->text().toStdString();
    size_t year = spinYear->value();

   
    if(first.empty() || last.empty() || index.FindByCompositeKey(first, last, year) != nullptr) {
        textResult->setPlainText("Ошибка: пустое имя/фамилия или такой человек уже есть");
        return;
    }
    index.AddPerson(first, last, year);
    textData->appendPlainText(editLast->text() + " " + editFirst->text() + ", " + QString::number(year));
    editFirst->clear();
    editLast->clear();
}

void MainWindow::onSearch() {
    std::string first = editFirst->text().toStdString();
    std::string last = editLast->text().toStdString();
    size_t year = spinYear->value();
    size_t yearTo = spinYearTo->value();
    int mode = comboMode->currentIndex();

    DynamicArray<Person*> found;
    auto start = std::chrono::steady_clock::now();
    if(mode == 0) { found = index.FindByLastName(last); }
    else if(mode == 1) { found = index.FindByBirthYear(year); }
    else if(mode == 2) {
        Person* person = index.FindByCompositeKey(first, last, year);
        if(person != nullptr) { found.Add(person); }
    }
    else { found = index.FindPeopleInYearRange(year, yearTo); }
    double micro = std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - start).count();

    textResult->clear();
    for(size_t i=0; i<found.GetSize(); ++i) {
        textResult->appendPlainText(QString::fromStdString(found[i]->GetFullName())
                                    + ", " + QString::number(found[i]->GetBirthYear()));
    }
    textResult->appendPlainText(QString("Найдено: %1, время поиска: %2 мкс")
                                .arg(found.GetSize()).arg(micro, 0, 'f', 2));
}

void MainWindow::onCompare() {
    int n = spinN->value();
    CompareResult r = RunCompare(n, comboOrder->currentIndex());
    QString names[3] = { "Линейный поиск", "Бинарное дерево", "Хэш-таблица" };
    CompareRow rows[3] = { r.linear, r.tree, r.hash };

    textResult->clear();
    for(int i=0; i<3; ++i) {
        QString insert = QString::number(rows[i].insertMillis, 'f', 3);
        QString search = QString::number(rows[i].searchMicros, 'f', 3);
        textResult->appendPlainText(names[i] + ": вставка " + insert + " мс, поиск " + search + " мкс");
    }
}