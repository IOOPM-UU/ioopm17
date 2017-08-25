/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-26
 */
import java.util.*;

public class Friend {
    String name;
    Friends friends;
    public Friend(String name, Friends friends) {
        this.name    = name;
        this.friends = friends;
    }

    void printNetwork() {
	printNetwork(0);
    }

    void printNetwork(int lvl) {
	...
    }
}
