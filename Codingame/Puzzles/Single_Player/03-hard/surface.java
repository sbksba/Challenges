import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

    /** width, height of the map and the map*/
    static private int width;
    static private int height;
    static private char[][] map;

    /** Class representing a couple of cartesian coordinates*/
    static class Coords {
        int X, Y;

        public Coords(int X, int Y){
            this.X = X;
            this.Y = Y;
        }

        /** returns an array containing the 4 adjacent coordinates to this */
        public Coords[] neighbours() {
            Coords res[] = {new Coords(X, Y-1), new Coords(X+1, Y), new Coords(X, Y+1), new Coords(X-1, Y)};
            return res;
        }

        /** returns true if and only if the coordinates are in the boundaries of the map*/
        public boolean isInMap() {
            return 0 <= X && X < width && 0 <= Y && Y < height;
        }
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        // Reads the map
        width = in.nextInt();
        height = in.nextInt();
        in.nextLine();
        map = new char[height][width];
        for (int y = 0; y < height; y++)
            map[y] = in.nextLine().toCharArray();

        int N = in.nextInt();
        for (int i = 0; i < N; i++) {
            int X = in.nextInt();
            int Y = in.nextInt();

            // copies the map
            char[][] copy = new char[height][width];
            for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                    copy[y][x] = map[y][x];

            // floods the map starting from (X,Y),
            // counting the number of cells flooded, which is the area of the lake
            LinkedList<Coords> queue = new LinkedList<Coords>();
            int count = 0;
            if (copy[Y][X] == 'O') {
                copy[Y][X] = '#';
                count++;
                queue.add(new Coords(X, Y));
            }

            while (queue.size() > 0) {
                Coords c = queue.remove();
                for (Coords neighbour : c.neighbours()) {
                    if (neighbour.isInMap() && copy[neighbour.Y][neighbour.X] == 'O') {
                        copy[neighbour.Y][neighbour.X] = '#';
                        count++;
                        queue.add(neighbour);
                    }
                }
            }
            System.out.println(count);
        }
    }
}
