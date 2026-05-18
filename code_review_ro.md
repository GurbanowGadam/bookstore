# Recenzie de cod pentru Proiectul 2

## 1. Informații despre proiect

Numele proiectului: Sistem de gestionare a proprietatilor  
Autor: Merdanov Ylham  
Depozit GitHub: https://github.com/MerdanovYlham/OOP-property-system  
Recenzent: Gurbanov Gadam

## 2. Scurtă descriere a proiectului

Acest proiect este un sistem simplu de gestionare a proprietăților. Proiectul încearcă să gestioneze diferite tipuri de proprietăți imobiliare. Exemplele principale sunt apartamentele, casele și vilele. Programul poate stoca aceste proprietăți într-o agenție, le poate afișa și poate calcula chiria totală pentru un număr de luni.

În `main.cpp`, programul creează un `Apartament`, o `Casa` și o `Vila`. Aceste obiecte sunt adăugate într-un obiect `Agentie`. După aceea, programul afișează toate proprietățile, calculează chiria pentru 6 luni, testează `dynamic_cast` și afișează numărul de proprietăți create. README explică ideea de bază, dar descrierea este scurtă și ar putea oferi mai multe detalii despre problemă și comportamentul așteptat.

## 3. Structura generală a depozitului

Depozitul este mic și ușor de navigat. Am găsit aceste fișiere importante: `README.md`, `main.cpp`, `Proprietate.h`, `Proprietate.cpp`, `Apartament.h`, `Apartament.cpp`, `Casa.h`, `Casa.cpp`, `Vila.h`, `Vila.cpp`, `Agentie.h`, `Agentie.cpp` și `Exceptii.h`.

Toate fișierele sunt plasate direct în folderul rădăcină. Pentru un proiect mic, acest lucru este acceptabil, dar pentru un proiect mai mare ar fi mai clar să se separe fișierele header și fișierele sursă în foldere.

Proiectul are în general o separare bună a codului. Majoritatea declarațiilor claselor sunt în fișiere `.h`, iar majoritatea implementărilor funcțiilor sunt în fișiere `.cpp`. O excepție este `Exceptii.h`, unde clasele de excepții implementează `what()` direct în declarațiile claselor. Funcțiile sunt mici, deci aceasta nu este o problemă mare.

Nu am găsit `CMakeLists.txt` sau alt fișier de build. README oferă o comandă `g++`, deci proiectul poate fi totuși compilat. De asemenea, nu am găsit fișiere de date sau fișiere de intrare. Datele de test sunt scrise direct în `main.cpp`.

## 4. Analiza designului OOP

Clasa de bază principală este `Proprietate`. Aceasta conține câmpuri comune: `oras`, `pret` și `suprafata`. Clasele derivate sunt `Apartament`, `Casa` și `Vila`. Această ierarhie are sens deoarece toate trei sunt tipuri de proprietăți.

`Casa` adaugă câmpul `etaje`, iar `Vila` adaugă câmpul `piscina`. `Apartament` nu adaugă un alt câmp, dar are totuși propria implementare pentru calculul chiriei și afișare. În opinia mea, ierarhia este simplă și naturală pentru această temă.

Clasa `Agentie` folosește compoziția. Aceasta conține un `std::vector<std::shared_ptr<Proprietate>>`, deci o agenție stochează multe proprietăți. Acesta este un design bun deoarece o agenție nu este o proprietate, ci gestionează proprietăți.

Încapsularea este în mare parte respectată. Câmpurile din `Agentie`, `Casa` și `Vila` sunt private. În `Proprietate`, câmpurile comune sunt protected, deci clasele derivate le pot accesa. Acest lucru este comun în proiectele studențești, deși câmpurile private cu funcții ajutătoare protected ar putea fi mai sigure.

## 5. Moștenire și polimorfism

Proiectul are o clasă de bază clar creată: `Proprietate`. Există trei clase derivate din aceasta: `Apartament`, `Casa` și `Vila`. Acest lucru satisface cerința de moștenire.

Clasa de bază are funcții virtuale pure. În `Proprietate.h`, `calculeazaChirie(int luni) const` și `clone() const` sunt virtuale pure. Există și o funcție virtuală pură privată numită `afiseazaImpl`. Funcția `calculeazaChirie` este specifică temei proiectului, nu doar o funcție de afișare, deci aceasta este o utilizare bună a polimorfismului.

Clasele derivate folosesc `override` pentru funcțiile lor virtuale. Clasa de bază are și un destructor virtual: `virtual ~Proprietate();`. Acest lucru este important deoarece proiectul stochează obiecte derivate prin pointeri inteligenți către clasa de bază.

Funcțiile virtuale sunt într-adevăr apelate prin pointeri către clasa de bază. În `Agentie::chirieTotala`, codul apelează `p->calculeazaChirie(luni)`, unde `p` este un `std::shared_ptr<Proprietate>`. Aceasta înseamnă că versiunea derivată corectă este apelată la runtime. Constructorii claselor derivate apelează și constructorul clasei de bază, de exemplu `Casa` apelează `Proprietate(oras, pret, suprafata)`.

## 6. Gestionarea memoriei și copierea

Proiectul folosește `std::shared_ptr` și `std::vector`, ceea ce este bine. Nu am văzut `new` sau `delete` brute. Acest lucru reduce riscul de memory leaks și face codul mai ușor de gestionat.

Clasa `Agentie` stochează proprietățile ca `std::shared_ptr<Proprietate>`. Acest lucru îi permite să stocheze apartamente, case și vile în același vector. Proiectul folosește și o funcție `clone()`. În constructorul de copiere al clasei `Agentie`, codul face `proprietati.push_back(p->clone())`. Aceasta este o soluție bună de copiere profundă pentru obiecte polimorfice.

`Agentie` are și un operator de atribuire folosind stilul copy-and-swap: `Agentie &Agentie::operator=(Agentie other)`. Aceasta este o abordare corectă și curată.

O posibilă problemă este contorul static `numarProprietati`. Acesta crește în constructor și în constructorul de copiere, dar destructorul nu îl scade. În demo, programul afișează 6 proprietăți chiar dacă sunt afișate doar 3, deoarece obiectele sunt clonate când sunt adăugate în agenție. Acest lucru poate fi intenționat, dar sensul contorului nu este foarte clar.

O altă problemă mică este că `adaugaProprietate` nu verifică dacă pointerul este null înainte de a apela `p->clone()`.

## 7. Excepții

Proiectul are o ierarhie personalizată de excepții în `Exceptii.h`. Excepția de bază este `EroareProprietate`, derivată din `std::exception`. Există trei clase specifice de excepții: `EroarePret`, `EroareSuprafata` și `EroareOras`.

Excepțiile suprascriu `what()` și oferă mesaje simple. În `main.cpp`, excepțiile sunt prinse prin referință constantă cu `catch (const EroareProprietate &e)`, ceea ce este bine.

Totuși, cred că excepțiile nu sunt încă folosite foarte semnificativ. Singurul throw pe care l-am găsit este un test în `main.cpp`:

```cpp
if (a1->calculeazaChirie(6) < 0)
    throw EroarePret();
```

Cu datele curente, această condiție este falsă. Nu am găsit validare în constructori pentru preț invalid, suprafață invalidă sau oraș gol. Proiectul ar putea fi mai bun dacă aceste clase de excepții ar fi folosite în logica reală de validare.

## 8. Static, const și operatori

Proiectul folosește un câmp static `numarProprietati` și o funcție statică `getNumarProprietati()`. Scopul pare să fie numărarea obiectelor de tip proprietate create. Aceasta este o utilizare rezonabilă a datelor statice, dar sensul exact ar trebui să fie mai clar.

Corectitudinea const este folosită bine în multe locuri. De exemplu, `calculeazaChirie`, `clone`, `afiseaza`, `afiseazaTot` și `chirieTotala` sunt marcate `const`. Parametri precum `const std::string &oras` sunt de asemenea transmiși prin referință constantă.

Nu am găsit o suprascriere pentru `operator<<`. Proiectul folosește în schimb `afiseaza(std::ostream &out)`. Acest lucru funcționează, dar dacă supraîncărcarea operatorilor este cerută, atunci această parte lipsește. Nu am găsit alți operatori semnificativi, cu excepția operatorilor de atribuire.

## 9. README și documentație

README explică pe scurt proiectul și enumeră principalele concepte OOP folosite. Include și o comandă de compilare și rulare folosind `g++`. Acest lucru este util deoarece proiectul nu are fișier CMake.

Totuși, README ar putea fi mai complet. Nu am putut găsi clar o enunțare detaliată a problemei, o explicație clară a ceea ce este dat și a ceea ce este cerut sau o secțiune de bibliografie/resurse. README ar putea explica și rolul lui `clone()`, `Agentie` și al ierarhiei de moștenire.

## 10. Părți bune ale proiectului

Cea mai puternică parte a proiectului este ierarhia clară de clase. `Proprietate` este o clasă de bază bună, iar clasele derivate se potrivesc cu tema imobiliară.

O altă parte bună este faptul că polimorfismul este folosit efectiv. Agenția stochează pointeri către clasa de bază și apelează funcții virtuale prin aceștia. Acest lucru arată că moștenirea nu este doar scrisă pentru cerință, ci este folosită și în logica programului.

Mi-a plăcut și utilizarea lui `std::vector`, `std::shared_ptr` și `clone()`. Aceste alegeri fac gestionarea memoriei mai curată și copierea mai sigură.

Codul este, de asemenea, ușor de citit. Fișierele sunt scurte, numele sunt ușor de înțeles, iar demo-ul din `main.cpp` este simplu de rulat.

## 11. Probleme și sugestii

O posibilă îmbunătățire este folosirea claselor de excepții în constructori sau funcții, nu doar într-un mic test în `main.cpp`.

Proiectul ar putea fi mai clar dacă contorul static ar explica dacă numără obiectele curente sau toate obiectele create.

Cred că această parte poate fi îmbunătățită deoarece `operator<<` lipsește. Adăugarea lui ar face afișarea mai idiomatică și ar satisface mai bine cerința de supraîncărcare a operatorilor.

O posibilă îmbunătățire este adăugarea unui fișier `CMakeLists.txt`. Acest lucru ar face proiectul mai ușor de construit.

README ar putea fi de asemenea extins cu o enunțare mai clară a problemei, explicația soluției și bibliografie.

## 12. Concluzie

În opinia mea, proiectul respectă în mare parte cerințele proiectului. Are separarea codului, moștenire, trei clase derivate, funcții virtuale pure, un destructor virtual, pointeri inteligenți, stocare prin pointeri către clasa de bază, apeluri polimorfice, clonare, excepții personalizate, date statice și funcții const.

Punctele forte principale sunt designul simplu, ierarhia clară de moștenire și utilizarea corectă a polimorfismului prin `Agentie`. Părțile mai slabe sunt utilizarea limitată a excepțiilor, lipsa lui `operator<<`, lipsa fișierului CMake și README-ul scurt. Per total, este un proiect OOP bun pentru nivel începător/intermediar, dar ar putea fi îmbunătățit prin completarea cerințelor și conectarea lor mai bună la logica proiectului.
