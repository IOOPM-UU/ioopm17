public class CommonCompilerErrors {
    // Denna kodfil visar exempel på fem vanliga kompileringsfel:
    //
    // 1. Tilldelning från värde av felaktig typ
    // 2. Anrop av metod med parameter-värde av felaktig typ
    // 3. Användning av en klass som antingen är felstavad eller inte har importerats
    // 4. Användning av variabel som inte finns (i regel stavfel)
    // 5. Anrop till metod som inte finns (i regel stavfel eller fel mottagartyp, inklusive fel parameterantal)
    // 
    // Du kan inte köra detta program. Det är till för att kompileras. LÄS SLUTET AV FILEN FÖR MER INFORMATION.
}

class ErrorOne {
    Object source = "Jag är en sträng, men f skulle kunna peka ut vad som helst!";
    String sink = source; // Ger kompileringsfel av typ 1 ovan

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:15: error: incompatible types: Object cannot be converted to String
    String sink = source; // Ger kompileringsfel av typ 1 ovan
    ********************************************************************************/
    
    // Förklaring: 
    // Source har en mer generell typ än sink, dvs. source skulle kunna tilldelas ett
    // värde som inte är en sträng. För att undvika att programmet någonsin kraschar
    // på grund av detta tillåter vi inte tilldelning från source till sink. 
    //
    // Generell regel för tilldelning:
    // Låt T1 vara typen på source, 
    // Låt T2 vara typen på sink
    // för att sink = source skall vara tillåtet måste T1 <: T2 hålla, dvs. 
    // T1 måste vara en *subtyp* av T2. 
    //
    // Innan vi går in på interface betyder detta att något av följande skall gälla:
    // - T1 == T2 (typerna är samma)
    // - T1 ärver av T2 i något led 
    // 
}

class ErrorTwo {
    void methodTakingTwoArguments(Object p1, String p2) { /* do nothing for now */ }
    
    void hereIsWhereTheErrorIs() {
	Object a1 = null;
	String a2 = null; 

	this.methodTakingTwoArguments(a2, a1);

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:48: error: incompatible types: Object cannot be converted to String
	this.methodTakingTwoArguments(a2, a1);
    ********************************************************************************/

    }

    // Förklaring: 
    // Ovan uppstår problemet förmodligen på grund av att a1 och a2 står i omvänd ordning.
    // Att anropa methodTakingTwoArguments och skicka in a1 som argument till parametern
    // p2 är fel av exakt samma problem som i ErrorOne, dvs. p2 = a1 fungerar inte. 
}

class ErrorThree {
    LinkedList myList; 

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:66: error: cannot find symbol
    LinkedList myList;
    ^
  symbol:   class LinkedList
  location: class ErrorThree
    ********************************************************************************/

    // Förklaring: 
    // För att få tillgång till typen LinkedList måste vi importera den. Det kan vi göra
    // på två sätt: 
    //
    // import java.util.LinkedList; 
    // import java.util.*; 
    // 
    // Båda satserna bör stå högst upp i filen där vi vill använda klassen. 
    //
    // Det fösta importerar endast LinkedList-klassen från paketet java.util. Det andra
    // importerar alla klasser från java.util. 

    Error3 foo = null;

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:90: error: cannot find symbol
    Error3 foo = null;
    ^
  symbol:   class Error3
  location: class ErrorThree
    ********************************************************************************/

    // Förklaring: 
    // Klassens namn är felstavat. ErrorThree, inte Error3. 
}

class ErrorFour {
    void methodTakingTwoArguments(Object p1, String p2) { /* do nothing for now */ }
    
    void hereIsWhereTheErrorIs() {
	Object descriptiveVariableName = null;
	String anotherDescriptiveVariableName = null; 

	this.methodTakingTwoArguments(descriptiveVariableName, anohterDescriptiveVariableName);

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:113: error: cannot find symbol
	this.methodTakingTwoArguments(descriptiveVariableName, anohterDescriptiveVariableName);

	                                                       ^
  symbol:   variable anohterDescriptiveVariableName
  location: class ErrorFour
    ********************************************************************************/

    }

    // Förklaring: 
    // Vi har stavat fel till det andra argumentet ('h' och 't' har bytt plats).
}

class ErrorFive {
    void methodTakingTwoArguments(Object p1, String p2) { /* do nothing for now */ }
    
    void hereIsWhereTheErrorIs() {
	Object a1 = null;
	String a2 = null; 

	// Fel 1:
	this.methodTakingOneArguments(a1);

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:140: error: cannot find symbol
	this.methodTakingOneArguments(a1);
	    ^
  symbol: method methodTakingOneArguments(Object)
    ********************************************************************************/


	// Fel 2:
	this.methodTakingTwoArguments(a1);

    /*******************************************************************************
Kompilatorn säger:

CommonCompilerErrors.java:153: error: method methodTakingTwoArguments in class ErrorFive cannot be applied to given types;
	this.methodTakingTwoArguments(a1);
	    ^
  required: Object,String
  found: Object
  reason: actual and formal argument lists differ in length
    ********************************************************************************/

    }

    // Förklaring fel 1: 
    // Metodens namn är felstavat. Det finns ingen sådan metod. 

    // Förklaring fel 2:
    // Metoden förväntar sig två argument men får endast ett. 
}

    /*******************************************************************************
Låt oss dissekera kompilatorns felmeddelanden:

Först information om var felet är:

<Filnamn.Java>:<Radnummer>: error: <Beskrivning av felet>

        <information om var det uppstår>

   <övrig hjälpinformation om tillämpligt>

Titta igen på det sista felet som visar här. Om man läser det i lugn och ro får man 
faktiskt ut all information. 

CommonCompilerErrors.java:153: error: method methodTakingTwoArguments in class ErrorFive cannot be applied to given types;
	this.methodTakingTwoArguments(a1);
	    ^
  required: Object,String
  found: Object
  reason: actual and formal argument lists differ in length
    ********************************************************************************/
