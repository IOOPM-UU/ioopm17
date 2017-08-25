package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-20
 */
public class Graph implements DeepCloneable<Graph> {
    private Node startNode;

    public Graph(Node n) { this.startNode = n; }

    public Graph deepClone(DeepCloneHelper h) {
	return null;
    }

    public Graph deepClone() {
	return deepClone(new DeepCloneHelper());
    }
}
