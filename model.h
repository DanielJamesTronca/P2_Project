#ifndef MODEL_H
#define MODEL_H
#include "container.h"
#include "deepptr.h"
#include "help_desk.h"
#include <vector>

class Model
{
private:
    Container<DeepPtr<Help_Desk>> contenitore;
public:
    Model() = default;
    ~Model() = default;
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string&);
    int count() const;
    void add(Help_Desk*);                                   // Aggiunge un BeautyItem in coda
    void remove(unsigned int);                              // Rimuove l'Help__Desk di indice i
    bool use(unsigned int);
    Help_Desk* operator[] (unsigned int) const;             // Restituisce un puntatore all'Help_Desk di indice i
    Help_Desk* getHelpDesk(unsigned int) const;             // Ritorna l'Help_Desk di indice specificato

};


#endif // MODEL_H
