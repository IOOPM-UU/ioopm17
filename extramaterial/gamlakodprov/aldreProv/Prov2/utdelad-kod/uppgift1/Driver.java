package graph;

/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-21
 */
public class Driver {
    public static void main(String[] args) {
        Node n1 = new Node(1);
	Node n2 = new Node(2);
	Node n3 = new Node(3);
	Node n4 = new Node(4);
	Edge e1 = new Edge(n1,n2);
	Edge e2 = new Edge(n2,n3);
	Edge e3 = new Edge(n3,n4);
	Edge e4 = new Edge(n4,n1);
        Graph g = new Graph(n1);

	// Här kan du t.ex. skriva testkod
    }
}
