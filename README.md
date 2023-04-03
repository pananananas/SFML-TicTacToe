# SFML-TicTacToe

Gra Kółko i Krzyżyk napisana w c++ z użyciem biblioteki SFML pozwalającej na stworzenie GUI. W grze można grać przeciwko innemu graczowi, lub zmierzyć się z algorytmem MinMax. Algorytm MinMax jest rozszerzony o cięcia alfa beta, aby działał optymalniej. Gra obsługuje wiele rozmiarów plansz (od 3x3 do 6x6) i umożliwia ustawienie ile pól wygrywa.

## Przykładowe screeny z gry:
<img width="612" alt="Main%20menu" src="https://user-images.githubusercontent.com/101266606/225125748-0d71c419-d849-4f87-8e7b-23d49dbf191c.png">
<img width="612" alt="1" src="https://user-images.githubusercontent.com/101266606/225125557-84ec7cbf-c5c1-4944-8c81-b9c40cc09799.png">
<img width="612" alt="2" src="https://user-images.githubusercontent.com/101266606/225125731-1932eacb-c35a-4134-a39b-97acef26fa9c.png">
<img width="612" alt="3" src="https://user-images.githubusercontent.com/101266606/225125734-6e5d641f-6d4c-4fbf-bc90-4e623cf6fb71.png">
<img width="612" alt="4" src="https://user-images.githubusercontent.com/101266606/225125738-c1a1cf50-b231-4eaf-9a62-b68131572905.png">
<img width="612" alt="5" src="https://user-images.githubusercontent.com/101266606/225125742-1cdb7d25-41f6-4e2d-9c23-c7993ea499cd.png">
<img width="612" alt="Splash" src="https://user-images.githubusercontent.com/101266606/225125751-1d74208e-58b9-4a22-8daa-8adf5cbb736e.png">

***

## Wnioski
- Po zaimplementowaniu algorytmów program zawsze wygrywa (jeśli gramy nieefektywnie), lub remisuje, gdy gramy efektywnie. Oznacza to, że algorytm został wdrożony odpowiednio i działa prawidłowo.
- Implementacja algorytmu cięć alfa beta znacznie poprawia szybkość pracy programu, zwłaszcza dla dużych plansz.
- Zauważyłem, że gdy algorytm wie, że na pewno wygra to nie wygrywa od razu, tylko na przykłąd w kolejnym ruchu, ale w żadnym wypadku gdy algorytm ma wygraną "w ręku" nie udało mi się wygrać.
- Dla wielkości 5x5 program działa bardzo wolno, gdyż z każdą możliwością ruchu musi wyliczyć bardzo dużo wariantów. Zmniejszenie maksymalnej głębokości pomaga, ale niestety wtedy program nie potrafi się bronić przed atakiem i przegrywa.
