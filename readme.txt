/**********************************************************************
 *  Knäcka lösenord readme.txt
 **********************************************************************/

/**********************************************************************
 *  Ge en högnivåbeskrivning av ditt program decrypt.cpp.
 **********************************************************************/
VŒrt program delar upp tabellen i tvŒ delar och berŠknar fšrst och sparar 
undan alla summor som kan bildas utav kombinationer av den fšrsta 
deltabellens rader. DŠrefter rŠknar det ut alla delsummor som kan bildas 
utav raderna i den andra deltabellen, utan att spara dessa vŠrden, och 
kollar om var och en utav dessa kan kombineras med nŒgon delsumma i den 
fšrsta delen fšr att bilda det krypterade lšsenordet. Om en kombination 
hittas sŒ sparas de rader som bildar kombinationen undan och konverteras 
till en strŠng som representerar en kandidat till det okrypterade 
lšsenordet.

/**********************************************************************
 *  Beskriv symboltabellen du använt för decrypt.cpp.
 **********************************************************************/


/**********************************************************************
 *  Ge de dekrypterade versionerna av alla lösenord med 8 och 10
 *  bokstäver i uppgiften du lyckades knäcka med DIN kod.
 **********************************************************************/


8 bokstäver         10 bokstäver
-----------         ------------
congrats	     completely
youfound	     unbreakabl
theright	     cryptogram
solution	     ormaybenot

/****************************************************************************
 *  Hur lång tid använder brute.cpp för att knäcka lösenord av en viss 
 *  storlek? Ge en uppskattning markerad med en asterisk om det tar längre 
 *  tid än vad du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ***************************************************************************/


Char     Brute     
--------------
 4	 1.843s
 5	73.693s
 6
 8


/******************************************************************************
 *  Hur lång tid använder decrypt.cpp för att knäcka lösenord av en viss 
 *  storlek?
 *  Hur mycket minne använder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)    Minne (bytes)
----------------------------------------
6		 0.746		fšr snabb
8		25.516		 ~750000000
10		1678.756	~5174000000
12

/*************************************************************************
 * Hur många operationer använder brute.cpp för ett N-bitars lösenord?
 * Hur många operationer använder din decrypt.cpp för ett N-bitars lösenord?
 * Använd ordo-notation.
 *************************************************************************/
brute anvŠnder O(2^N) operationer
decode anvŠnder O(2^(N/2+1)) operationer dŒ den kšr 
k*2^(N/2)+l*2^(N/2) = (k+l)*2^(N/2) ³ 2*2^(N/2) = 2^(N/2) gŒnger
fšr nŒgra kšnstanter k,l ³ 1.
