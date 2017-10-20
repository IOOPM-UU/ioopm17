import java.io.Serializable;

public class AddFriend implements Serializable {
    private Account friendToBeAdded;

    public AddFriend(Account friendToBeAdded) {
        this.friendToBeAdded = friendToBeAdded;
    }

    public Account getFriend() {
        return this.friendToBeAdded;
    }
}
