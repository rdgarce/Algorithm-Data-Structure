/*

Trovare il modo migliore di tagliare una panca di legno per ottimizzare il guadagno

-----------------
|   |   |   |   |
-----------------

1  2  3  4  5
10 24 30 40 45

1) Def Sottoproblema: Risolvo il sottoproblema per n - l_i data la scelta di tagliare o meno
   alla lunghezza l_i => Il # dei sottoproblemi è n
2) La scelta di l_i => O(n)
3) P(k) = G(l_i) + P(k-l_i)

4) R(n) = max_{l_i}{ G(l_i) + R(n-l_i) }


*/

int main(){

}