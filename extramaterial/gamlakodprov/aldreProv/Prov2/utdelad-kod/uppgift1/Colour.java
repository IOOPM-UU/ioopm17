package graph;
/**
 * @author Tobias Wrigstad (tobias.wrigstad@it.uu.se)
 * @date 2013-11-20
 */
public class Colour implements DeepCloneable<Colour> {
    private int RED;   /** A value between 0 .. 255 */
    private int GREEN; /** A value between 0 .. 255 */
    private int BLUE;  /** A value between 0 .. 255 */
    public Colour(final int r, final int g, final int b) {
	assert(0 <= r && r <= 255);
	assert(0 <= g && g <= 255);
	assert(0 <= b && b <= 255);
	RED = r; 
	GREEN = g; 
	BLUE = b;
    }

    public Colour deepClone(DeepCloneHelper h) {
	return null;
    }

    public Colour deepClone() {
	return deepClone(new DeepCloneHelper());
    }
}
