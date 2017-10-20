public class Login implements java.io.Serializable {
    private Account account;

    public Login(Account a) {
        this.account = a;
    }

    public Account getAccount() {
        return this.account;
    }
}
