#include "help_desk.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


std::map<std::string,Help_Desk*> Help_Desk::table = std::map<std::string, Help_Desk*>();

Help_Desk::Help_Desk(unsigned int d, const std::string& t, const std::string& n):ID(d), titolo(t), soluzione(n),time(QTime::currentTime()){}


Help_Desk* Help_Desk::unserialize(QXmlStreamReader& reader){
    if(reader.name()!="HelpDesk")
        throw std::string("Name is incorrect");
    std::string tmp = reader.attributes().value("tipo").toString().toStdString();
    if(table.count(tmp)==0)
        throw std::string("Type not found");
    return table[tmp]->create(reader);
}


std::string Help_Desk::getTitolo() const{ return titolo; }
std::string Help_Desk::getSoluzione() const{ return soluzione; }
unsigned int Help_Desk::getID() const { return ID; }
void Help_Desk::setID(unsigned int d){ID=d; }
void Help_Desk::setTitolo(const std::string& m){ titolo=m; }
void Help_Desk::setSoluzione(const std::string& n){ soluzione=n; }
QTime Help_Desk::getTime() const { return time; }

bool Help_Desk::operator==(const Help_Desk & s) const
{
    return ID == s.ID && titolo==s.titolo && soluzione==s.soluzione;
}

bool Help_Desk::operator!=(const Help_Desk & s) const
{ return !(*this == s); }


