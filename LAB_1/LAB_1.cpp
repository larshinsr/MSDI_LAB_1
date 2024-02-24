#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <Windows.h>
#include <cctype>
#include<unordered_set>
#define SIZE 6
const char matrixLeft[SIZE][SIZE] = {
        {'е', '€', '.', 'к', 'ъ', 'б'},
        {'ы', 'ч', 'х', 'с', 'д', 'в'},
        {'н', 'у', ':', 'м', 'г', 'т'},
        {'ф', 'о', 'ж', 'й', 'и', 'р'},
        {'з', 'ц', 'а', 'п', 'л', 'э'},
        {'ю', 'ь', ' ', 'щ', 'ш', 'Є'} };
const char matrixRight[SIZE][SIZE] = { 
        {'м', 'щ', 'ъ', '.', 'ф', 'ц'},
        {'т', 'п', 'д', 'л', 'з', 'а'},
        {'и', 'Є', 'б', 'о', 'г', 'с'},
        {'ь', 'в', ':', '€', 'х', 'е'},
        {'э', 'р', 'н', 'ж', 'ю', 'ч'},
        {'й', 'ы', 'к', 'ш', ' ', 'у'} };
struct LetterPlace {
  int rowLeft, columnLeft;
  int rowRight, columnRight;
};
LetterPlace findPlace(char a, char b) {
  
  LetterPlace Place;
  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++) {
      
      if (std::tolower(a, std::locale("Russian")) == matrixLeft[i][j]) {
       // std::cout<< i<< ' '<<j<<std::endl;
        Place.rowLeft = i;
        Place.columnLeft = j;
      }
      if (std::tolower(b, std::locale("Russian")) == matrixRight[i][j]){
        Place.rowRight = i;
        Place.columnRight = j;
      }
    }
    /*for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << matrixLeft[i][j]<< ' ';
        }
        std::cout<<"                ";
        for (int j = 0; j < SIZE; j++) {
            std::cout << matrixRight[i][j] << ' ';
        }
        std::cout<<std::endl;
    }*/
    //std::cout<<Place.rowLeft<<' '<<Place.columnLeft<<"     "<< Place.rowRight << ' ' << Place.columnRight << std::endl;
  return Place;
}

std::vector<std::pair<char, char>> stringToBigrams(
        const std::string& str) {
      std::vector<std::pair<char, char>> bigramPairs;
      for (int i = 0; i < str.size(); i+=2) {
            if (i + 1 < str.size()) {  // Ensure there are enough characters for a pair
                bigramPairs.emplace_back(str[i], str[i + 1]);
            } else {
                bigramPairs.emplace_back(str[i], ' ');  // If the last pair has only one character, pad with 'space'
            }
    
      }
      return bigramPairs;
}

std::pair<char, char> RectangleSwap(LetterPlace place) { //swap characters as another 2 angles
    
    if (place.rowLeft == place.rowRight) {
        int tmp = place.columnLeft;
        place.columnLeft = place.columnRight;
        place.columnRight = tmp;
    }
    else {
        int tmp = place.rowLeft;
        place.rowLeft = place.rowRight;
        place.rowRight = tmp;        
    }
    std::pair<char,char> newBigram = {matrixLeft[place.rowLeft][place.columnLeft], 
                                      matrixRight[place.rowRight][place.columnRight]};
    
    return newBigram; 
}

std::string Encryption(const std::string& _stringForEncryption) {
    std::string _encryptedString;
    LetterPlace pairPlace;

    std::vector<std::pair<char, char>> bigramPairs =
        stringToBigrams(_stringForEncryption);
    
    std::pair<char, char > newBigramPairs;

    for (const auto& bigram : bigramPairs) {
        //std::cout << (bigram.first) << " " << (bigram.second) << "    ";
        newBigramPairs = RectangleSwap(findPlace(bigram.first, bigram.second));
        /*if (std::islower(bigram.first, std::locale("Russian"))) // Preserve uppercase
            newBigramPairs.first = std::tolower(newBigramPairs.first, std::locale("Russian"));
        if (std::islower(bigram.second, std::locale("Russian"))) // Preserve uppercase
            newBigramPairs.second = std::tolower(newBigramPairs.second, std::locale("Russian"));
        if (bigram.first == ' '){ newBigramPairs.first = std::tolower(newBigramPairs.first, std::locale("Russian"));}
        if (bigram.second == ' ') { newBigramPairs.second = std::tolower(newBigramPairs.second, std::locale("Russian")); }*/
        _encryptedString += newBigramPairs.first;
        _encryptedString += newBigramPairs.second;
        
    }
    
    return _encryptedString;
}

std::string Decryption(const std::string& _stringForDecryption) {
    std::string _decryptedString;
    LetterPlace pairPlace;
    std::vector<std::pair<char, char>> bigramPairs =
        stringToBigrams(_stringForDecryption);

    std::pair<char, char > newBigramPairs;

    for (const auto& bigram : bigramPairs) {
        //std::cout << (bigram.first) << " " << (bigram.second) << "    ";
        newBigramPairs = RectangleSwap(findPlace(bigram.first, bigram.second));
        /*if (std::islower(bigram.first, std::locale("Russian"))) // Preserve uppercase
            newBigramPairs.first = std::tolower(newBigramPairs.first, std::locale("Russian"));
        if (std::islower(bigram.second, std::locale("Russian"))) // Preserve uppercase
            newBigramPairs.second = std::tolower(newBigramPairs.second, std::locale("Russian"));
        if (bigram.first == ' ') { newBigramPairs.first = std::tolower(newBigramPairs.first, std::locale("Russian")); }
        if (bigram.second == ' ') { newBigramPairs.second = std::tolower(newBigramPairs.second, std::locale("Russian")); }*/
        _decryptedString += newBigramPairs.first;
        _decryptedString += newBigramPairs.second;

    }

    return _decryptedString;
}
int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string StringForEncryption;
    std::cout << "¬ведите предложение дл€ шифровки (только нижний регистр на выходе): ";
    getline(std::cin, StringForEncryption);
   
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << matrixLeft[i][j] << ' ';
        }
        std::cout << "                ";
        for (int j = 0; j < SIZE; j++) {
            std::cout << matrixRight[i][j] << ' ';
        }
        std::cout << std::endl;
    }
   /* std::unordered_set<char> seenElements;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (seenElements.find(matrixRight[i][j]) != seenElements.end()) {
               // std::cout<<i<<' '<<j<<std::endl;
            }
            // Otherwise, add the element to the set
            seenElements.insert(matrixRight[i][j]);
            
        }
        
    }*/
    //std::cout<<" fs   " << (int)std::tolower('ј', std::locale("Russian")) << ' ' << (int)'а' << std::endl;
    //if(std::isupper('я')){std::cout<<"1"<<std::endl; }
    std::string encryptedString = Encryption(StringForEncryption);
    std:: cout<<std::endl<<" encrypted string: " << encryptedString;
    std::string decryptedString = Decryption(encryptedString);
    std:: cout<<std::endl<<" decrypted string: " << decryptedString;
}