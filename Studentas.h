#include <string>
#include <vector>

class Studentas {
public:
  Studentas(const std::string &vardas, const std::string &pavarde);
  void IvestiBalus();
  double Vidurkis() const;
  double Mediana() const;
  const std::string &Vardas() const;
  const std::string &Pavarde() const;
  void NuskaitytiIsFailo(const std::string &failo_pavadinimas);
  void IrasytiIFaila(const std::string &failo_pavadinimas) const;
  static std::vector<Studentas> GautiStudentus();
  static void AtnaujintiStudentus(const std::vector<Studentas> &studentai);

private:
  std::string vardas_;
  std::string pavarde_;
  std::vector<int> namu_darbai_;
  int egzaminas_;
  static std::vector<Studentas> studentai_;
};
