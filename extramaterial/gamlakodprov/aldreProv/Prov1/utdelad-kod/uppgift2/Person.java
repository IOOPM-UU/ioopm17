/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-06
 */
public class Person {
    private String name;
    private int age; 
    // Inte vettigt att representera med en sträng, men gör programmet mindre
    private String pnr; 

    public Person(final String name, final int age, final String pnr) {
	this.name = name; 
	this.age  = age;
	this.pnr  = pnr;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public String getPersonnummer() { return new String(pnr); }

    public String toString() {
	return "Person(" + name + "," + age + "," + pnr + ")";
    }

    public boolean equals(Object obj) {
	System.out.println(this + " eq " + obj);
	if (obj instanceof Person) {
	    Person other = (Person) obj;
	    return this.age == other.age &&
		(name == null ? other.name == null : name.equals(other.name)) &&
		(pnr  == null ? other.pnr  == null : pnr .equals(other.pnr));
	} else {
	    return false;
	}
    }
}

