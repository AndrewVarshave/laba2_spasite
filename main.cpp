#include <iostream>
#include "Containers/DynamicArray.h"
#include "Containers/LinkedList.h"
#include "Sequences/Sequence.h"
#include "Sequences/ArraySequence.h"
#include "Sequences/Mutable/MutableArraySequence.h"

using namespace std;
#include "Menu/Menu.h"
#include "Menu/tests.h"
#include "Sequences/Immutable/ImmutableArraySequence.h"


template <typename T>
void handleSequenceOperations() {
    int sequenceType = 0;

    while (true) {
        printSequenceMenu();
        std::cin >> sequenceType;

        if (sequenceType == 0) {
            break;
        }

        if (sequenceType < 1 || sequenceType > 4) {
            std::cout << "Wrong type " << std::endl;
            continue;
        }

        runSequenceOperations<T>(sequenceType);
    }
}

void runMenu() {
    while (true) {
        printMainMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                int dataType;
                printDataTypeMenu();
                std::cin >> dataType;

                switch (dataType) {
                    case 1:
                        handleSequenceOperations<int>();
                        break;
                    case 2:
                        handleSequenceOperations<double>();
                        break;
                    case 3:
                        handleSequenceOperations<std::string>();
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Wrong type." << std::endl;
                }
                break;
            }

            case 2:

                runAllTests();
                break;

            default:
                std::cout << "Wrong action." << std::endl;
        }
    }
}

int main() {
    runMenu();
    return 0;
}