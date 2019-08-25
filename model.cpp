#include "model.h"
#include "xmlio.h"
#include <QtAlgorithms>
#include <QDebug>

//Metodo di salvataggio
void Model::saveToFile(const std::string &filename) const {
    XmlIO xmlio(filename);
    xmlio.write(contenitore);
}

void Model::loadFromFile(const std::string& filename) {
    XmlIO xmlio(filename);
    contenitore = xmlio.read();
}

int Model::count() const{
    return contenitore.getCounter();
}

void Model::add(Help_Desk* bt){
    contenitore.push_back(DeepPtr<Help_Desk>(bt));
}

void Model::remove(unsigned int index) {
    contenitore.RemoveFromPos(index);
}

Help_Desk* Model::operator[](unsigned int i) const {
    return contenitore[i].operator->();
}

//Ritorna helpDesk in posizione i
Help_Desk* Model::getHelpDesk(unsigned int i) const{
    return contenitore[i].operator->();
}

