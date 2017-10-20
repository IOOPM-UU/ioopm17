public class Logout implements java.io.Serializable {
    private Account account;

    public Logout(Account a) {
        this.account = a;
    }

    public Account getAccount() {
        return this.account;
    }
}
