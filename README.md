# Dining-Philosophers-Problem

# Dining Philosophers Problem

## Opis projektu
Ten projekt implementuje rozwiązanie problemu filozofów przy stole w języku C z użyciem wątków i semaforów. Program ilustruje zarządzanie współdzielonymi zasobami (widełkami) oraz synchronizację wątków.

## Funkcjonalności
1. Symulacja pięciu filozofów medytujących, jedzących oraz czekających na widelce.
2. Synchronizacja wątków za pomocą:
   - Semaforów (`sem_t`) dla widelców.
   - Muteksu (`pthread_mutex_t`) dla operacji wejścia-wyjścia (zapobieganie nakładaniu się wypisywania przez wątki).
3. Realizacja 7 cykli jedzenia dla każdego filozofa.

## Struktura kodu
- **Stany filozofów**:
  - `m`: medytuje,
  - `C`: czeka,
  - `L`: bierze lewy widelec,
  - `P`: bierze prawy widelec,
  - `J`: je,
  - `l`: odkłada lewy widelec,
  - `p`: odkłada prawy widelec,
  - `-`: kończy jedzenie.
- Synchronizacja operacji na widelcach za pomocą semaforów.
