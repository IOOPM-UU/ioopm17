package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-21
 */
public interface DeepCloneable<T> {
    public T deepClone(DeepCloneHelper h);
    public T deepClone();
}
