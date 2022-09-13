# AnalysisTool

AnalysisTool è uno strumento per l'analisi dati che può essere impiegato per semplici esperienze laboratoriali, come quelle del primo anno del corso di laurea in Fisica. È possibile importare dati da file, gestirli ed eseguire fit polinomiali. 

Si può lavorare tramite il `main.cpp`, dotato di un'interfaccia con menu, o scrivendo un file `.cpp` e includendo le classi necessarie, come mostrato in `data_analysis_example.cpp`.

***
## Librerie (incluse nel progetto)

* Eigen (calcolo vettoriale e matriciale)
* matplotlibcpp (interprete per la libreria matplotlib di Python - semplici grafici)

***
## Requisiti

* C++11 o superiore 
* Python2.7 o superiore





***
## Come iniziare

Nei successivi step saranno mostrati i comandi per lanciare il programma, nella versione menu interattivo e in quella di script personalizzabile. All'interno, è necessario includere i path ad alcune cartelle di Python. Questi sono in realtà dei requisiti di `matplotlib.cpp`, che possono essere approfonditi sulla [pagina ufficiale](https://matplotlib-cpp.readthedocs.io/en/latest/ "matplotlibcpp Home"). Si riassumono, comunque, qui.

* locazione dell'header `Python.h`
* locazione dell'header per gli array numpy `numpy/arrayobjects.h`
* locazione della libreria `libpython*.so`
* specificazione della libreria con `-lpython*`

Sono rispettivamente aggiunti in questo modo (inserisco i path standard dopo un'installazione con Homebrew)
```
-I /Library/Frameworks/Python.framework/Versions/3.9/include/python3.9
-I /Library/Frameworks/Python.framework/Versions/3.9/lib/python3.9/site-packages/numpy/core/include/
-L /Library/Frameworks/Python.framework/Versions/3.9/lib
-lpython3.9
```

### `main.cpp`
Per utilizzare il main con il menu interattivo lanciare, dalla cartella principale,
```
> clang++ -std=c++14 main.cpp src/*.cpp -o main 
> ./main
```
Indicando il path relativo o assoluto di un file `.txt` o `.csv` è possibile iniziare l'analisi dati (lettura del file, fit polinomiale tra due colonne). 





### `data_analysis_example.cpp`
Analogamente, dalla cartella principale, lanciare
```
> clang++ -std=c++14 data_analysis_example.cpp src/*.cpp -o data_analysis_example 
> ./data_analysis_example
```
È possibile scrivere la propria analisi dati sulla falsariga dell'esempio e poi eseguirla in maniera analoga.


**NOTA:** potrebbe essere necessario includere nel comando anche `-I Eigen`, ad esempio
```
clang++ -std=c++14 -I Eigen data_analysis_example.cpp src/*.cpp -o data_analysis_example  
```

***
## Udouble (spiegazione completa)

Questi oggetti, ispirati alla libreria _uncertainties_ di Python, costituiscono uno strumento per lavorare con dati associati a un'incertezza, permettendo di costruire grandezze derivate senza preoccuparsi della propagazione degli errori, che viene effettuata automaticamente.

Uno Udouble è costituito da un `PartDer`, un errore e una `std::map` che lega un nome (nome di una variabile) a un valore (derivata rispetto a quella variabile). 

Per la propagazione degli errori ci si serve dei risultati della mappa dello Udouble e del `PartDer` alla base.
La mappa  del PartDer è inizializzata come `{{'nome1', 1.}}` e viene "aggiornata" durante le operazioni (somme, prodotti, ma anche applicazioni di funzioni trigonometriche etc.) e contiene i valori delle derivate parziali fatte rispetto a tutte le grandezze usate per definire la grandezza derivata. 
La mappa dello Udouble contiene gli errori associati a ciascuna delle grandezze. 

Da queste informazioni, è possibile costruire l'incertezze della grandezza derivata come segue.

$G = G(a, b, c, ...)$

$\sigma_G = \sqrt{ \left( \frac{\partial G}{\partial a} \right)^2 \sigma_a^2 + \left( \frac{\partial G}{\partial b} \right)^2 \sigma_b^2 + ... } $

