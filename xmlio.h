#ifndef XMLIO_H
#define XMLIO_H
#include "container.h"
#include "deepptr.h"
#include "help_desk.h"

class XmlIO {
private:
    std::string filename;
public:
    XmlIO(const std::string&);
    Container<DeepPtr<Help_Desk>> read() const;
    void write(const Container<DeepPtr<Help_Desk>>&) const;
};

#endif // XMLIO_H
