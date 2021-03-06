/**********************************************************************
 *  Kn�cka l�senord readme.txt
 **********************************************************************/

/**********************************************************************
 *  Ge en h�gniv�beskrivning av ditt program decrypt.cpp.
 **********************************************************************/
V�rt program delar upp tabellen i tv� delar och ber�knar f�rst och sparar 
undan alla summor som kan bildas utav kombinationer av den f�rsta 
deltabellens rader. D�refter r�knar det ut alla delsummor som kan bildas 
utav raderna i den andra deltabellen, utan att spara dessa v�rden, och 
kollar om var och en utav dessa kan kombineras med n�gon delsumma i den 
f�rsta delen f�r att bilda det krypterade l�senordet. Om en kombination 
hittas s� sparas de rader som bildar kombinationen undan och konverteras 
till en str�ng som representerar en kandidat till det okrypterade 
l�senordet.

/**********************************************************************
 *  Beskriv symboltabellen du anv�nt f�r decrypt.cpp.
 **********************************************************************/
Som symboltabell har vi anv�nt en multimap. Detta utifall flera olika kombinationer
skapar samma summa. Det skulle leda till att det finns flera kandidater till l�senordet
som alla kan vara r�tt.

/**********************************************************************
 *  Ge de dekrypterade versionerna av alla l�senord med 8 och 10
 *  bokst�ver i uppgiften du lyckades kn�cka med DIN kod.
 **********************************************************************/


8 bokst�ver         10 bokst�ver
-----------         ------------
congrats	     completely
youfound	     unbreakabl
theright	     cryptogram
solution	     ormaybenot

/****************************************************************************
 *  Hur l�ng tid anv�nder brute.cpp f�r att kn�cka l�senord av en viss 
 *  storlek? Ge en uppskattning markerad med en asterisk om det tar l�ngre 
 *  tid �n vad du orkar v�nta. Ge en kort motivering f�r dina uppskattningar.
 ***************************************************************************/


Char     Brute     
--------------
 4	 1.843s
 5	73.693s
 6	3017s * 
 8	5058857s * 

(* Vi ber�knade en ungef�rlig formel och stoppade in v�rdena som skulle ber�knas)



/******************************************************************************
 *  Hur l�ng tid anv�nder decrypt.cpp f�r att kn�cka l�senord av en viss 
 *  storlek?
 *  Hur mycket minne anv�nder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar l�ngre tid �n vad
 *  du orkar v�nta. Ge en kort motivering f�r dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)    Minne (bytes)
----------------------------------------
6		 0.746		f�r snabb
8		25.516		 ~750000000
10		1678.756	~5174000000
12		>10h *		~5174000000

Vi uppskattade att minnes�tg�ngen skulle vara den samma f�r 12 chars som f�r 10 chars d� vi valde att g�ra den minneskr�vande
delen lika stor f�r b�da.

/*************************************************************************
 * Hur m�nga operationer anv�nder brute.cpp f�r ett N-bitars l�senord?
 * Hur m�nga operationer anv�nder din decrypt.cpp f�r ett N-bitars l�senord?
 * Anv�nd ordo-notation.
 *************************************************************************/
brute anv�nder O(2^N) operationer
decode anv�nder O(2^(N/2+1)) operationer d� den k�r 
k*2^(N/2)+l*2^(N/2) = (k+l)*2^(N/2) � 2*2^(N/2) = 2^(N/2) g�nger
f�r n�gra k�nstanter k,l � 1.
