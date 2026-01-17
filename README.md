# A.I FIGHTER - FREEDOM KEEPER

## Opis projektu
**A.I FIGHTER - FREEDOM KEEPER** to gra typu **Tower Defense** napisana w języku **C++** z wykorzystaniem biblioteki **SFML**.  
Gracz broni swojej bazy przed kolejnymi falami przeciwników, budując wieżyczki na wyznaczonych kafelkach mapy.  
Projekt skupia się na architekturze obiektowej, systemie stanów gry oraz praktycznym użyciu SFML.

---

## Funkcje gry
- System stanów (Menu, Gra, Pauza, Ekran wygranej/przegranej)
- Mapa wczytywana z pliku tekstowego
- System fal przeciwników
- Różne typy potworów (Basic, Fast, Tank)
- Różne typy wieżyczek (BasicTower, LaserTower)
- System pocisków i obrażeń
- Obrót wieżyczek w stronę najbliższego przeciwnika
- UI: HP, Gold, Wave, przyciski
- Pauza gry
- Muzyka i dźwięki zależne od stanu gry

---

## Sterowanie
- **Mysz** – wybór kafelków, przycisków i wieżyczek  
- **LPM** – interakcja (budowa wieżyczek, przyciski UI)  
- **P** – pauza / wznowienie gry  
- **START (przycisk)** – rozpoczęcie aktualnej fali przeciwników  

---

## Instrukcja uruchamiania
Projekt **wymaga** obecności następujących plików:
- `assets/` – tekstury, muzyka i dźwięki
- `comicFont.ttf` – font używany w UI
- `mapx.txt` – definicja mapy
- `Kompilator obsługujący **C++17** lub nowszy`  
- `SFML 3.x`
- `Visual Studio 2022`
- `System Windows`
- Brak któregokolwiek z tych plików może spowodować niepoprawne działanie gry!

1.Otwórz plik z rozszerzeniem .sln w Visual Studio
2.Podlinkuj niezbędne biblioteki SFML
  -sfml-graphics
  -sfml-window
  -sfml-system
  -sfml-audio
  3.Ustaw konfigurcje projektu na Debug/x64
  4.Naciśnij przycisk F5
