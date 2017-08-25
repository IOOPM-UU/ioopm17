/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-06
 */
public class Driver {
    public static void populate(java.util.List<Object> list) {
        list.add(new Person(new String("A"), 1, new String("e")));
        list.add(new Person(new String("B"), 2, new String("f")));
        list.add(new Person(new String("C"), 3, new String("g")));
    }

    public static void main(String[] args) {
        java.util.List<Object> list1 = new java.util.LinkedList<Object>();
        java.util.List<Object> list2 = new java.util.ArrayList<Object>();

        populate(list1);
        populate(list2);

        System.out.println("Test 1: " + list1.equals(list2));

        java.util.List<Object> list3 = new java.util.ArrayList<Object>();
        list3.add(null);
        System.out.println("Test 2: " + list1.equals(list3));

        java.util.List<Object> list4 = new java.util.ArrayList<Object>();
        list4.add(new Person(null, 0, null));
	System.out.println("Test 3: " + list1.equals(list4));

        java.util.List<Object> list5 = new java.util.ArrayList<Object>();
        list5.add("adflkja dflkajd falkj afdlkajfaf adfj alkdjf aldfj adlfkja ");
	System.out.println("Test 4: " + list1.equals(list5));
    }
}
