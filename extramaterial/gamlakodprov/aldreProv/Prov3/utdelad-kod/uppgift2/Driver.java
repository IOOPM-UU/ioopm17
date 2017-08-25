/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-26
 */
public class Driver {
    public static String indent(int level) {
	StringBuilder sb = new StringBuilder();
	for (int i = 0; i < level; ++i) sb.append("\t");
	return sb.toString();
    }

    public static void main(String[] args) {
	Friends alicesFriends  = new Friends();
	Friends bobsFriends    = new Friends();
	Friends caesarsFriends = new Friends();
	Friend alice = new Friend("Alice", alicesFriends);
	Friend bob = new Friend("Bob", bobsFriends);
	Friend caesar = new Friend("Caesar", caesarsFriends);
	alicesFriends.add(bob);
	alicesFriends.add(caesar);
	bobsFriends.add(alice);
	bobsFriends.add(caesar);
	caesarsFriends.add(alice);
	caesarsFriends.add(bob);
	alice.printNetwork();
    }
}
