#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProgressBar>
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}
int iterator_size;
int mod = 1000000007;
void MainWindow::visualizeSort()
{
    QLayoutItem* item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < arr.size(); ++i) {
        QProgressBar* progressBar = new QProgressBar(this);
        progressBar->setValue(arr[i]);
        ui->verticalLayout->addWidget(progressBar);
        progressBar->show();  // Добавьте эту строку
    }

    QCoreApplication::processEvents();  // Добавьте эту строку
}


void MainWindow::displayIndexPowMod(int mod, QVector<int> arr)
{

    //int arrayLength = arr.size();
    int indexPowMod = binpow(iterator_size, iterator_size, mod);

    QString resultText = "Индекс в степени длины массива по модулю числа: " + QString::number(indexPowMod);
    ui->labelIndex->setText(resultText);
}

int MainWindow::binpow(int digit, int power, int mod)
{
    if (power == 0)
        return 1;

    int result = 1;
    digit %= mod;

    while (power > 0) {
        if (power & 1) {
            result = (result * digit) % mod;
        }

        digit = (digit * digit) % mod;
        power >>= 1;
    }

    return result;
}

void MainWindow::bubbleSort()
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                visualizeSort();
                qApp->processEvents(); // Для обновления GUI
                std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Задержка для визуализации
            }
        }
    }
}

void MainWindow::mergeSort(int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        QVector<int> leftArr(n1);
        QVector<int> rightArr(n2);

        for (int i = 0; i < n1; ++i)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            rightArr[j] = arr[mid + 1 + j];

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                ++i;
            } else {
                arr[k] = rightArr[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = leftArr[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = rightArr[j];
            ++j;
            ++k;
        }

        visualizeSort();
        qApp->processEvents(); // Для обновления GUI
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Задержка для визуализации
    }
}

int MainWindow::binarySearch(int digit)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == digit)
            return mid;

        if (arr[mid] < digit)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void MainWindow::on_bubbleSortButton_clicked()
{
    if (arr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Массив пуст!");
        return;
    }

    auto start = std::chrono::steady_clock::now();
    bubbleSort();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    QString message = "Время сортировки пузырьком: " + QString::number(diff.count()) + " секунд";
    QMessageBox::information(this, "Информация", message);
}

void MainWindow::on_mergeSortButton_clicked()
{
    if (arr. isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Массив пуст!");
        return;
    }

    auto start = std::chrono::steady_clock::now();
    mergeSort(0, arr.size() - 1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    QString message = "Время сортировки слиянием: " + QString::number(diff.count()) + " секунд";
    QMessageBox::information(this, "Информация", message);
}

void MainWindow::on_binarySearchButton_clicked()
{
    if (arr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Массив пуст!");
        return;
    }

    bool ok;
    int digit = QInputDialog::getInt(this, "Введите число", "Число:", 0, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        int index = binarySearch(digit);
        if (index != -1) {
            QMessageBox::information(this, "Результат", "Искомое число найдено на индексе: " + QString::number(index));
        } else {
            QMessageBox::information(this, "Результат", "Искомое число не найдено");
        }
    }
}

void MainWindow::on_sortBu_clicked()
{

    QString input = ui->arrayTextEdit->toPlainText();
    QStringList stringList = input.split(" ", Qt::SkipEmptyParts);
    arr.clear();
    for (const QString& str : stringList) {
        bool ok;
        iterator_size++;
        int value = str.toInt(&ok);
        if (ok) {
            arr.append(value);
        } else {
            QMessageBox::warning(this, "Ошибка", "Некорректный ввод массива!");
            return;
        }
    }
    displayIndexPowMod(mod,arr);

}

void MainWindow::heapify(QVector<int>& arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        visualizeSort();
        QCoreApplication::processEvents();
        QThread::msleep(500);  // Задержка для визуализации
        heapify(arr, n, largest);
    }
}
void MainWindow::interpolationSort()
{
    auto start = std::chrono::steady_clock::now();

    int n = arr.size();

    int low = 0;
    int high = n - 1;

    int minVal = arr[0];
    int maxVal = arr[0];

    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal)
            minVal = arr[i];
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    while (low <= high && minVal <= maxVal) {
        int pos = low + ((arr[low] - minVal) * (high - low)) / (maxVal - minVal);

        if (arr[pos] == arr[low])
            ++pos;

        if (arr[pos] < arr[low])
            std::swap(arr[pos], arr[low]);

        if (arr[pos] > arr[high])
            std::swap(arr[pos], arr[high]);

        if (arr[low] == minVal)
            ++low;

        if (arr[high] == maxVal)
            --high;

        visualizeSort();
        QCoreApplication::processEvents();
        QThread::msleep(500);  // Задержка для визуализации

        minVal = arr[low];
        maxVal = arr[high];
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    QMessageBox::information(this, "Время выполнения", QString("Время выполнения: %1 секунд").arg(duration.count()));
}

void MainWindow::on_interpolationSortButton_clicked()
{
    interpolationSort();
}

void MainWindow::heapSort()
{
    auto start = std::chrono::steady_clock::now();

    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        visualizeSort();
        QCoreApplication::processEvents();
        QThread::msleep(500);  // Задержка для визуализации
        heapify(arr, i, 0);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    QMessageBox::information(this, "Время выполнения", QString("Время выполнения: %1 секунд").arg(duration.count()));
}
void MainWindow::on_heapsortButton_clicked()
{
    heapSort();
}


void MainWindow::on_pushButton_clicked()
{
    ui->arrayTextEdit->setPlainText("99 88 11 44 33 22 8 4 6  1 3 32 54 34 98 45");
    ui->arrayTextEdit->update();
}




