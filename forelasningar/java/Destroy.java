import java.util.*;

public class Destroy {
    public static void main(String[] args) {
        List<Integer> list = new LinkedList<Integer>();

        while (true) {
            try {
                list.add(42);
            } catch (OutOfMemoryError e) {
                System.err.println("Minnet fullt!");
                while (list.size() > 0) {
                    list.remove(0);
                }
                /// Ingen garanti att GC körs!
                System.gc();
            }
        }
    }
}
