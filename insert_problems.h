
#ifndef INSERT_PROBLEMS_H
#define INSERT_PROBLEMS_H
#include <QWidget>
class QVBoxLayout;
class QLineEdit;
class QString;
class QComboBox;
class QCheckBox;
class QLabel;
class insertProblems : public QWidget
{
    Q_OBJECT
private:
    QLabel* tipoLabel;
    QComboBox* tipo;

    QLabel* titoloLabel;
    QLabel* soluzioneLabel;
    QLabel* IDLabel;
    QLabel* solvedLabel;
    QComboBox* solved;

    QLineEdit* ID;
    QLineEdit* titolo;
    QLineEdit* soluzione;

public:
    explicit insertProblems(QWidget *parent = nullptr);
    unsigned int getID() const;
    std::string getTipo() const;
    std::string getTitolo() const;
    std::string getSoluzione() const;
    std::string getSolved() const;

signals:
    void insertClicked();
private slots:
    void setRightFields(const QString &);
};
#endif // INSERT_PROBLEMS_H

