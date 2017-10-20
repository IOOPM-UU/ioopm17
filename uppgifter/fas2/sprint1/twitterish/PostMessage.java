import java.io.Serializable;

public class PostMessage implements Serializable {
    private String msg;

    public PostMessage(String msg) {
        this.msg = msg;
    }

    public String getMsg() {
        return msg;
    }
}
