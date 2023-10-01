#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Studentas.h"
int main() {
  std::vector<Studentas> studentai;
  int studentu_skaicius;
  

  std::cout << "Pasirinkite, ka norite daryti:\n";
  std::cout << "1. Įvesti naujus duomenis\n";
  std::cout << "2. Nuskaityti duomenis iš failo\n";
  int pasirinkimas;
  std::cin >> pasirinkimas;

  if (pasirinkimas == 1) {
    std::cout << "Įveskite studentų skaičių: ";
    std::cin >> studentu_skaicius;

    for (int i = 0; i < studentu_skaicius; ++i) {
      std::string vardas, pavarde;
      std::cout << "Įveskite studento vardą: ";
      std::cin >> vardas;
      std::cout << "Įveskite studento pavardę: ";
      std::cin >> pavarde;

      Studentas studentas(vardas, pavarde);
      studentas.IvestiBalus();

      studentai.push_back(studentas);
    }
  } else if (pasirinkimas == 2) {
    
    Studentas studentas; 
    studentas.NuskaitytiIsFailo("kursiokai.txt");
    studentai = studentas.GautiStudentus();
  } else {
    std::cout << "Netinkamas pasirinkimas." << std::endl;
    return 1; 
  }

  
  std::sort(studentai.begin(), studentai.end());


  std::cout << std::left << std::setw(15) << "Pavardė" << std::setw(15)
            << "Vardas" << std::setw(20) << "Galutinis (Vid.)" << std::setw(20)
            << "Galutinis (Med.)" << std::endl;
  std::cout << "----------------------------------------------------------"
            << std::endl;

  for (const Studentas &studentas : studentai) {
    std::cout << std::left << std::setw(15) << studentas.Pavarde()
              << std::setw(15) << studentas.Vardas() << std::setw(20)
              << studentas.Vidurkis() << std::setw(20) << studentas.Mediana()
              << std::endl;
  }


  Studentas studentas; 
  studentas.AtnaujintiStudentus(studentai);
  studentas.IrasytiIFaila("kursiokai.txt");

  return 0;
}
