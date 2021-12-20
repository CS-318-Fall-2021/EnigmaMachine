#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>
#include <QString>


class Reflector {

private:
    std::vector < std::pair<char, char> > spec;
    std::vector < std::pair<char, char> > first = {{'A', 'D'}, {'B', 'X'}, {'C', 'H'}, {'E', 'S'}, {'F', 'M'}, {'G', 'W'}, {'I', 'O'},
                                                   {'J', 'K'}, {'L', 'T'}, {'N', 'Z'}, {'P', 'Q'}, {'R' ,'V'}, {'U', 'Y'}};

public:
    Reflector();
    Reflector(int reflectorSpec);
    ~Reflector();
    QChar pass(QChar input);
    QString curSetting();
};

#endif // REFLECTOR_H
