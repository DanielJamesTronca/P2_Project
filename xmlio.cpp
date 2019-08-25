#include "xmlio.h"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDebug>

XmlIO::XmlIO(const std::string& filepath) : filename(filepath) {}

Container<DeepPtr<Help_Desk>> XmlIO::read() const {
    //Creo un contenitore
    Container<DeepPtr<Help_Desk>> contenitore;
    //Apro file (QFile)
    QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore di apertura", "Non è stato possibile aprire il file", QMessageBox::Ok);
        return contenitore;
    }


    //Lettura da file XML
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement() && reader.name() == "root"){
        while(reader.readNextStartElement()) {
            try{
                 contenitore.push_back(Help_Desk::unserialize(reader));
            } catch(std::string s) {
                QMessageBox box(QMessageBox::Warning, "Errore in lettura", "Potrebbe esserci un elemento non letto correttamente", QMessageBox::Ok);
            }
        }
    }
    //Chiude il file e ritorna il contenitore con gli HelpDesk letti
    file.close();
    return contenitore;
}


void XmlIO::write(const Container<DeepPtr<Help_Desk>>& container) const {
    QSaveFile file(QString::fromStdString(filename));
    //Apre un file. Se non si apre lancia una eccezione
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");
    writer.writeStartElement("root");               // <root>
    auto citer = container.begin();
    while(citer!= container.end()) {
        (*citer)->serialize(writer);
        ++citer;
    }
    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // Chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine
    file.commit();  // Scrive il file temporaneo su disco
}
