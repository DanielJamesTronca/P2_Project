#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Model;                                    // definizioni incomplete
class TableView;
class QTableModelAdapter;
class QLineEdit;
class QFilterProxyModel;
class QCloseEvent;
class QComboBox;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr, bool load=true);
    ~MainWindow() override = default;
    QSize sizeHint() const override;
protected:
    virtual void closeEvent (QCloseEvent *event) override;
private:
    QString fileName;
    QLineEdit* searchbar;
    QFilterProxyModel* proxymodel;
    QTableModelAdapter* model;
    TableView* view;

    void loadData();                             //Non viene chiamata da un pulsante, non serve sia uno SLOT

private slots:

    void loadHelpDesk() const ;
    void saveData() ;
    void saveAsData() ;
    void showMore() const;
    void add() const;
    void remove() const;
    void removeResults() const;
    void textFilterChanged() const;
};

#endif // MAINWINDOW_H
