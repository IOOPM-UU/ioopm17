/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-27
 */
public class Driver {
    public static void main(String[] args) {
	mm.MemoryManager mm = new mm.MemoryManager(1024,0); 
	mm.allocate(128);
	mm.allocate(128);
    }
}
