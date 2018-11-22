
import java.util.Deque;
import java.util.LinkedList;


public class WallsAndGates {
    private static final int d[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    private static final int INF = Integer.MAX_VALUE;

    public void wallsAndGates(int[][] rooms) {
        Deque<Cell> queue = new LinkedList<>();
        gates(rooms, queue);

        while (!queue.isEmpty()) {
            Cell cell = queue.pollLast();
            addNeighbors(rooms, cell.row, cell.col, queue);
        }

    }

    private  void addNeighbors(int[][] rooms, int row, int col, Deque<Cell> queue) {
        for (int[] d1 : d) {
            int r1 = row + d1[0];
            int c1 = col + d1[1];
            if (r1 < 0 || c1 < 0 || r1 >= rooms.length || c1 >= rooms[0].length || rooms[r1][c1] != INF) {
                continue;
            }
            rooms[r1][c1] = 1 + rooms[row][col];
            queue.offerFirst(new Cell(r1, c1));
        }
    }

    private void gates(int[][] rooms, Deque<Cell> queue) {
        for (int i = 0; i < rooms.length; i++) {
            for (int j = 0; j < rooms[0].length; j++) {
                if (rooms[i][j] == 0) {
                    queue.offerFirst(new Cell(i, j));
                }
            }
        }
    }

    class Cell {
        int row;
        int col;

        Cell(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }
}