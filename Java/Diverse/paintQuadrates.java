

package paintQuadrates;
import java.awt.*;
import javax.swing.*;

public class paintQuadrates extends JPanel {	
	
	private static final long serialVersionUID = 1L;

	public void paint(Graphics g) {
		// Dimension - encapsulates w and h of a component in a single object
		Dimension dim = this.getSize();
		drawSquare(g, dim.width / 2, dim.height / 2, Math.min(dim.width / 2, dim.height / 2));
	}
	
	private void drawSquare(Graphics g, int x, int y, int l) {
		if(l > 10) {
			drawSquare(g, x - l / 2, y - l / 2, l / 2);
			drawSquare(g, x - l / 2, y + l / 2, l / 2);
			drawSquare(g, x + l / 2, y - l / 2, l / 2);
			drawSquare(g, x + l / 2, y + l / 2, l / 2);
			g.drawRect(x - l / 2, y - l / 2, l, l);
		}
	}
    
	public static void main(String[] args) {
		JFrame frame = new JFrame("Recursion is fun !");
		paintQuadrates quadratePanel =  new paintQuadrates();
		// Content Pane - the layer which holds the objects
		frame.getContentPane().add(quadratePanel); 
		quadratePanel.setPreferredSize(new Dimension(400,400));
		// Cause the window to be sized
		frame.pack();
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		Dimension screenDim = Toolkit.getDefaultToolkit().getScreenSize();
		Dimension frameDim = frame.getSize();
		frame.setLocation((screenDim.width - frameDim.width) / 2, (screenDim.height - frameDim.height) / 2);
		frame.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		frame.setVisible(true);
		
		// Prevent from shriking or growing
		// frame.setResizable(false);
	}
}

