#ifndef HELP_DESK_H
#define HELP_DESK_H
#include <map>
#include <string>
#include <QTime>

class QXmlStreamReader;
class QXmlStreamWriter;

class Help_Desk
{
private:
    unsigned int ID;
    std::string titolo;
    std::string soluzione;
    virtual Help_Desk* create(QXmlStreamReader&) const = 0;
    QTime time;

protected:
    static std::map<std::string,Help_Desk*> table;

public:
    Help_Desk(unsigned int=1, const std::string& ="Titolo", const std::string& ="Soluzione");

    std::string getTitolo() const;
    std::string getSoluzione() const;
    unsigned int getID() const;
    QTime getTime() const;

    void setID(unsigned int);
    void setTitolo(const std::string& = "Titolo");
    void setSoluzione(const std::string& = "Soluzione");

    virtual std::string getSolved() const =0;
    virtual void setSolved(const std::string&) = 0;

    virtual std::string tipo() const = 0;

    virtual Help_Desk* clone() const = 0;
    virtual ~Help_Desk() = default;

    //SERIALIZZAZIONE
    static Help_Desk* unserialize(QXmlStreamReader&);
    virtual void serialize(QXmlStreamWriter&) const = 0;

    virtual bool operator ==(const Help_Desk &) const;
    virtual bool operator !=(const Help_Desk &) const;
};

#endif // HELP_DESK_H
