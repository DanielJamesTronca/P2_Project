#include "tableview.h"
#include <QMouseEvent>

TableView::TableView(QWidget* parent) : QTableView(parent) {
    // rendiamo possibile la selezione di un singolo elemento alla volta
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

// override delle dimensioni della view per farla espandere con il pannello
QSize TableView::sizeHint() const {
    return QSize(1200, 400);
}


//Ridefinisco il comportamento della vista al click del mouse su un elemento.
void TableView::mousePressEvent(QMouseEvent* event) {
     if (!indexAt(event->pos()).isValid()) {
        clearSelection();
        selectionModel()->clearCurrentIndex();
    }
    QTableView::mousePressEvent(event);
}

