package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-20
 */
import java.util.Set;
import java.util.HashSet;

public class Node implements DeepCloneable<Node> {
    private int value; 
    public Set<Edge> connections = new HashSet<Edge>(); 

    public Node(int value) {
	this(null, value);
    }

    public Node(Set<Edge> connections, int value) {
	this.connections.addAll(connections);
	this.value = value;
    }

    public void connect(Node other) {
	connect(new Edge(this,other));
    }

    public void connect(Edge edge) {
	connections.add(edge);
    }

    public Node deepClone(DeepCloneHelper h) {
	return null;
    }

    public Node deepClone() {
	return deepClone(new DeepCloneHelper());
    }
}
