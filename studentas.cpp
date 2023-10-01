#include "Studentas.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

std::vector<Studentas> Studentas::studentai_;

Studentas::Studentas(const std::string &vardas, const std::string &pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}

void Studentas::IvestiBalus() {
    int pazymys;
    int namu_darbu_sk = 0;
    std::cout << "Įveskite namų darbų rezultatus (įveskite 5 paskutinius pažymius): ";
    while (namu_darbu_sk < 5) {
        std::cin >> pazymys;
        if (pazymys == -1) {
            break;
        }
        namu_darbai_.push_back(pazymys);
        namu_darbu_sk++;
    }
    std::cout << "Įveskite egzamino rezultatą: ";
    std::cin >> egzaminas_;
}

double Studentas::Vidurkis() const {
    if (namu_darbai_.empty())
        return 0.6 * egzaminas_;
    double vidurkis =
        std::accumulate(namu_darbai_.begin(), namu_darbai_.end(), 0.0) /
        namu_darbai_.size();
    return 0.4 * vidurkis + 0.6 * egzaminas_;
}

double Studentas::Mediana() const {
    if (namu_darbai_.empty())
        return 0.6 * egzaminas_;
    std::vector<int> pazymiai = namu_darbai_;
    std::sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();
    return n % 2 == 0 ? 0.4 * (0.5 * (pazymiai[n / 2 - 1] + pazymiai[n / 2])) +
        0.6 * egzaminas_
        : 0.4 * pazymiai[n / 2] + 0.6 * egzaminas_;
}

const std::string &Studentas::Vardas() const { return vardas_; }

const std::string &Studentas::Pavarde() const { return pavarde_; }

void Studentas::NuskaitytiIsFailo(const std::string &failo_pavadinimas) {
    std::ifstream failas(failo_pavadinimas);

    if (!failas.is_open()) {
        std::cerr << "Klaida atidarant failą!" << std::endl;
        return;
    }

    std::string pavardes_stulpelis, vardai_stulpelis;
    std::vector<int> namu_darbai_stulpeliai;
    int egzaminas_stulpelis;
    failas >> pavardes_stulpelis >> vardai_stulpelis;

    std::string stulpelio_pavadinimas;
    while (failas >> stulpelio_pavadinimas) {
        if (stulpelio_pavadinimas == "Egzaminas") {
            break; 
        }
        namu_darbai_stulpeliai.push_back(std::stoi(
            stulpelio_pavadinimas.substr(2)));
    }

   
    std::string vardas, pavarde;
    while (failas >> vardas >> pavarde) {
        Studentas studentas(vardas, pavarde);
        studentas.namu_darbai_ =
            namu_darbai_stulpeliai;
        failas >> studentas.egzaminas_;
        studentai_.push_back(studentas);
    }

    failas.close();
}

void Studentas::IrasytiIFaila(const std::string &failo_pavadinimas) const {
    std::ofstream failas(failo_pavadinimas);

    if (!failas.is_open()) {
        std::cerr << "Klaida atidarant failą rašymui!" << std::endl;
        return;
    }

 
    failas << "Pavardė"
        << "\t"
        << "Vardas";
    for (int i = 0; i < namu_darbai_.size(); ++i) {
        failas << "\tND" << (i + 1);
    }
    failas << "\tEgzaminas" << std::endl;

  
    for (const Studentas &studentas : studentai_) {
        failas << studentas.Pavarde() << "\t" << studentas.Vardas();
        for (int nd : studentas.namu_darbai_) {
            failas << "\t" << nd;
        }
        failas << "\t" << studentas.egzaminas_ << std::endl;
    }

    failas.close();
}

std::vector<Studentas> Studentas::GautiStudentus() {
    return studentai_;
}

void Studentas::AtnaujintiStudentus(const std::vector<Studentas> &studentai) {
    studentai_ = studentai;
}
