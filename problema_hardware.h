#ifndef PROBLEMA_HARDWARE_H
#define PROBLEMA_HARDWARE_H

#include "help_desk.h"

class problema_hardware: public Help_Desk {
private:
    class StaticTableInit{
    private:
        problema_hardware* ptr;
    public:
        StaticTableInit();
        ~StaticTableInit();
    };
    static StaticTableInit a;

    std::string solved;
    virtual problema_hardware* create(QXmlStreamReader&) const override;
public:
    problema_hardware(unsigned int=1,const std::string& ="Titolo", const std::string& ="Soluzione",const std::string& ="Risolto");

    virtual void serialize(QXmlStreamWriter&) const override;

    std::string getSolved() const override;
    void setSolved(const std::string& ="Risolto") override;

    virtual std::string tipo() const override;
    virtual problema_hardware* clone() const override;

    virtual bool operator ==(const Help_Desk &) const override;
    virtual bool operator !=(const Help_Desk &) const override;
};


#endif // PROBLEMA_HARDWARE_H
