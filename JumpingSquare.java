import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

public class JumpingSquare extends JPanel implements ActionListener {
    private static final int WINDOW_WIDTH = 500;  
    private static final int WINDOW_HEIGHT = 500;  
    private static final int SQUARE_SIZE = 50;  
    private static final int JUMP_DISTANCE = 50; 
    private int squareX = (WINDOW_WIDTH - SQUARE_SIZE) / 2; 
    private int squareY = WINDOW_HEIGHT - SQUARE_SIZE;  
    private Timer timer; 

    public JumpingSquare() {
      
        setPreferredSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
        setBackground(Color.WHITE);

        JButton jumpButton = new JButton("Jump");
        jumpButton.addActionListener(this);

        add(jumpButton);

        timer = new Timer(100, this);
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.RED);
        g.fillRect(squareX, squareY, SQUARE_SIZE, SQUARE_SIZE);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            squareY -= JUMP_DISTANCE;
            repaint();
        } else if (e.getSource() instanceof Timer) {
            squareY += JUMP_DISTANCE;
            repaint();
        }

        if (squareY >= WINDOW_HEIGHT - SQUARE_SIZE) {
            // Stop the timer
            timer.stop();
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Jumping Square");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new JumpingSquare());
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    public void startAnimation() {
        timer.start();
    }
}
