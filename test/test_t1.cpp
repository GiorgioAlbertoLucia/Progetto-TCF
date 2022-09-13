#include "../include/udouble.hpp"
#include "../include/fileFactory.hpp"

#include <iostream>

using namespace std;

// Da eseguire sul terminale con 
// clang++ -std=c++11 test/test_t1.cpp src_t/txtFile_t.cpp src_t/csvFile_t.cpp src_t/partder.cpp src_t/udouble.cpp -o exe/test_t1

// PER FRA: COME FUNZIONA (E NON FUNZIONA) UDOUBLE: 
// La costruzione di uno udouble dal nulla è banale: lo inizializzi con valore, errore e (se vuoi) nome. 
// La costruzione di uno udouble che sia espressione di altri udouble (quindi la costruzione di una grandezza derivata) va fatta
// inizializzando PRIMA uno udouble senza valore, POI uguagliandolo all'espressione. 

// Questa cosa è dovuta a come lavora c++, da quanto mi sembra di capire. Pensavo che z = x + y la interpretasse come 
// un'addizione e un'assegnazione. Mi sembra di vedere che la consideri semplicemente un'addizione. A questo punto, mi potresti dire,
// si può pensare di correggerlo. La correzione, però, renderebbe impossibile lavorare con la sintassi che ho proposto io, quindi
// comunque si tratterebbe solo di fare la scelta. Vorrei tanto dirti che la scelta è dettata dalla pigrizia di aver già scritto il
// codice, in realtà farlo al contrario romperebbe un sacco di altre cose, direi. Accettiamolo e andiamo avanti.

// Nell'esempio ti mostro cosa succede inizializzando uno udouble somma nei due modi elencati e osservando i risultati a confronto

int main() {
	Udouble x(1., 1., "x"), y(1., 2., "y");



	// Metodo corretto
	Udouble z;
	z = 5 * y;
	cout << x << " " << y << " " << z << endl;

//    // Metodo sbagliato
//    Udouble w = x + y;
//
//    cout << x << endl << y << endl << "z = " << z << endl << "w = " << w << endl;
//    // NOTA: agli udouble derivati vengono assegnati nomi automatici, arricchisco il printout per renderli leggibili
//
//
//
//    // NOTA: pur dandogli un nome, questo viene sovrascritto. Non è importante il nome, in realtà. È importante che ne abbiano uno diverso
//    // perché la diversificazione degli errori si basa su un sistema di mappe i cui indici sono i nomi delle grandezze (a grandezze
//    // diverse, errori diversi).
//    Udouble zeta(0., 0., "z");
//    zeta = x + y;
//    cout << zeta << endl;

	return 0;
}

