#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// Ders sınıfı tanımı
class Ders {
private:
    string dersAdi;
    int dersKodu;
    vector<float> notlar;

public:
    // Yapıcı fonksiyon
    Ders(string adi, int kod, vector<float> notlar = {})
        : dersAdi(adi), dersKodu(kod), notlar(notlar) {}

    // Getter fonksiyonları
    string getDersAdi() const { return dersAdi; }
    int getDersKodu() const { return dersKodu; }
    vector<float> getNotlar() const { return notlar; }

    // Not ekleme fonksiyonu
    void addNot(float notu) {
        notlar.push_back(notu);
    }

    // Ortalama hesaplama fonksiyonu
    float hesaplaOrtalama() const {
        if (notlar.empty()) return 0.0;
        float toplam = accumulate(notlar.begin(), notlar.end(), 0.0);
        return toplam / notlar.size();
    }

    // Standart sapma hesaplama fonksiyonu
    float hesaplaStandartSapma() const {
        float ortalama = hesaplaOrtalama();
        float toplam = 0.0;
        for (float notu : notlar) {
            toplam += pow(notu - ortalama, 2);
        }
        return sqrt(toplam / notlar.size());
    }

    // Harf notu hesaplama fonksiyonu
    char harfNotuHesapla(float notu) const {
        if (notu >= 90) return 'A';
        else if (notu >= 80) return 'B';
        else if (notu >= 70) return 'C';
        else if (notu >= 60) return 'D';
        else return 'F';
    }

    // Ders verisini dosyaya yazma fonksiyonu
    void saveToFile(ofstream &outFile) const {
        outFile << dersAdi << endl;
        outFile << dersKodu << endl;
        outFile << notlar.size() << endl;
        for (float notu : notlar) {
            outFile << notu << endl;
        }
    }

    // Ders verisini dosyadan okuma fonksiyonu
    static Ders loadFromFile(ifstream &inFile) {
        string adi;
        int kod;
        size_t notSayisi;
        inFile >> ws;
        getline(inFile, adi);
        inFile >> kod;
        inFile >> notSayisi;
        vector<float> notlar(notSayisi);
        for (size_t i = 0; i < notSayisi; ++i) {
            inFile >> notlar[i];
        }
        return Ders(adi, kod, notlar);
    }
};

// Öğrenci sınıfı tanımı
class Ogrenci {
private:
    string isim;
    string soyad;
    int numara;
    vector<Ders> dersler;

public:
    // Yapıcı fonksiyon
    Ogrenci(string isim, string soyad, int numara)
        : isim(isim), soyad(soyad), numara(numara) {}

    // Getter fonksiyonları
    int getOgrenci() const { return numara; }
    vector<Ders> getDersler() const { return dersler; }
    string getIsim() const { return isim; }
    string getSoyad() const { return soyad; }

    // Ders ekleme fonksiyonu
    void dersEkle(const Ders& ders) {
        dersler.push_back(ders);
    }

    // Not ekleme fonksiyonu
    void notEkle(int dersKodu, float notu) {
        auto it = find_if(dersler.begin(), dersler.end(), [dersKodu](const Ders& ders) {
            return ders.getDersKodu() == dersKodu;
        });
        if (it != dersler.end()) {
            it->addNot(notu);
            cout << "Not başariyla eklendi." << endl;
        } else {
            cout << "Böyle bir ders bulunamadi." << endl;
        }
    }

    // Ders silme fonksiyonu
    void dersSil(int dersKodu) {
        dersler.erase(remove_if(dersler.begin(), dersler.end(),
                                [dersKodu](const Ders& ders) {
                                    return ders.getDersKodu() == dersKodu;
                                }), dersler.end());
    }

    // Öğrenci bilgilerini güncelleme fonksiyonu
    void guncelle(string yeniIsim, string yeniSoyad) {
        isim = yeniIsim;
        soyad = yeniSoyad;
    }

    // Öğrenci bilgilerini gösterme fonksiyonu
    void bilgileriGoster() const {
        cout << "Öğrenci No: " << numara << " - İsim: " << isim << " " << soyad << endl;
        cout << "Dersler:" << endl;
        for (const Ders& ders : dersler) {
            cout << "  Ders Adi: " << ders.getDersAdi() << " (Kodu: " << ders.getDersKodu() << ")" << endl;
        }
    }

    // Belirli bir dersin kayıtlı olup olmadığını kontrol etme fonksiyonu
    bool dersKayitliMi(const string& dersAdi) const {
        return any_of(dersler.begin(), dersler.end(),
                      [&dersAdi](const Ders& ders) {
                          return ders.getDersAdi() == dersAdi;
                      });
    }

    // Öğrenci verisini dosyaya yazma fonksiyonu
    void saveToFile(ofstream &outFile) const {
        outFile << isim << endl;
        outFile << soyad << endl;
        outFile << numara << endl;
        outFile << dersler.size() << endl;
        for (const Ders& ders : dersler) {
            ders.saveToFile(outFile);
        }
    }

    // Öğrenci verisini dosyadan okuma fonksiyonu
    static Ogrenci loadFromFile(ifstream &inFile) {
        string isim, soyad;
        int numara;
        size_t dersSayisi;
        inFile >> ws;
        getline(inFile, isim);
        getline(inFile, soyad);
        inFile >> numara;
        inFile >> dersSayisi;
        Ogrenci ogrenci(isim, soyad, numara);
        for (size_t i = 0; i < dersSayisi; ++i) {
            ogrenci.dersEkle(Ders::loadFromFile(inFile));
        }
        return ogrenci;
    }
};

// Global öğrenci ve ders listeleri
vector<Ogrenci> ogrenciListesi;
vector<Ders> dersListesi;

// Öğrenci ve ders verilerini dosyaya kaydetme fonksiyonu
void saveData() {
    ofstream outFile("ogrenciler.dat");
    outFile << ogrenciListesi.size() << endl;
    for (const Ogrenci& ogrenci : ogrenciListesi) {
        ogrenci.saveToFile(outFile);
    }
    outFile.close();

    outFile.open("dersler.dat");
    outFile << dersListesi.size() << endl;
    for (const Ders& ders : dersListesi) {
        ders.saveToFile(outFile);
    }
    outFile.close();
}

// Öğrenci ve ders verilerini dosyadan yükleme fonksiyonu
void loadData() {
    ifstream inFile("ogrenciler.dat");
    if (inFile) {
        size_t ogrenciSayisi;
        inFile >> ogrenciSayisi;
        for (size_t i = 0; i < ogrenciSayisi; ++i) {
            ogrenciListesi.push_back(Ogrenci::loadFromFile(inFile));
        }
        inFile.close();
    }

    inFile.open("dersler.dat");
    if (inFile) {
        size_t dersSayisi;
        inFile >> dersSayisi;
        for (size_t i = 0; i < dersSayisi; ++i) {
            dersListesi.push_back(Ders::loadFromFile(inFile));
        }
        inFile.close();
    }
}

// Öğrenci ekleme fonksiyonu
void ogrenciEkle(string isim, string soyad, int numara) {
    ogrenciListesi.emplace_back(isim, soyad, numara);
    cout << "Öğrenci başariyla eklendi." << endl;
}

// Öğrenci güncelleme fonksiyonu
void ogrenciGuncelle(int numara, string yeniIsim, string yeniSoyad) {
    auto it = find_if(ogrenciListesi.begin(), ogrenciListesi.end(), [numara](const Ogrenci& ogrenci) {
        return ogrenci.getOgrenci() == numara;
    });
    if (it != ogrenciListesi.end()) {
        it->guncelle(yeniIsim, yeniSoyad);
        cout << "Öğrenci başariyla güncellendi." << endl;
    } else {
        cout << "Böyle bir öğrenci bulunamadi." << endl;
    }
}

// Öğrenci kaldırma fonksiyonu
void ogrenciKaldir(int numara) {
    ogrenciListesi.erase(remove_if(ogrenciListesi.begin(), ogrenciListesi.end(),
                                   [numara](const Ogrenci& ogrenci) {
                                       return ogrenci.getOgrenci() == numara;
                                   }), ogrenciListesi.end());
    cout << "Öğrenci başariyla kaldirildi." << endl;
}

// Ders ekleme fonksiyonu
void dersEkle(string dersAdi, int dersKodu) {
    dersListesi.emplace_back(dersAdi, dersKodu);
    cout << "Ders başariyla eklendi." << endl;
}

// Ders kaldırma fonksiyonu
void dersKaldir(int dersKodu) {
    dersListesi.erase(remove_if(dersListesi.begin(), dersListesi.end(),
                                [dersKodu](const Ders& ders) {
                                    return ders.getDersKodu() == dersKodu;
                                }), dersListesi.end());
    cout << "Ders başariyla kaldirildi." << endl;
}

// Öğrenciye ders ekleme fonksiyonu
void ogrenciDersEkle(int ogrenciNo, int dersKodu) {
    auto ogrenciIt = find_if(ogrenciListesi.begin(), ogrenciListesi.end(), [ogrenciNo](const Ogrenci& ogrenci) {
        return ogrenci.getOgrenci() == ogrenciNo;
    });
    if (ogrenciIt != ogrenciListesi.end()) {
        auto dersIt = find_if(dersListesi.begin(), dersListesi.end(), [dersKodu](const Ders& ders) {
            return ders.getDersKodu() == dersKodu;
        });
        if (dersIt != dersListesi.end()) {
            ogrenciIt->dersEkle(*dersIt);
            cout << "Ders başariyla eklendi." << endl;
        } else {
            cout << "Böyle bir ders bulunamadi." << endl;
        }
    } else {
        cout << "Böyle bir öğrenci bulunamadi." << endl;
    }
}

// Belirli bir numaraya sahip olan öğrenciyi gösterme fonksiyonu
void ogrenciNumarasiylaGoster(int numara) {
    auto it = find_if(ogrenciListesi.begin(), ogrenciListesi.end(), [numara](const Ogrenci& ogrenci) {
        return ogrenci.getOgrenci() == numara;
    });
    if (it != ogrenciListesi.end()) {
        it->bilgileriGoster();
    } else {
        cout << "Böyle bir öğrenci bulunamadi." << endl;
    }
}

// Kayıtsız öğrencileri gösterme fonksiyonu
void kayitsizOgrencileriGoster() {
    for (const Ogrenci& ogrenci : ogrenciListesi) {
        if (ogrenci.getDersler().empty()) {
            ogrenci.bilgileriGoster();
        }
    }
}

// Tüm dersleri gösterme fonksiyonu
void tumDersleriGoster() {
    for (const Ders& ders : dersListesi) {
        cout << "Ders Adi: " << ders.getDersAdi() << " - Kodu: " << ders.getDersKodu() << endl;
    }
}

// Derslerin ortalama ve standart sapmalarını gösterme fonksiyonu
void dersOrtalamaVeStandartSapmaGoster() {
    for (const Ders& ders : dersListesi) {
        cout << "Ders Adi: " << ders.getDersAdi() << " - Kodu: " << ders.getDersKodu() << endl;
        cout << "  Ortalama: " << ders.hesaplaOrtalama() << endl;
        cout << "  Standart Sapma: " << ders.hesaplaStandartSapma() << endl;
    }
}

// Bir dersin not ortalamasını gösterme fonksiyonu
void dersNotOrtalamasiGoster(int dersKodu) {
    auto dersIt = find_if(dersListesi.begin(), dersListesi.end(), [dersKodu](const Ders& ders) {
        return ders.getDersKodu() == dersKodu;
    });
    if (dersIt != dersListesi.end()) {
        cout << "Ders Adi: " << dersIt->getDersAdi() << " - Kodu: " << dersIt->getDersKodu() << endl;
        cout << "  Ortalama: " << dersIt->hesaplaOrtalama() << endl;
    } else {
        cout << "Böyle bir ders bulunamadi." << endl;
    }
}

// Bir öğrencinin kayıtlı olduğu dersleri gösterme fonksiyonu
void ogrencininDersleriniGoster(int ogrenciNo) {
    auto ogrenciIt = find_if(ogrenciListesi.begin(), ogrenciListesi.end(), [ogrenciNo](const Ogrenci& ogrenci) {
        return ogrenci.getOgrenci() == ogrenciNo;
    });
    if (ogrenciIt != ogrenciListesi.end()) {
        cout << "Öğrenci No: " << ogrenciIt->getOgrenci() << " - İsim: " << ogrenciIt->getIsim() << " " << ogrenciIt->getSoyad() << endl;
        cout << "Kayitli Dersler:" << endl;
        for (const Ders& ders : ogrenciIt->getDersler()) {
            cout << "  Ders Adi: " << ders.getDersAdi() << " (Kodu: " << ders.getDersKodu() << ")" << endl;
        }
    } else {
        cout << "Böyle bir öğrenci bulunamadi." << endl;
    }
}

// Kaydedilmeyen dersleri gösterme fonksiyonu
void kaydedilmeyenDersleriGoster() {
    for (const Ders& ders : dersListesi) {
        bool kaydedilmisMi = any_of(ogrenciListesi.begin(), ogrenciListesi.end(), [&ders](const Ogrenci& ogrenci) {
            return ogrenci.dersKayitliMi(ders.getDersAdi());
        });
        if (!kaydedilmisMi) {
            cout << "Ders Adi: " << ders.getDersAdi() << " - Kodu: " << ders.getDersKodu() << endl;
        }
    }
}

// Bir derse kayıtlı olmayan öğrencileri gösterme fonksiyonu
void derseKayitliOlmayanOgrencileriGoster(int dersKodu) {
    auto dersIt = find_if(dersListesi.begin(), dersListesi.end(), [dersKodu](const Ders& ders) {
        return ders.getDersKodu() == dersKodu;
    });
    if (dersIt != dersListesi.end()) {
        cout << "Ders Adi: " << dersIt->getDersAdi() << " - Kodu: " << dersIt->getDersKodu() << endl;
        cout << "Kayitli Olmayan Öğrenciler:" << endl;
        for (const Ogrenci& ogrenci : ogrenciListesi) {
            bool kayitliMi = any_of(ogrenci.getDersler().begin(), ogrenci.getDersler().end(), [dersKodu](const Ders& ders) {
                return ders.getDersKodu() == dersKodu;
            });
            if (!kayitliMi) {
                ogrenci.bilgileriGoster();
            }
        }
    } else {
        cout << "Böyle bir ders bulunamadi." << endl;
    }
}

// Menü fonksiyonu
void menu() {
    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Ogrenci Ekle" << endl;
        cout << "2. Ogrenci Guncelle" << endl;
        cout << "3. Ogrenci Kaldir" << endl;
        cout << "4. Ders Ekle" << endl;
        cout << "5. Ders Kaldir" << endl;
        cout << "6. Ogrenciye Ders Ekle" << endl;
        cout << "7. Ogrenciye Not Ekle" << endl;
        cout << "8. Verileri Kaydet" << endl;
        cout << "9. Verileri Yükle" << endl;
        cout << "10. Çikis" << endl;
        cout << "11. Numara ile öğrenci bulma" << endl;
        cout << "12. Kayitsiz Ogrencileri Goster" << endl;
        cout << "13. Derslerin Ortalama ve Standart Sapmalarini Göster" << endl;
        cout << "14. Tum Dersleri Göster" << endl;
        cout << "15. Ders Not Ortalamasini Goster" << endl;
        cout << "16. Ogrencinin Kayitli Olduğu Dersleri Goster" << endl;
        cout << "17. Kaydedilmeyen Dersleri Goster" << endl;
        cout << "18. Bir Derse Kayitli Olmayan ogrencileri Goster" << endl;

        int secim;
        cin >> secim;

        if (secim == 1) {
            string isim, soyad;
            int numara;
            cout << "Öğrenci adi: ";
            cin >> isim;
            cout << "Öğrenci soyadi: ";
            cin >> soyad;
            cout << "Öğrenci numarasi: ";
            cin >> numara;
            ogrenciEkle(isim, soyad, numara);
             } else if (secim == 2) {
            int numara;
            string yeniIsim, yeniSoyad;
            cout << "Güncellenecek öğrenci numarasi: ";
            cin >> numara;
            cout << "Yeni isim: ";
            cin >> yeniIsim;
            cout << "Yeni soyad: ";
            cin >> yeniSoyad;
            ogrenciGuncelle(numara, yeniIsim, yeniSoyad);
        } else if (secim == 3) {
            int numara;
            cout << "Kaldirilacak öğrenci numarasi: ";
            cin >> numara;
            ogrenciKaldir(numara);
        } else if (secim == 4) {
            string dersAdi;
            int dersKodu;
            cout << "Ders adi: ";
            cin >> dersAdi;
            cout << "Ders kodu: ";
            cin >> dersKodu;
            dersEkle(dersAdi, dersKodu);
        } else if (secim == 5) {
            int dersKodu;
            cout << "Kaldirilacak ders kodu: ";
            cin >> dersKodu;
            dersKaldir(dersKodu);
        } else if (secim == 6) {
            int ogrenciNo, dersKodu;
            cout << "Öğrenci numarasi: ";
            cin >> ogrenciNo;
            cout << "Eklenecek ders kodu: ";
            cin >> dersKodu;
            ogrenciDersEkle(ogrenciNo, dersKodu);
        } else if (secim == 7) {
            int ogrenciNo, dersKodu;
            float notu;
            cout << "Öğrenci numarasi: ";
            cin >> ogrenciNo;
            cout << "Ders kodu: ";
            cin >> dersKodu;
            cout << "Eklenmek istenen not: ";
            cin >> notu;
            auto ogrenciIt = find_if(ogrenciListesi.begin(), ogrenciListesi.end(), [ogrenciNo](const Ogrenci& ogrenci) {
                return ogrenci.getOgrenci() == ogrenciNo;
            });
            if (ogrenciIt != ogrenciListesi.end()) {
                ogrenciIt->notEkle(dersKodu, notu);
            } else {
                cout << "Böyle bir öğrenci bulunamadi." << endl;
            }
        } else if (secim == 8) {
            saveData();
            cout << "Veriler başariyla kaydedildi." << endl;
        } else if (secim == 9) {
            loadData();
            cout << "Veriler başariyla yüklendi." << endl;
        } else if (secim == 10) {
            cout << "Çikiş yapiliyor..." << endl;
            break;
        } else if (secim == 11) {
            int numara;
            cout << "Gösterilecek öğrenci numarasi: ";
            cin >> numara;
            ogrenciNumarasiylaGoster(numara);
        } else if (secim == 12) {
            kayitsizOgrencileriGoster();
        } else if (secim == 13) {
            dersOrtalamaVeStandartSapmaGoster();
        } else if (secim == 14) {
            tumDersleriGoster();
        } else if (secim == 15) {
            int dersKodu;
            cout << "Not ortalamasi gösterilecek ders kodu: ";
            cin >> dersKodu;
            dersNotOrtalamasiGoster(dersKodu);
        } else if (secim == 16) {
            int ogrenciNo;
            cout << "Kayitli dersleri gösterilecek öğrenci numarası: ";
            cin >> ogrenciNo;
            ogrencininDersleriniGoster(ogrenciNo);
        } else if (secim == 17) {
            kaydedilmeyenDersleriGoster();
        } else if (secim == 18) {
            int dersKodu;
            cout << "Kayitli olmayan öğrenciler gösterilecek ders kodu: ";
            cin >> dersKodu;
            derseKayitliOlmayanOgrencileriGoster(dersKodu);
        } else {
            cout << "Geçersiz seçim. Lütfen tekrar deneyin." << endl;
        }
    }
}

int main() {
    loadData();
    menu();
    saveData();
    return 0;
}