#include "problema_network.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
problema_network::StaticTableInit::StaticTableInit(){
    ptr = new problema_network();
    table[ptr->tipo()]=ptr;
}
problema_network::StaticTableInit::~StaticTableInit(){ delete ptr; }
problema_network::StaticTableInit problema_network::a;

problema_network::problema_network(unsigned int d,const std::string& t, const std::string& n,const std::string& s): Help_Desk(d,t,n), solved(s){}

void problema_network::serialize(QXmlStreamWriter& writer) const{
    writer.writeStartElement("HelpDesk");
    writer.writeAttribute("tipo", QString::fromStdString(tipo()));

    writer.writeStartElement("ID");
    writer.writeCharacters(QString::fromStdString(std::to_string(getID())));
    writer.writeEndElement();
    writer.writeStartElement("titolo");
    writer.writeCharacters(QString::fromStdString(getTitolo()));
    writer.writeEndElement();
    writer.writeStartElement("soluzione");
    writer.writeCharacters(QString::fromStdString(getSoluzione()));
    writer.writeEndElement();
    writer.writeStartElement("risolto");
    writer.writeCharacters(QString::fromStdString(getSolved()));
    writer.writeEndElement();

    writer.writeEndElement();
    if (writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
        throw std::exception();
}

problema_network* problema_network::create(QXmlStreamReader& reader) const{
    std::string titolo = "Titolo";
    std::string soluzione = "Soluzione";
    unsigned int ID(0);
    std::string solved = "Risolto";

    if(reader.readNextStartElement() && reader.name()=="ID")
        ID = reader.readElementText().toUInt();
    if(reader.readNextStartElement() && reader.name()=="titolo")
        titolo = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="soluzione")
        soluzione = reader.readElementText().toStdString();
    if(reader.readNextStartElement() && reader.name()=="risolto")
        solved = reader.readElementText().toStdString();
    reader.skipCurrentElement();
    return new problema_network(ID, titolo,soluzione,solved);
}

std::string problema_network::getSolved() const{ return solved ;}
void problema_network::setSolved(const std::string& sol){ solved=sol;}
problema_network* problema_network::clone() const{ return new problema_network(*this); }
std::string problema_network::tipo() const{ return std::string("Network"); }

bool problema_network::operator ==(const Help_Desk & s) const
{
    if(!(dynamic_cast<const problema_network *>(&s)))
        return false;

    return Help_Desk::operator ==(s)

            && dynamic_cast<const problema_network&>(s).getSolved() == solved;
}

bool problema_network::operator !=(const Help_Desk & s) const
{ return !(*this == s); }


