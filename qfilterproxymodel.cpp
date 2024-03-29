#include "qfilterproxymodel.h"
#include "qtablemodeladapter.h"
#include <vector>
#include <QComboBox>

QFilterProxyModel::QFilterProxyModel(QObject* parent, const QComboBox* c) : QSortFilterProxyModel (parent), searchAttribute(c){
}

void QFilterProxyModel::showMore(const QModelIndex& index) const{
    QModelIndex index_source = mapToSource(index);
    static_cast<QTableModelAdapter*>(sourceModel())->showMore(index_source);
}

void QFilterProxyModel::removeResults() {
    while(rowCount()){
        removeRows(0,1);
    }
}

bool QFilterProxyModel::removeRows(int begin, int count, const QModelIndex& parent) {
    bool result = sourceModel()->removeRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::insertRows(int begin, int count, const QModelIndex& parent) {
    bool result = sourceModel()->insertRows(begin, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::filterAcceptsRow(int row_source, const QModelIndex&) const {
    return static_cast<QTableModelAdapter*>(sourceModel())->matchRegExp(static_cast<unsigned int>(row_source), filterRegExp(), searchAttribute->currentText());
}
