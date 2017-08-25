package mm;

/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-27
 */
import java.util.*;

public class MemoryManager {
    List<Chunk> free      = new LinkedList<Chunk>();
    List<Chunk> allocated = new LinkedList<Chunk>();
    Set<Chunk>  rootset   = new HashSet<Chunk>();

    public MemoryManager(int initialSize, int startAddress) {
	free.add(new Chunk(initialSize, startAddress));
    }

    private Set<Chunk> getRootset() {
	return rootset;
    }

    public void addRoot(Chunk c) {
	rootset.add(c);
    }

    public void removeRoot(Chunk c) {
	rootset.remove(c);
    }

    private Chunk firstFreeBlock(int size) {
	Iterator<Chunk> i = free.iterator();
	while (i.hasNext()) {
	    Chunk c = i.next();
	    if (c.size() >= size) {
		i.remove();
		allocated.add(c);
		// Stupid simplification to keep the code small
		// Sorts all chunks in the allocated list in address-order
		Collections.sort(allocated);
		return c; 
	    }
	}
	throw new MemoryFullException();
    }

    public Chunk allocate(int size) {
	try {
	    return firstFreeBlock(size);
	} catch (MemoryFullException mfe) {
	    gc();
	    return firstFreeBlock(size);
	}
    }

    private void sweep() {
	// TODO
    }

    public void gc() {
	for (Chunk c : rootset) {
	    c.mark();
	}

	sweep();
    }


}
