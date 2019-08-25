#include "insert_problems.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QCheckBox>

insertProblems::insertProblems(QWidget *parent) : QWidget(parent),
    tipoLabel(new QLabel("Tipo problema:", this)),
    tipo(new QComboBox(this)),

    titoloLabel(new QLabel("Titolo:", this)),
    soluzioneLabel(new QLabel("Soluzione:", this)),
    IDLabel(new QLabel("ID:",this)),

    solvedLabel(new QLabel("Risolto?", this)),
    solved(new QComboBox(this)),


    ID(new QLineEdit(this)),
    titolo(new QLineEdit(this)),
    soluzione(new QLineEdit(this))
{
    QPushButton* insertButton = new QPushButton("Inserisci", this);
    tipo->addItem("Hardware");
    tipo->addItem("Software");
    tipo->addItem("Network");

    solved->addItem("Risolto");
    solved->addItem("Da risolvere");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* fieldsLayout = new QVBoxLayout();
    QHBoxLayout* tipoLayout = new QHBoxLayout();
    QHBoxLayout* soluzioneLayout = new QHBoxLayout();
    QHBoxLayout* titoloLayout = new QHBoxLayout();
    QHBoxLayout* IDLayout = new QHBoxLayout();
    QHBoxLayout* solvedLayout = new QHBoxLayout();



    tipoLayout->addWidget(tipoLabel);
    tipoLayout->addWidget(tipo);
    titoloLayout->addWidget(titoloLabel);
    titoloLayout->addWidget(titolo);
    soluzioneLayout->addWidget(soluzioneLabel);
    soluzioneLayout->addWidget(soluzione);
    IDLayout->addWidget(IDLabel);
    IDLayout->addWidget(ID);
    solvedLayout->addWidget(solvedLabel);
    solvedLayout->addWidget(solved);

    fieldsLayout->addLayout(titoloLayout);
    fieldsLayout->addLayout(soluzioneLayout);
    fieldsLayout->addLayout(IDLayout);
    fieldsLayout->addLayout(solvedLayout);




    mainLayout->addLayout(tipoLayout);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(insertButton);
    connect(tipo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setRightFields(const QString &)));
    connect(insertButton, SIGNAL(clicked()), this, SIGNAL(insertClicked()));
    setLayout(mainLayout);
    emit(tipo->currentTextChanged(tipo->currentText()));
}

void insertProblems::setRightFields(const QString& s){
    titoloLabel->setVisible(false);
    titolo->setVisible(false);
    soluzioneLabel->setVisible(false);
    soluzione->setVisible(false);
    IDLabel->setVisible(false);
    ID->setVisible(false);

    if(s=="Hardware"){
        titoloLabel->setVisible(true);
        titolo->setVisible(true);
        soluzioneLabel->setVisible(true);
        soluzione->setVisible(true);
        IDLabel->setVisible(true);
        ID->setVisible(true);

    } else if (s=="Software"){
        titoloLabel->setVisible(true);
        titolo->setVisible(true);
        soluzioneLabel->setVisible(true);
        soluzione->setVisible(true);
        IDLabel->setVisible(true);
        ID->setVisible(true);

    } else if (s=="Network"){
        titoloLabel->setVisible(true);
        titolo->setVisible(true);
        soluzioneLabel->setVisible(true);
        soluzione->setVisible(true);
        IDLabel->setVisible(true);
        ID->setVisible(true);

    }
}

std::string insertProblems::getTipo() const{ return tipo->currentText().toStdString(); }
std::string insertProblems::getTitolo() const{ return titolo->text().toStdString(); }
std::string insertProblems::getSoluzione() const{ return soluzione->text().toStdString(); }
unsigned int insertProblems::getID() const { return ID->text().toUInt(); }
std::string insertProblems::getSolved() const{ return solved->currentText().toStdString(); }

