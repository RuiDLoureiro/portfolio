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
    private static final int WINDOW_WIDTH = 500;  // Width of the window
    private static final int WINDOW_HEIGHT = 500;  // Height of the window
    private static final int SQUARE_SIZE = 50;  // Size of the square
    private static final int JUMP_DISTANCE = 50;  // Distance the square jumps
    private int squareX = (WINDOW_WIDTH - SQUARE_SIZE) / 2;  // X-coordinate of the square
    private int squareY = WINDOW_HEIGHT - SQUARE_SIZE;  // Y-coordinate of the square
    private Timer timer;  // Timer to control animation

    // Constructor
    public JumpingSquare() {
        // Set up the panel
        setPreferredSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
        setBackground(Color.WHITE);

        // Create the jump button
        JButton jumpButton = new JButton("Jump");
        jumpButton.addActionListener(this);

        // Add the jump button to the panel
        add(jumpButton);

        // Create the timer
        timer = new Timer(100, this);
    }

    // Paint the panel
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.RED);
        g.fillRect(squareX, squareY, SQUARE_SIZE, SQUARE_SIZE);
    }

    // Handle button and timer events
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            // Button event: jump the square
            squareY -= JUMP_DISTANCE;
            repaint();
        } else if (e.getSource() instanceof Timer) {
            // Timer event: move the square down
            squareY += JUMP_DISTANCE;
            repaint();
        }

        // Check if the square has landed
        if (squareY >= WINDOW_HEIGHT - SQUARE_SIZE) {
            // Stop the timer
            timer.stop();
        }
    }

    // Main method to create and show the window
    public static void main(String[] args) {
        JFrame frame = new JFrame("Jumping Square");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new JumpingSquare());
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    // Start the animation
    public void startAnimation() {
        timer.start();
    }
}
