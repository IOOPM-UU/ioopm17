package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-20
 */
public class Edge implements DeepCloneable<Edge> {
    private Node end;
    private Node otherEnd;

    public Edge(Node end, Node otherEnd) {
	end.connect(this);
	otherEnd.connect(this);
    }

    public Edge deepClone(DeepCloneHelper h) {
	return null;
    }

    public Edge deepClone() {
	return deepClone(new DeepCloneHelper());
    }
}
