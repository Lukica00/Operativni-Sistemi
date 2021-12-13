# Operativni sistemi
Na ovom repozitorijumu se nalaze rešeni zadaci sa laboratorijski vežbi iz operativnih sistema, urađeni za potrebe pripreme za prvi kolokvijum. Neki pokušaji su varijacija na zadatu temu i nisu uspešno rešeni. Neki ni ne mogu da se reše na načine predstavljene na vežbama što predstavlja veliku nepravdu za studente koji su dobili zadatak na laboratorijskoj vežbi. Ostali zadaci su rešeni uspešno, sa možda slobodnijim tumačenjem broja iteracija, pisanja po fajlovima i standardnim izlazima, a sve radi čitljivosti i lakšeg otklanjanja grešaka.

Pored rešenja nalazi se i folder *.vscode* koji sadrži podešavanja da se uz pomoć F5 može pokrenuti i debagirati program u *VS Code*. U tabu *Run and Debug* (Ctrl+Shift+D) odabrati iz padajućeg menija opciju koja sadrži *Zastava za niti*. Treba napomenuti da tako nije moguće prosleđivanje podatka kao argument programa iz konzole. Za rešavanje tog problema dodati argumente u *.vscode/launch.json* u polje *"args"* kao stringove odvojene zapetom. Još jedno rešenje, prema mom mišljenju i brže, je da se slobodnije pristupi čitanju zadatka jer je čitanje argumenta programa iz konzole svakako najlakše od svega što se traži, a samo iziskuje dodatno udaranje po tastaturi. 

# Zadaci
## 1. Niti
1. Korišćenjem programskog jezika C napisati Linux program koji u datoteku izlaz.txt upisuje niz od prvih 20 parnih i 20 neparnih brojeva redom. Parne brojeve upisuje jedna nit, a neparne druga nit. Sinhronizacijom niti semaforima obezbediti da se u datoteku parni i neparni brojevi upisuju naizmenično.

2. Kao i primer iznad samo umesto semafora muteks i uslovne promenjive. (Ovaj primer nije moguće rešiti na ovaj način (ili sam se samo zagledao na jedan način rešavanja i prevideo sve ostale). Razlog leži u tome što postoji mogućnost da se pozove `signal` pre `wait` što će dovesti do beskonačnog čekanja. Rešenje koje je priloženo se može izvršiti sa željenim ishodom u zavisnosti od toga kako se pozovu niti. Ostavio sam printove i veći broj iteracija tako da ko želi da vidi ovaj efekat na delu će uz dovoljno pokretanja programa sigurno jednom dobiti željeni redosled poziva.)

3. Korišćenjem programskog jezika C napisati Linux program threadovi u kome dve niti u tekstualnu datoteku upisuju redom cele brojeve od 1 do 20, pri čemu je svaki broj u zasebnom redu. Prva nit upisuje samo neparne, a druga nit samo parne brojeve. Sinhronizacijom niti obezbediti da se brojevi upisuju u datoteku pravilnim redosledom, 1 2 3 4 5 itd. (Isti kao 1.1).



## 2. Procesi
>>> **Predavači predmeta na prezentaciji o semaforima:"*Koristićemo ih isključivo za sinhronizaciju niti.*"**  
>>> **Takođe predavači predmeta: zadatak 2.1.**  

1. Korišćenjem programskog jezika C kreirati program koji se deli u dva Linux procesa koji generišu slučajne celobrojne vrednosti i upisuju ih u datoteku čiji se naziv prosleđuje kao argument komandne linije glavnog procesa. Prvi proces generiše niz od tri slučajne pozitivne celobrojne vrednosti i upisuje ih u datoteku. Nakon toga drugi proces generiše dve slučajne negativne celobrojne vrednosti i upisuje ih u istu datoteku. Postupak se ponavlja N puta (naizmenično prvi pa drugi proces). Vrednost N se takođe prosleđuje kao argument komandne linije. Sinhronizovati rad procesa korišćenjem semafora.
(Citat odozgo me nije sprečilo da nađem rešenje ovog zadatka. Potrebno je koristiti *imenovane* semafore. Razlog za njihovu upotrebu je što se prilikom kreiranja procesa pravi "nova" memorija za novi proces i promena semafora se ne vide u oba. Rešenje je korišćenje deljenog memorijskog prostora (nije gradivo za prvi kolokvijum) ili imenovanih semafora. Kod ovih semafora što sam uočio da je obavezno da se koristi `unlink` jer će inače ostati ime semfora negde i gubiće se program pri narednim pokretanjima.)

## 3. Datovodi
1. Korišćenjem programskog jezika C kreirati tri Linux procesa koja komuniciraju korišćenjem datavoda. Prvi proces generiše niz proizvoljnih celih brojeva (dužina niza je fiksna i iznosi 20 brojeva) a zatim računa zbir svih tako generisanih brojeva. Ukoliko je dobijeni zbir paran broj, generisani niz brojeva se korišćenjem datavoda šalje drugom procesu koji ih upisuje u datoteku BROJEVI.txt. Ukoliko je dobijeni zbir neparan broj, generisani niz brojeva se korišćenjem datavoda šalje trećem procesu koji ih štampa na standardnom izlazu.

2. Korišćenjem programskog jezika C kreirati tri Linux procesa koja komuniciraju korišćenjem datavoda. 
Prvi proces generiše niz proizvoljnih karaktera (dužina niza je fiksna i iznosi 20 karaktera) a zatim računa zbir ASCII vrednosti svih tako generisanih karaktera. Ukoliko je dobijeni zbir paran broj, generisani niz karaktera se korišćenjem datavoda šalje drugom procesu koji ih upisuje u datoteku KARAKTERI.txt. Ukoliko je dobijeni zbir neparan broj, generisani niz karaktera se korišćenjem datavoda šalje trećem procesu koji ih štampa na standardnom izlazu.

## 3. Ispitni zadaci
1. Jun 2021. Prvi zadatak - Korišćenjem programskog jezika C kreirati Linux program u kome korisnik sa tastature unosi rečenicu. Glavni program zatim kreira dve niti. Prva nit sortira reči u unetoj rečenici u leksikografski opadajućem redosledu, a po završetku sortiranja druga nit na ekranu štampa tu rečenicu tako da samo prva reč počinje velikim slovom, a sve ostale reči malim. Po završetku rada ove dve niti glavni program treba da odštampa: "KRAJ".
2. Jun 2021. Drugi zadatak - Korišćenjem programskog jezika C kreirati Linux program koji oponaša program more. Ovaj program očekuje dva argumenta komandne linije. Prvi argument je naziv programa koji treba da startuje i čiji izlaz da prikazuje ekran po ekran. Drugi argument N je broj linija koje prikazuje na ekranu posle čega prikazuje poruku - MORE - , čeka pritisak bilo kog tastera i nakon toga prikazuje narednih N linija itd...