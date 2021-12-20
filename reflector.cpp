#include "reflector.h"
#include <utility>

using namespace std;

//  Constructor
Reflector::Reflector() {}

//  Constructor with spec
Reflector::Reflector(int reflectorSpec) {
    switch (reflectorSpec) {
        case 1: spec = first;   //default for now
                break;
    }
}

//  Destructor
Reflector::~Reflector() {}

//  Swaps the given value with the value its wired to, returns the wired value
QChar Reflector::pass(QChar input) {
    for (pair <QChar, QChar> x: spec) {
        if (x.first == input) return x.second.toLatin1();
        else if (x.second == input) return x.first.toLatin1();
    }
    return '\0';
}

//  Returns a formatted representation of the current setting of the Reflector
QString Reflector::curSetting() {
    QString result = "{";
    for (int i = 0; i < (int)spec.size()-1; ++i) {
        result += spec[i].first;
        result += "-";
        result += spec[i].second;
        result += " | ";
    }
    result += spec[spec.size()-1].first;
    result += "-";
    result += spec[spec.size()-1].second;
    result += "}";
    return result;
}
