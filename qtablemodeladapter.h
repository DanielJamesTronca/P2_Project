#ifndef QTABLEMODELADAPTER_H
#define QTABLEMODELADAPTER_H

#include <QAbstractTableModel>
#include <vector>
#include <QTimer>

class Help_Desk;
class insertProblems;
class QRegExp;
class Model;
class itemview;

class QTableModelAdapter: public QAbstractTableModel {
private:
    Model* model;
    const insertProblems* insert;
public:
    QTableModelAdapter(QObject* = nullptr, const insertProblems* = nullptr);
    ~QTableModelAdapter() override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int) override;
    Qt::ItemFlags flags(const QModelIndex&) const override;
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    void showMore(const QModelIndex&);
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string &) const;
    const insertProblems* getInsertProblems() const;
    bool matchRegExp(unsigned int, const QRegExp&, const QString&) const;
    void removeResults(const std::vector<unsigned int> &);
};

#endif // QTABLEMODELADAPTER_H
