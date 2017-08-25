package mm;

/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-27
 */
import java.util.Set;
import java.util.HashSet;
public class Chunk implements Comparable<Chunk> {
    private int size; 
    private boolean marked; 
    private Set<Chunk> pointers_in_chunk = new HashSet<Chunk>();
    private int start_address;

    public Chunk(int size, int start_address) {
	this.size = size;
	this.start_address = start_address;
    }

    public int compareTo(Chunk c) {
	return c.start_address - this.start_address;
    }

    public void addPointer(Chunk c) {
	pointers_in_chunk.add(c);
    }

    public void removePointer(Chunk c) {
	pointers_in_chunk.remove(c);
    }

    public int startAddress() {
	return start_address;
    }

    public int size() {
	return size;
    }

    public boolean garbage() {
	return !marked;
    }

    public void unmark() {
	marked = false;
    }

    public void mark() {
	// TODO
    }
}
