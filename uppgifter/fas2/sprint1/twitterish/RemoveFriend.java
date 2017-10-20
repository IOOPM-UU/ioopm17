import java.io.Serializable;

public class RemoveFriend implements Serializable {
    private Account friendToBeRemoved;

    public RemoveFriend(Account friendToBeRemoved) {
        this.friendToBeRemoved = friendToBeRemoved;
    }

    public Account getFriend() {
        return this.friendToBeRemoved;
    }
}
