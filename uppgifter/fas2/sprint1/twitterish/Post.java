import java.io.Serializable;

public class Post implements Serializable {
    private int globalPostId;
    private Account poster;
    private String content;

    public Account getPoster() {
        return this.poster;
    }

    public Post(int globalPostId, Account poster, String content) {
        this.globalPostId = globalPostId;
        this.poster       = poster;
        this.content      = content;
    }

    public String render() {
        return "{" + this.poster.getName() + "} says:\n" + this.content + "\n";
    }
}
