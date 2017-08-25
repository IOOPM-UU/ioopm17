package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-20
 */
import java.util.Set;
import java.util.HashSet;

public class ColouredNode extends Node {
    private Colour colour; 
    public Set<Edge> connections = new HashSet<Edge>(); 

    public ColouredNode(int value, Colour colour) {
	this(null, value, colour);
    }

    public ColouredNode(Set<Edge> connections, int value, Colour colour) {
	super(connections, value);
	this.colour = colour;
    }

    public Node deepClone(DeepCloneHelper h) {
	return null;
    }
}
