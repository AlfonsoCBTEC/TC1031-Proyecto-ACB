#ifndef INPUTUTILS_H_
#define INPUTUTILS_H_

#include <iostream>
#include <string>

/**
 * @class InputUtils
 * @brief Utilidades estaticas para validar entradas de usuario en consola.
 */

class InputUtils {
public:
    /**
     * @brief Lee un numero flotante validando tipo y rango [minVal, maxVal].
     */
    static float readFloat(const std::string& prompt, float minVal, float maxVal);

    /**
     * @brief Lee un numero entero validando tipo y rango [minVal, maxVal].
     */
    static int readInt(const std::string& prompt, int minVal, int maxVal);
        
    /**
     * @brief Lee una linea de texto no vacia y sin comas (para no corromper el CSV).
     */
    static std::string readText(const std::string& prompt);
};

float InputUtils::readFloat(const std::string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && std::cin.peek() == '\n') {
            std::cin.ignore(10000, '\n');
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "Error: El valor debe estar entre " << minVal << " y " << maxVal << ".\n";
        } else {
            std::cout << "Error: Entrada invalida. Ingresa un numero valido.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

int InputUtils::readInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && std::cin.peek() == '\n') {
            std::cin.ignore(10000, '\n');
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "Error: El valor debe estar entre " << minVal << " y " << maxVal << ".\n";
        } else {
            std::cout << "Error: Entrada invalida. Ingresa un numero entero.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

std::string InputUtils::readText(const std::string& prompt) {
    std::string text;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, text);

        bool onlySpaces = (text.find_first_not_of(" \t\r\n") == std::string::npos);
        bool hasComma = (text.find(',') != std::string::npos);

        if (onlySpaces) {
            std::cout << "Error: Este campo no puede quedar vacio.\n";
        } else if (hasComma) {
            std::cout << "Error: No uses comas (,) en este campo.\n";
        } else {
            return text;
        }
    }
}

#endif
