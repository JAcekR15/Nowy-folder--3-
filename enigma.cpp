#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // dla rand() i srand()
#include <ctime>   // dla time()

class Enigma {
private:
    std::vector<int> rotors; // Zestaw rotatorów

public:
    Enigma(const std::vector<int>& rotors) : rotors(rotors) {}

    // Szyfruj pojedynczy znak
    char encryptChar(char c) {
        if (isalpha(c)) {
            // Rotacja o wartość wirnika
            int offset = (toupper(c) - 'A' + rotors[0]) % 26; 
            return 'A' + offset;
        }
        return c; // Nieszyfrowane znaki
    }

    // Deszyfruj pojedynczy znak
    char decryptChar(char c) {
        if (isalpha(c)) {
            // Odwrócenie rotacji
            int offset = (toupper(c) - 'A' - rotors[0] + 26) % 26; 
            return 'A' + offset;
        }
        return c; // Nieszyfrowane znaki
    }

    // Szyfruj ciąg tekstowy
    std::string encrypt(const std::string& text) {
        std::string encryptedText;
        for (char c : text) {
            encryptedText += encryptChar(c);
        }
        return encryptedText;
    }

    // Deszyfruj ciąg tekstowy
    std::string decrypt(const std::string& text) {
        std::string decryptedText;
        for (char c : text) {
            decryptedText += decryptChar(c);
        }
        return decryptedText;
    }
};

// Funkcja do losowania wirników
std::vector<int> generateRandomRotors(int count) {
    std::vector<int> rotors;
    for (int i = 0; i < count; ++i) {
        rotors.push_back(rand() % 1000 + 1); // Losuj wartość od 1 do 1000
    }
    return rotors;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Ustawienie ziarna losowości

    int rotorCount;
    std::cout << "Ile wirników chcesz użyć (1-5)? ";
    std::cin >> rotorCount;
    rotorCount = std::max(1, std::min(rotorCount, 5)); // Ograniczenie do 1-5

    std::vector<int> rotors = generateRandomRotors(rotorCount);
    Enigma enigma(rotors);

    int choice;
    std::string text;

    // Menu wyboru
    std::cout << "Wybierz opcję:\n";
    std::cout << "1. Szyfruj tekst\n";
    std::cout << "2. Odszyfruj tekst\n";
    std::cin >> choice;
    std::cin.ignore(); // Ignoruj znak nowej linii po wczytaniu liczby

    if (choice == 1) {
        std::cout << "Wpisz tekst do zaszyfrowania: ";
        std::getline(std::cin, text);
        std::string encrypted = enigma.encrypt(text);
        std::cout << "Zaszyfrowany tekst: " << encrypted << std::endl;
    } else if (choice == 2) {
        std::cout << "Wpisz tekst do odszyfrowania: ";
        std::getline(std::cin, text);
        std::string decrypted = enigma.decrypt(text);
        std::cout << "Odszyfrowany tekst: " << decrypted << std::endl;
    } else {
        std::cout << "Nieprawidłowy wybór." << std::endl;
    }

    return 0;
}
