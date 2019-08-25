#ifndef PROBLEMA_NETWORK_H
#define PROBLEMA_NETWORK_H

#include "help_desk.h"

class problema_network: public Help_Desk {
private:
    class StaticTableInit{
    private:
        problema_network* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;

    std::string solved;
    virtual problema_network* create(QXmlStreamReader&) const override;
public:
    problema_network(unsigned int=1,const std::string& ="Titolo", const std::string& ="Soluzione",const std::string& ="Risolto");

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getSolved() const override;
    void setSolved(const std::string& ="Risolto") override;

    virtual std::string tipo() const override;
    virtual problema_network* clone() const override;

    virtual bool operator ==(const Help_Desk &) const override;
    virtual bool operator !=(const Help_Desk &) const override;
};

#endif // PROBLEMA_NETWORK_H
