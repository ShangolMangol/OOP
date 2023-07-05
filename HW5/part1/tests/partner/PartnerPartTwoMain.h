#ifndef OOP5_PARTNERMAIN_H
#define OOP5_PARTNERMAIN_H

#include "PartTwoObserverTests.h"
#include "PartTwoSubjectTests.h"

class PartnerPartTwoMain {
public:

    void partnerPartTwoMain() {
        PartTwoObserverTests().partTwoObserverTests();
        PartTwoSubjectTests().partTwoSubjectTests();
    };
};

#endif //OOP5_PARTNERMAIN_H
