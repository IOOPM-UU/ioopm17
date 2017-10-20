import java.io.Serializable;
import java.util.Set;
import java.util.List;

public class SyncResponse implements Serializable {
    private Set<Account> users;
    private List<Post> posts;

    public SyncResponse(Set<Account> users, List<Post> posts) {
        this.users = users;
        this.posts = posts;
    }

    public List<Post> getPosts() {
        return this.posts;
    }

    public Set<Account> getUsers() {
        return this.users;
    }
}
