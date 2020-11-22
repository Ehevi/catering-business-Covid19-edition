## <div align="center">Akademia Górniczo-Hutnicza </div>

### <div align="center"> WIEiT : Informatyka : 3 semestr </div>
## <div align="center"> 2020-2021 </div>
### <div align="center"> PODSTAWY BAZ DANYCH </div>

# <div align="center"> *Dokumentacja projektu* </div>

# <div align="center"> System wspomagania działalności firmy świadczącej usługi gastronomiczne,  _COVID-19 edition_ </div>


###### <div align="center"> :copyright: AGATA CYRA </div>

# 1. Analiza wymagań systemu
## 1. Role w systemie:
\[ system | administrator systemu | klient indywidualny | przedstawiciel firmy | obsługa (pracownicy gastronomii) ]
### 1. System (oprogramowanie)
:computer: generowanie identyfikatorów dla klientów, menu, pozycji w menu, pozycji w ofercie itp..

:computer: dbanie o poprawność danych i zapobieganie błędom (np. zabezpieczenia przed kolizjami przy rezerwacji stolika przez dwie różne osoby)

:computer: aktualizacja danych i funkcjonalności dotyczących zamówień, stolików wraz z upływem czasu (obsługa zamówienia, sprawdzanie dostępności miejsc - np. limit przekroczony: brak możliwości rezerwacji)

:computer: obsługa płatności i historii płatności: zniżki, programy rabatowe, wystawianie paragonu/faktury

### 2. Administrator systemu

:closed_lock_with_key: pełny dostęp do danych w bazie (generowanie raportów, list, podsumowań)

:closed_lock_with_key: "awaryjne" zarządzanie bazą danych poprzez bezpośrednią ingerencję, w skrajnym przypadku możliwość usunięcia bazy danych

:closed_lock_with_key: zatwierdzanie ograniczeń związanych z Covid-19 (np. ograniczenia liczby miejsc przy stolikach)

:closed_lock_with_key: generowanie raportów miesięcznych i tygodniowych, dotyczących rezerwacji stolików, rabatów, menu, a także statystyk zamówienia (dla klientów indywidualnych oraz firm) dotyczących kwot oraz czasu składania zamówień


### 3. Klient indywidualny
:bust_in_silhouette: utworzenie własnego konta (imię + nazwisko)

:bust_in_silhouette: wyświetlenie aktualnego menu

:bust_in_silhouette: wyświetlenie wolnych (możliwych do zarezerwowania) stolików

:bust_in_silhouette: złożenie zamówienia

:bust_in_silhouette: rezerwacja stolika przy składaniu zamówienia

:bust_in_silhouette: złożenie zamówienia na owoce morza

:bust_in_silhouette: opłacenie zamówienia

:bust_in_silhouette: wyświetlenie listy swoich zamówień (np. w celu sprawdzenia historii/statusów płatności/zarezerwowanych stolików)


### 4. Przedstawiciel firmy
:busts_in_silhouette: utworzenie konta firmy (nazwa + email + telefon + NIP)

:busts_in_silhouette: wyświetlenie aktualnego menu

:busts_in_silhouette: wyświetlenie wolnych (możliwych do zarezerwowania) stolików

:busts_in_silhouette: rezerwacja stolika/ów dla firmy: na firmę lub dla konkretnych pracowników firmy (imię + nazwisko)

:busts_in_silhouette: złożenie zamówienia

:busts_in_silhouette: złożenie zamówienia na owoce morza

:busts_in_silhouette: opłacenie zamówienia

:busts_in_silhouette: wyświetlenie listy swoich zamówień np. w celu sprawdzenia historii/statusów płatności/zarezerwowanych stolików


### 5. Obsługa (pracownicy gastronomii)
:fork_and_knife: utworzenie nowego menu poprzez wybranie podgrupy oferty

:fork_and_knife: uaktualnienie oferty

:fork_and_knife: tymczasowe usunięcie pozycji z menu na skutek wyczerpania się półproduktów

:fork_and_knife: akceptacja spływających zamówień, rezerwacji stolików.

:fork_and_knife: obsługa zamówień


## 2. Informacje szczegółowe
### Oferta

:memo: w ofercie jest żywność (np. ciastka, lunch, drobne przekąski) oraz napoje bezalkoholowe (np. kawa, koktajle, woda)

:memo: usługi świadczone są na miejscu oraz na wynos

:memo: sposoby składania zamówień: w lokalu | za pośrednictwem formularza WWW (wybór preferowanej daty i godziny odbioru zamówienia)

### Ograniczenia

:memo: firma dysponuje ograniczoną liczbą stolików, w tym miejsc siedzących

:mask: zmieniające się ograniczenia związane z Covid-19: w poszczególnych dniach może być dostępna ograniczona liczba miejsc (w odniesieniu do powierzchni lokalu), zmienna w czasie

### Menu

:memo: ustalane jest z co najmniej dziennym wyprzedzeniem

:memo: co najmniej połowa pozycji menu jest zmieniana co najmniej raz na dwa tygodnie

:memo: pozycja zdjęta z menu nie może powtórzyć się wcześniej niż za miesiąc

:sushi: w dniach czwartek-piątek-sobota istnieje możliwość wcześniejszego zamówienia dań zawierających owoce morza - z uwagi na indywidualny transport takie zamówienie powinno byc złożone *najpóźniej w poniedziałek poprzedzający zamówienie*

:x: istnieje możliwość, że pozycja w menu zostanie czasowo niedostępna na skutek wyczerpania się półproduktów

### Rezerwacje

:memo: istnieje możliwość wcześniejszej rezerwacji stolika dla *co najmniej dwóch osób*

:memo: aby dokonać rezerwacji należy spełnić co najmniej jeden z warunków:

a) minimalna wartość zamówienia składanego przy rezerwacji: 50 zł

b) zapis w historii potwierdzający dokonanie min. 5 wcześniejszych zamówień

c) jeżeli mniej niż 5 wcześniejszych zamówień: na kwotę min. 200 zł

:memo: rezerwujący otrzymuje potwierdzenie zamówienia po akceptacji przez obsługę

:memo: rezerwacja przez firmy:

a) rezerwacja stolików *na firmę*

b) rezerwacja stolików *dla konkretnych pracowników* (imiennie)

### Rabaty
a) programy rabatowe dla klientów indywidualnych:

- Po realizacji ustalonej liczby zamówień Z1 (np. Z1=10) za co najmniej określoną kwotę K1 (np. K1=30 zł każde zamówienie): R1%(np. R1=3%) zniżki na wszystkie zamówienia.

- Po realizacji kolejnych Z1 (np. Z1=10) zamówień za co najmniej określoną kwotę K1 (np. K1=20 zł) każde: dodatkowe R1% zniżki na wszystkie zamówienia (np. R1=3%)

- Po realizacji zamówień za łączną kwotę K2 (np. 1000 zł): jednorazowa zniżka R2% (np. 5%) na zamówienia złożone przez D1 (np. D1=7) dni, począwszy od dnia przyznania zniżki

- Po realizacji zamówień za łączną kwotę K3 (np. K3=5000 zł): jednorazowa zniżka R3% (np. R3=5%) na zamówienie złożone przez D2 (np. D2=7) dni, począwszy od dnia przyznania zniżki

b) zasady udzielania rabatów dla firm:

- Za każdy kolejny miesiąc, w którym dokonano co najmniej FZ zamówień (np. FZ=5) za łączną kwotę co najmniej FK1 (np. FK1=500 zł): rabat FR1% (np. FR1=0,1%). W przypadku braku ciągłości w zamówieniach rabat zeruje się. Łączny, maksymalny rabat to FM% (np. FM=4%).

- Za każdy kolejny kwartał, w którym dokonano zamówień za łączną kwotę FK2 (np. FK2=10.000 zł): rabat kwotowy równyt FR2% (np. FR2=5%) z łącznej kwoty, z którą zrealizowano zamówienie.

### Raporty :chart_with_upwards_trend:
Generowanie raportów *miesięcznych* i *tygodniowych* dotyczących:

- rezerwacji stolików,

- rabatów, 

- menu,

- statystyk zamównienia (dla klientów indywidualnych oraz firm): dotyczących kwot oraz czasu składania zamówienia

Generowanie "raportów" (faktury/paragonu) dotyczących zamówień + rabatów dla klientów indywidualnych oraz firm.

Faktura dla firmy: wystawiona dla danego zamówienia lub zbiorcza raz na miesiąc.
