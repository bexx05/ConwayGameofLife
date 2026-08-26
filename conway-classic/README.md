# Conway's Game of Life - Implementare POO în C++

## 1. Enunțul Problemei

**Ce se dă:**
Se cere implementarea unei simulări de tip automat celular (Game of Life) folosind principiile Programării Orientate pe Obiecte. Simularea presupune o grilă de celule care evoluează în timp pe baza unor seturi de reguli matematice. Fiecare celulă poate fi "vie" sau "moartă", iar starea ei viitoare depinde de numărul de vecini vii din proximitatea sa (vecinătatea Moore). Proiectul trebuie să suporte diferite variante de reguli (Conway, HighLife, DayNight).

**Ce se cere:**
Să se utilizeze o ierarhie de clase pentru tipurile de celule, gestionarea memoriei cu pointeri std (`std::shared_ptr`), tratarea erorilor prin excepții personalizate și vizualizarea grafică a simulării folosind biblioteca SFML. Codul trebuie să demonstreze concepte precum polimorfismul, metodele statice și utilizarea moștenirii din C++.

---

## 2. Modul de Rezolvare

### 2.1 Arhitectura Claselor

**Clasa de Bază: `Cell`**
Definește comportamentul abstract al unei celule în sistem.
* **Atribute protejate:**
    * `bool isAlive_` - starea curentă a celulei.
    * `static int livingCellCount` - variabilă statică ce contorizează în timp real numărul total de celule vii din simulare.
* **Metode virtuale (private/protejate):**
    * `survives(int neighbors)` - regula de supraviețuire.
    * `born(int neighbors)` - regula de naștere.
* **Interfață Non-Virtuală (NVI):**
    * `nextState(int neighbors)` - determină starea viitoare apelând polimorfic metodele de reguli.
* **Justificare:** Permite uniformizarea logicii de actualizare a grilei indiferent de setul de reguli aplicat.

**Clase Derivate:**
1.  **`ConwayCell`**: Implementează regulile clasice: supraviețuiește cu 2 sau 3 vecini, se naște cu exact 3 (B3/S23).
2.  **`HighLifeCell`**: O variantă unde celulele se nasc la 3 sau 6 vecini (B36/S23).
3.  **`DayNightCell`**: Un model complex unde supraviețuirea are loc la 3, 4, 6, 7, 8 vecini, iar nașterea la 3, 6, 7, 8 (B3678/S34678).



**Clasa de Gestionare: `Grid`**
Responsabilă de logica simulării și randare.
* Folosește un `std::vector<std::vector<std::shared_ptr<Cell>>>` pentru stocarea polimorfă a celulelor.
* Gestionează fereastra SFML și ciclul principal de `update()` și `draw()`.

### 2.2 Gestionarea Excepțiilor

S-a implementat o ierarhie proprie de excepții pentru a valida input-ul utilizatorului:
* **`GridInitializationException`**: Aruncată dacă dimensiunile grilei (rânduri/coloane) sunt în afara limitelor 1-100.
* **`InvalidCellTypeException`**: Aruncată dacă utilizatorul alege un tip de celulă în afara opțiunilor 1-3.
* **`InvalidProbabilityException`**: Validarea factorului de densitate (probabilitatea) pentru popularea inițială.

### 2.3 Utilizare Polimorfism și Dynamic Cast

* **Polimorfism la Update:** În metoda `Grid::update()`, se iterează prin vectorul de pointeri către `Cell` și se apelează `isAlive()`, `survives()` sau `born()`, ignorând tipul specific al celulei.
* **Dynamic Cast:** În metoda `printCellTypeStats()`, se utilizează `std::dynamic_pointer_cast` pentru a identifica tipul concret al obiectelor (Conway, HighLife sau DayNight) la runtime și a genera statistici specifice.

### 2.4 Date și Funcții Statice

* **`livingCellCount`**: Urmărește automat numărul de celule vii. Este incrementată în constructor și decrementată în destructor.
* **`getLivingCellCount()`**: Metodă statică ce oferă acces la numărul total de celule vii fără a necesita o instanță specifică.

### 2.5 Elemente de Logică (SFML)

* **Desen**: Se utilizează `sf::RectangleShape` pentru a desena celulele vii pe o fereastră cu fundal negru.
* **Vecinătate**: Metoda `countNeighbors` verifică cei 8 vecini adiacenți, asigurând că indicii rămân în limitele grilei.
* **Randomizare**: Folosirea `std::mt19937` și `std::bernoulli_distribution` pentru o populare inițială bazată pe probabilitate.

---

## 3. Conformitate cu Cerințele

| Cerință | Status | Detalii |
| :--- | :--- | :--- |
| Split header/source | ✅ | Fiecare clasă are fișiere `.h` și `.cpp` separate. |
| Ierarhie (1 bază + 3 derivate) | ✅ | Cell (bază) -> ConwayCell, HighLifeCell, DayNightCell. |
| Virtuale și NVI | ✅ | `nextState` (public) apelează `survives`/`born` (virtuale). |
| Pointer bază + Downcast | ✅ | `shared_ptr<Cell>` și `dynamic_pointer_cast` în statistici. |
| Ierarhie excepții | ✅ | 3 tipuri distincte bazate pe `std::invalid_argument`/`out_of_range`. |
| Date și funcții statice | ✅ | `livingCellCount` și `getLivingCellCount`. |
| Operator << | ✅ | Supraîncărcat pentru afișarea detaliată a fiecărei excepții. |
| Fără citiri în loop | ✅ | Citirea datelor se face prin `std::cin` doar la start în `main`. |

---

## 4. Compilare și Rulare

**Dependențe:**
* SFML 2.5+ (Simple and Fast Multimedia Library)
* Compilator C++17 sau mai nou

**Rulare:**
1. Introdu rândurile și coloanele (1-100).
2. Selectează tipul de celulă (1, 2 sau 3).
3. Se deschide fereastra grafică. Apasă `Escape` sau butonul Close pentru a ieși.

---

## 5. Bibliografie
* [SFML Documentation](https://www.sfml-dev.org/documentation/2.5.1/)
* [Conway's Game of Life Rules](https://conwaylife.com/wiki/Conway%27s_Game_of_Life)
* [Modern C++ Design Patterns (NVI)](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-Virtual_Interface)
* Tutorial yt https://www.youtube.com/watch?v=daFYGrXq0aw
* Alt tutorial yt https://www.youtube.com/watch?v=9NK5holxvOw
