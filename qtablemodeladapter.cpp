#include "qtablemodeladapter.h"
#include "model.h"
#include "problema_hardware.h"
#include "problema_network.h"
#include "problema_software.h"
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QVariant>
#include <QPushButton>
#include <QRegExp>
#include <QDebug>

#include <QTime>
#include "insert_problems.h"

QTableModelAdapter::QTableModelAdapter(QObject* parent, const insertProblems* i) :
    QAbstractTableModel(parent),
    model(new Model()),
    insert(i){
}

QTableModelAdapter::~QTableModelAdapter() {
    if(model) delete model;
}

//Ritorna il numero di righe del modello
int QTableModelAdapter::rowCount(const QModelIndex &) const {
    return model->count();
}

//Ritorna il numero di colonne del modello
int QTableModelAdapter::columnCount(const QModelIndex &) const {
    return 7;
}

QVariant QTableModelAdapter::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if(role==Qt::FontRole)
    {
        return QFont("Sans Serif", 25, QFont::Bold);
    }
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Numero");
        case 1:
            return QString("Orario");
        case 2:
            return QString("ID");
        case 3:
            return QString("Titolo");
        case 4:
            return QString("Soluzione");
        case 5:
            return QString("Tipo");
        case 6:
            return QString("Solved?");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant QTableModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= model->count() || index.row()<0)
        return QVariant();
    switch(role){
    case Qt::BackgroundColorRole:
        return QVariant(QBrush(QColor(Qt::gray)));
    case Qt::TextAlignmentRole:
        return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    case Qt::SizeHintRole:
        return QSize(500, 0 );
    case Qt::EditRole:
    case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case 0:
            return index.row()+1;
        case 1:
            return model->getHelpDesk(static_cast<unsigned int>(index.row()))->getTime().toString();
        case 2:
            return QString::number(model->getHelpDesk(static_cast<unsigned int>(index.row()))->getID());
        case 3:
            return QString::fromStdString(model->getHelpDesk(static_cast<unsigned int>(index.row()))->getTitolo());
        case 4:
            return QString::fromStdString(model->getHelpDesk(static_cast<unsigned int>(index.row()))->getSoluzione());
        case 5:
            return QString::fromStdString(model->getHelpDesk(static_cast<unsigned int>(index.row()))->tipo());
        case 6:
            return QString::fromStdString(model->getHelpDesk(static_cast<unsigned int>(index.row()))->getSolved());
        default:
            return QVariant();

        }
    }
    }
    return QVariant();
}


bool QTableModelAdapter::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() && role != Qt::EditRole)
        return false;
    switch(index.column())
    {
    case 2:
        model->getHelpDesk(static_cast<unsigned int>(index.row()))->setID(value.toUInt()); break;
    case 3:
        model->getHelpDesk(static_cast<unsigned int>(index.row()))->setTitolo(value.toString().toStdString()); break;
    case 4:
       model->getHelpDesk(static_cast<unsigned int>(index.row()))->setSoluzione(value.toString().toStdString()); break;
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags QTableModelAdapter::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if(index.column()==0 || index.column()==6)
        return QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

/*
 * Inserisce 'count' nuove righe nel modello a partire dall'elemento di indice 'begin'
 */
bool QTableModelAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);

    std::string s = insert->getTipo();
    if(s=="Hardware"){
        model->add(new problema_hardware(insert->getID(), insert->getTitolo(), insert->getSoluzione(), insert->getSolved()));
    } else if (s=="Software"){
        model->add(new problema_software(insert->getID(), insert->getTitolo(), insert->getSoluzione(),insert->getSolved()));
    } else if (s=="Network"){
        model->add(new problema_network(insert->getID(),insert->getTitolo(), insert->getSoluzione(),insert->getSolved()));
    }
    endInsertRows();
    return true;
}

/*
 * Rimuove 'count' nuove righe nel modello a partire dall'indice 'begin'
 */
bool QTableModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(begin);
    endRemoveRows();
    return true;
}

void QTableModelAdapter::showMore(const QModelIndex & index) {
    if (index.isValid()
        && index.row() <rowCount()
            && index.column() < columnCount())
    emit dataChanged(createIndex(index.row(),0), createIndex(index.row(), columnCount()-1));
}

//Salva il modello sul file XML
void QTableModelAdapter::saveToFile(const std::string& filename) const {
    model->saveToFile(filename);
}

//Carica il modello in memoria leggendo gli HelpDesk dal file XML
void QTableModelAdapter::loadFromFile(const std::string& filename) const {
    model->loadFromFile(filename);
}

const insertProblems* QTableModelAdapter::getInsertProblems() const{
    return insert;
}

bool QTableModelAdapter::matchRegExp(unsigned int r, const QRegExp& s, const QString& a) const{
    if(a=="ID")
        return QString::number(model->getHelpDesk(r)->getID()).contains(s);
    if(a=="Titolo")
        return QString::fromStdString(model->getHelpDesk(r)->getTitolo()).contains(s);
    else if(a=="Soluzione")
        return QString::fromStdString(model->getHelpDesk(r)->getSoluzione()).contains(s);
    else if(a=="Tipo")
        return QString::fromStdString(model->getHelpDesk(r)->tipo()).contains(s);
    else if(a=="Risolto")
        return QString::fromStdString(model->getHelpDesk(r)->getSolved()).contains(s);
    else
        return false;
}





