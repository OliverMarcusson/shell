* Vad är en kommandotolk?

En kommandotolk är ett program som tar in data från en användare i form av kommandon, för att sedan hantera och exekvera dessa kommandon. Exempel på vanliga kommandotolkar är Microsofts CMD, Powershell, samt olika linux-skal som bash, sh och fish.

* Hur kan din kommandotolk byggas ut för att stödja paralell exekvering av kommandon? Och hur kan kommandon exekverade i separata processer kommunicera med varandra?

Min kommandotolk kan byggas ut för att stödja paralell exekvering av kommandon med hjälp av funktionen fork() som specifieras i POSIX-standarden. Denna funktion tillåter ett kommando att starta en ny process för sig själv. För att dessa processer ska kunna kommunicera med varandra kan IPC, eller "interprocess communication" användas. Ett vanligt kommunikationsmedel inom IPC är pipes eller named pipes, som är tvåvägstunnlar som processer kan använda för att dela data med varandra.

* Hur kan din kommandotolk byggas ut för att stödja exekvering av kommandon i bakgrunden?

Min kommandotolk kan byggas ut för att stödja exekvering i bakgrunden på samma sätt som i förra frågan, nämligen genom att använda fork(). Funktionen kommer att köra processen i bakgrunden och förälder-processen kommer inte att vänta på den förrens en funktion som waitpid() används.

* Vad är skillnaderna i implementation mellan mina cd, pwd och echo och linux cd, pwd och echo?

Den största skillnaden mellan min implementation och hur skal fungerar i linux generellt är att nästan alla kommandon i linux är separata program. I exemplet är pwd och echo sina egna binärer som exekveras av skalet. I min kommandotolk är alla dessa kommandon implementerade internt med hjälp av diverse C-APIer.

En annan skillnad mellan mina implementationer och coreutils-implementationerna är att de är mycket mer avancerade och har många fler funktioner än vad mina implementationer har.

* Vad skulle krävas för att stödja scriptfiler i min kommandotolk?

För att stödja exekvering från skriptfiler i min kommandotolk skulle det inte krävas jättemycket mer kod. I sin enklaste form behövs det en funktion för att läsa rader av kod från en specifierad fil. Dessa rader behöver sedan tolkas och kommandon kan sedan sekvensiellt exekveras. För att öka användbarheten av dessa skriptfiler skulle dock andra funktioner också behöva implementeras, såsom if-satser, loopar, och pipes.

* Vad innebär det att tolka ett kommando? Vad är skillnaden på hur min kommandotolk tolkar inmatade kommandon och hur en C-kompilator gör det?

Att tolka ett kommando innebär att från en sträng lista ut vilka handlingar en användare vill göra på datorn. Skillnaden mellan hur min kommandotolk tolkar kommandon och hur en C-kompilator tolkar kod är väldigt stor. 

Min kommandotolk är väldigt enkel och fyrkantig. Allt den stöjder är att upptäcka specifika nyckelord som kommandon, för att därefter lista ut argumenten till dessa kommandon. 

En C-kompilator är mycket mer avancerad. Den innehåller fler delar, t.ex. en lexer, en parser och en code generator som arbetar efter varandra. En kompilator måste kunna evaluera satser, beräkningar osv. vilket min kommandotolk inte behöver göra.

* Vad är ett systemanrop? Använder min kommandotolk något systemanrop?

Ett systemanrop är en funktion som pratar direkt med operativsystemets kärna. Till exempel, Allting som håller på med filer i linux använder sig av systemanrop som read() och write(). Min kommandotolk använder sig inte av några systemanrop direkt, men den använder sig av funktioner som själva använder systemanrop, som fgets().
