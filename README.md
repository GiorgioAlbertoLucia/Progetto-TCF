# AnalysisTool

AnalysisTool è uno strumento per l'analisi dati che può essere impiegato per semplici esperienze laboratoriali, come quelle del primo anno del corso di laurea in Fisica. È possibile importare dati da file, gestirli, eseguire fit polinomiali e produrre semplici grafici. 

Si può lavorare tramite il `main.cpp`, dotato di un'interfaccia con menu, o scrivendo un file `.cpp` e includendo le classi necessarie, come mostrato in `data_analysis_example.cpp`.

***
## Librerie (incluse nel progetto)

* [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page "Eigen home page") (calcolo vettoriale e matriciale)
* [pbPlots](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.9.1 "pbPlots Github page") (semplici grafici)

***
## Requisiti

* C++11 o superiore 

***
## Struttura dei file

Benché sia possibile inserire manualmente i dati nel file `.cpp`, AnalysisTool è pensato (e la versione con menu lo richiede) per essere usato leggendo i dati direttamente da file.

#### Formati supportati

* .txt
* .csv

#### Contenuto del file
Per una lettura ottimale del file si richiede di alternare le colonne di grandezze con quelle contenenti i relativi errori. Questa disposizione può essere ignorata lavorando con `double` e `float`, mentre è indispensabile per una corretta lettura da file di Udouble.

#### Commenti
È possibile far precedere la sezione dati da una sezione commentata. Questa viene ignorata nella lettura del file e può risultare utile per eventuali appunti durante la presa dati. Ogni rigo di commento deve iniziare con '#'.

---
Si presenta un esempio (valido per un .txt):
```
# commenti
# commenti
#
#
VH0[mV]       i0[mA]		sVH0[mV]		si0[mA]
-1.95         -8.00			0.039			0.068
-1.71         -7.00			0.0342			0.062
-1.46         -6.00			0.0292			0.056
-1.22         -5.00			0.0244			0.05
```

***
## Come iniziare

Nei successivi step saranno mostrati i comandi per lanciare il programma, nella versione menu interattivo e in quella di script personalizzabile.

### `main.cpp`
Per utilizzare il main con il menu interattivo lanciare, dalla cartella principale,
```
> clang++ -std=c++11 main.cpp src/*.cpp pbPlots/*.cpp -o exe/main 
> ./exe/main
```
Indicando il path relativo o assoluto di un file `.txt` o `.csv` è possibile iniziare l'analisi dati (lettura del file, fit polinomiale tra due colonne). 





### `data_analysis_example.cpp`
Analogamente, dalla cartella principale, lanciare
```
> clang++ -std=c++11 data_analysis_example.cpp src/*.cpp pbPlots/*.cpp -o exe/data_analysis_example 
> ./exe/data_analysis_example
```
È possibile scrivere la propria analisi dati sulla falsariga dell'esempio e poi eseguirla in maniera analoga.


**NOTA:** potrebbe essere necessario includere nel comando anche `-I Eigen`, ad esempio
```
clang++ -std=c++11 -I Eigen data_analysis_example.cpp src/*.cpp pbPlots/*.cpp -o exe/data_analysis_example  
```

***
## Udouble (spiegazione completa)

Questi oggetti, ispirati alla libreria _uncertainties_ di Python, costituiscono uno strumento per lavorare con dati associati a un'incertezza, permettendo di costruire grandezze derivate senza preoccuparsi della propagazione degli errori, che viene effettuata automaticamente.

#### Nota pratica
Come viene spiegato nel paragrafo successivo, la costruzione di uno Udouble a partire da altri oggetti preesistenti dello stesso tipo avviene correttamente tramite l'operatore "=". Per questo motivo, il metodo per ottenere una corretta propagazione dell'errore è il seguente.

```
Udouble x(1., 1., "x"), y(1., 2., "y");

Udouble z;                      // inizializzazione con un costruttore generico 
z = sin(x) + y^2 / tan(x);      // assegnazione
```

Uno Udouble è costituito da un `PartDer`, un errore e una `std::map` che lega un nome a un valore. 

Per la propagazione degli errori ci si serve dei risultati della mappa dello Udouble e del `PartDer` alla base.
La mappa  del PartDer è inizializzata come `{{'nome1', 1.}}`, viene "aggiornata" durante le operazioni (somme, prodotti, ma anche applicazioni di funzioni trigonometriche etc.) e contiene i valori delle derivate parziali fatte rispetto a tutte le grandezze usate per definire la grandezza derivata. 
La mappa dello Udouble contiene gli errori associati a ciascuna delle grandezze. 

Da queste informazioni, l'incertezze delle grandezze derivate viene calcolata come segue.

$G = G(a, b, c, ...)$

$\sigma_G = \sqrt{ \left( \frac{\partial G}{\partial a} \right)^2 \sigma_a^2 + \left( \frac{\partial G}{\partial b} \right)^2 \sigma_b^2 + ... } $

