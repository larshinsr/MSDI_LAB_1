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
  int _rowLeft, _columnLeft;
  int _rowRight, _columnRight;
};
LetterPlace FindPlace(char a, char b) {                                     //find place of chars of bigram in squares
                                                                            //first in left, second in right
  LetterPlace Place;
  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++) {
      
      if (std::tolower(a, std::locale("Russian")) == matrixLeft[i][j]) {
       // std::cout<< i<< ' '<<j<<std::endl;
        Place._rowLeft = i;
        Place._columnLeft = j;
      }
      if (std::tolower(b, std::locale("Russian")) == matrixRight[i][j]){
        Place._rowRight = i;
        Place._columnRight = j;
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
    //std::cout<<Place._rowLeft<<' '<<Place._columnLeft<<"     "<< Place._rowRight << ' ' << Place._columnRight << std::endl;
  return Place;
}

std::vector<std::pair<char, char>> StringToBigrams(const std::string& str) {        // Parse string to bigrams
      std::vector<std::pair<char, char>> bigramPairs;
      for (int i = 0; i < str.size(); i+=2) {
            if (i + 1 < str.size()) {                                               // Ensure there are enough characters for a pair
                bigramPairs.emplace_back(str[i], str[i + 1]);
            } else {
                bigramPairs.emplace_back(str[i], ' ');                              // If the last pair has only one character, pad with 'space'
            }
    
      }
      return bigramPairs;
}

std::pair<char, char> RectangleSwap(LetterPlace place) {                            // Swap chars to chars in another 2 angles
    
    if (place._rowLeft == place._rowRight) {
        int tmp = place._columnLeft;
        place._columnLeft = place._columnRight;
        place._columnRight = tmp;
    }
    else {
        int tmp = place._rowLeft;
        place._rowLeft = place._rowRight;
        place._rowRight = tmp;        
    }
    std::pair<char,char> newBigram = {matrixLeft[place._rowLeft][place._columnLeft],      // Swapped characters
                                      matrixRight[place._rowRight][place._columnRight]};
    
    return newBigram; 
}

std::string Encryption(const std::string& _stringForEncryption) {
    std::string _encryptedString;
    LetterPlace pairPlace;                              

    std::vector<std::pair<char, char>> bigramPairs =        
        StringToBigrams(_stringForEncryption);                                      // Make bigrams from string
    
    std::pair<char, char > newBigramPairs;

    for (const auto& bigram : bigramPairs) {
        //std::cout << (bigram.first) << " " << (bigram.second) << "    ";
        newBigramPairs = RectangleSwap(FindPlace(bigram.first, bigram.second));     // Swap character to another diagonal in bigram rectangle
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

std::string Decryption(const std::string& _stringForDecryption) {                    // Work simillary as Encryption
    std::string _decryptedString;                                                    // allowed by RectangleSwap() function
    LetterPlace pairPlace;
    std::vector<std::pair<char, char>> bigramPairs =
        StringToBigrams(_stringForDecryption);

    std::pair<char, char > newBigramPairs;

    for (const auto& bigram : bigramPairs) {
        //std::cout << (bigram.first) << " " << (bigram.second) << "    ";
        newBigramPairs = RectangleSwap(FindPlace(bigram.first, bigram.second));       
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