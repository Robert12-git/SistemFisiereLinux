                                                                            Tema 1 - Sistemul lui Biju

    Scopul temei il constituie simularea unui sistem de fisiere, implementand
utilizand limbajul de programare C comenzile:
    *touch
    *mkdir
    *ls
    *rm
    *rmdir
    *cd
    *tree
    *pwd
    *mv

    Pentru realizarea acestor comenzi au fost necesare realizarea functiilor
aferente comenzilor astfel incat in urma introducerii input ului corespunzator
sa aiba loc realizarea task-urilor aferente.

    Citirea comenzilor se face din stdin in cadrul programului, citind linie
cu linie utilizand functia getline ce citeste linie cu linie, luand in seama
si caracterul "\n", pentru ca ulterior sa accesam cuvintele cheie corespunzatoare
utilizand functia strtok si pattern-ul de spargere al string-ului " \n" deoarece
se cunoaste faptul ca dupa ce este introdusa comanda se introduce unul sau 2
parametri necesare in functie de comanda necesara utilizarii.

    Inainte de a se putea incepe vreo operate la nivelul sistemului de directoare
a fost necesar creearea directorului home, acest lucru a necesitat creearea unui
functii desemnata Dir *homeDir () ce initializeaza memoria necesara pentru
directorul home si ii da si numele corespunzator, utilizand pentru partea
de alocare de memorie functia void initDir (Dir *directory, char *name, Dir *parent)
ce primeste ca parametrii de intrare directorul ce se doreste a fii alocat,
numele ce se doreste a fi atribuit si directorul sau parinte, aceasta functie este
importanta atat pentru functia homeDir cat si pentru functia mkdir

    Descrierea comenzilor de prelucrare a sistemului de fisiere precum si
descrierea functiilor aferente:

    1.Touch:
    -comanda touch are rolul de a creea un nou fisier in interiorul directorului
curent
    -functia aferenta acestei comenzi primeste ca parametrii directorul parinte,
acesta fiind directorul in care se doreste crearea noului fisier, iar al doilea
parametru il constituie numele ce se doreste a fi atribuit noului fisier
    -in cadrul acestei functii prima data se utilizeaza functia searchName
pentru a se determina daca fisierul exista deja sau nu in cadrul fisierului
curent, iar daca functia returneaza o valoare mai mare decat 0 inseamna ca
nu a fost gasit niciun fisier sau director cu acest nume, si astfel se poate
face crearea noului fisier utilizand functia addFile ce creeaza fisierul
si il introduce in cadrul listei de fisiere tinand cont sa nu modifice
proprietatea listei ca elementele sa existe in ordine alfabetica

    2.Mkdir:
    -mkdir realizeaza acelas lucru ca si comanda touch, dar nu se mai manifesta
prin creeare unui nou fisier, ci prin crearea unui nou director
    -modul de implementare al functiei mkdir este identica din punct de vedere
logic asemeni functiei touch

    3.Ls:
    -comanda ls afiseaza toate directoarele si toate listele din directorul
curent afisate unele sub altele
    -functia void ls (Dir *parent) primeste ca parametru directorul curent
si acceseaza listele de directoare si de fisiere din cadrul directorului
curent astfel incat utilizand 2 structuri repetitive sa se afiseze numele
obiectelor existente in cadrul directorului curent

    4.Rm:
    -comanda rm se aplica fisierelor si asigura stergerea unui fisier din
directorul curent, in cazul in care este fisier exista, si eliberearea
memoriei corespunzatoare fisierului proaspat eliminat din lista de fisiere
    -ca si implementare, void rm (Dir *parent, char *name) primeste ca parametri
directorul curent si numele fisierului de eliminat si dupa se acceseaza
lista de fisiere utilizand o structura repetitiva pentru a se determina daca
exista sau nu fisierul cautat, in cazul in care se gaseste se refac legaturile
astfel incat sa nu se mai poata accesa fisierul de eliminat in cadrul listei,
dupa care fisierul de eliminat fiind retinut intr-o variabila auxiliara
incepe procesul de eliberare de memorie dand free atat la numele fisierului
cat si la structura de fisier

    5.Rmdir:
    -comanda rmdir asigura stergerea unui directorul din cadrul listei de
directoare din cadrul directorului curent, eliminand totodata si intregul
continut al acestui director
    -functia void rmdir (Dir *parent, char *name) functioneaza asemeni functiei
rm, cu precizarea ca daca acceseaza recursiv toate datele din cadrul directorului
ce se doreste a fi eliminat din cadrul directorului curent

    6.Cd:
    -comanda cd este utilizata pentru a se face schimbarea directorului curent
    -void cd (Dir **target, char *name) cauta prin lista de directoare directorul
care detine numele dat si dupa modifica adresa retinuta de target astfel incat sa
se modifice adresa directorului curent cu noul director ce se doreste a fi accesat
    -daca se doreste intoarcerea la directorul parinte, este implementat comparatia
dintre numele dat ca parametru si string-ul ".." iar in caz de egalitate target
devine target = target->parent

    7.Pwd:
    -comanda pwd afiseaza calea absoluta la care se afla directorul curent
    -char *pwd (Dir *target) primeste ca parametru directorul curent, iar prin
intermediul functiei void pwdUtils (Dir *target, char *path, itn *length)
programul se intoarce recursiv prin lantul de directoare parinte pana ajunge
la directorul home astfel incat sa inceapa sa scrie path-ul corespunzator
intr-un buffer prin intermediul functiei sprintf pentru a asigura evitarea
erorilor de scriere in memorie

    8.Tree:
    -comanda tree afiseaza ierarhic toate fisierele si directoarele ce se afla
in cadrul directorului curent
    -functia tree (Dir *target, int level) este conceputa recursiv astfel incat
sa introduca numarul de spatii necesare pe fiecare linie in functie de nivelul
la care se afla fata de directorul curent, sa afiseaze fisierele necesare si
pe linia de intoarcere din recursivitate sa afiseze si numele directoarelor
aferente fisierelor ce au fost deja afisate

    9.Mv:
    -comanda mv schimba numele unui fisier sau al unui director
    -funtia mv a fost candita astfel incat sa gaseasc verifice daca se poate
face modificare de nume, iar in caz afirmativ se creeaza un nou fisier sau
director (stabilirea daca este fisier sau director se face cu functia fileOrDir),
iar identificarea obiectului vechi si al celui nou creeat se face cu functia
findObject ce primeste ca parametru tipul de data , numele ce se cauta si
parintele
    -ulterior, se copiaza informatiile din vechiul obiect in noul obiect,
se rup legaturile cu vechiul obiect si ulterior se sterge memoria vechiului
obiect

    Pentru oprirea programului s-a implementat functia void stop (Dir * target)
unde este apelata functia deleteDir ce asigura eliberarea intregii memorii
alocate pentru toate instantele initializate