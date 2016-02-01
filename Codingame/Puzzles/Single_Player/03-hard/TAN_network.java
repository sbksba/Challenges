import java.util.*;
import java.io.*;
import java.math.*;

/** This class represents a TAN stop. It is characterized by :
 * <ul>
 * <li>A unique constant identifier</li>
 * <li>Its full name</li>
 * <li>A latitude and a longitude giving his position</li>
 * <li>The list of stops accessible from this stop</li>
 * <li>A unique number, which can be used as an identifier too</li>
 * </ul>
 */
class Stop {
    private String id;
    private String name;
    private double latitude;
    private double longitude;
    private ArrayList<Stop> accessibleStops;
    private int number;

    /** Initializes a new stop with informations given by the inputLine*/
    public Stop(String inputLine, int nb) {
        String fields[] = inputLine.split(",", -1);
        id = fields[0];
        name = fields[1].substring(1, fields[1].length()-1);
        latitude = Math.toRadians(new Double(fields[3]));
        longitude = Math.toRadians(new Double(fields[4]));
        accessibleStops = new ArrayList<Stop>();
        number = nb;
    }

    /** Only setter, adding an accessible stop the list*/
    public void addAccessibleStop(Stop s) {
        accessibleStops.add(s);
    }

    // Getters
    public String id() {
        return id;
    }

    public String name() {
        return name;
    }

    public double lat() {
        return latitude;
    }

    public double lon() {
        return longitude;
    }

    public ArrayList<Stop> accessibleStops() {
        return accessibleStops;
    }

    public int nb() {
        return number;
    }
}

class Solution {

    /** Looks for a stop of id 'id' in 'stops' and returns it.
     * if it can't be found, return null
     */
    static private Stop getStop(String id) {
        for (Stop s : stops)
            if (s.id().equals(id))
                return s;
        return null;
    }


    /** Returns the distance between stop A and stop B*/
    private static double distance(Stop A, Stop B) {
        double x = (B.lon()-A.lon())*Math.cos((A.lat()+A.lat())/2);
        double y = B.lat() - A.lat();
        return Math.sqrt(Math.pow(x,2) + Math.pow(y,2)) * 6371;
    }

    /** Returns one of the shortest Path from stop 'from' to stop 'to'
     * or null if there is no path.
     */
    private static Stack<Stop> shortestPath(Stop from, Stop to) {
        // arrays of predecessors, and distance from 'from'
        Stop pred[] = new Stop[stops.length];
        double dist[] = new double[stops.length];
        for (int i = 0; i < stops.length; i++) {
            pred[i] = null;
            dist[i] = Double.MAX_VALUE;
        }
        dist[from.nb()] = 0.0;
        pred[from.nb()] = from;

        ArrayList<Stop> notExplored = new ArrayList(Arrays.asList(stops));

        while (notExplored.size() > 0) {
            // amongst the non explored stops, find the one with smallest dist
            Stop chosen = null;
            double min = Double.MAX_VALUE;
            for (Stop s : notExplored)
                if (dist[s.nb()] < min) {
                    min = dist[s.nb()];
                    chosen = s;
                }

            // if chosen stays null, then remaining stops are not accessible
            // from 'from
            if (chosen == null)
                notExplored.clear();
            else {
                // update distance of neighbours of the chosen stop
                notExplored.remove(chosen);
                for (Stop neighbour : chosen.accessibleStops()) {
                    double d = distance(chosen, neighbour);
                    if (dist[neighbour.nb()] > dist[chosen.nb()] + d) {
                        dist[neighbour.nb()] = dist[chosen.nb()] + d;
                        pred[neighbour.nb()] = chosen;
                    }
                }
            }
        }

        // if the predecessor of 'to' is still null, then 'to' is not
        // accessible from 'from
        if (pred[to.nb()] == null)
            return null;
        else {
            // retraces path by reading pred, and returns it
            Stack<Stop> path = new Stack<Stop>();
            Stop iter = to;
            while (iter != from) {
                path.push(iter);
                iter = pred[iter.nb()];
            }
            path.push(from);
            return path;
        }
    }

    /** array containing all the stops of the network*/
    private static Stop stops[];


    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        String startPoint = in.nextLine();
        String endPoint = in.nextLine();

        int nbStops = in.nextInt();
        in.nextLine();
        stops = new Stop[nbStops];
        for (int i = 0; i < nbStops; i++)
            stops[i] = new Stop(in.nextLine(), i);

        int nbRoutes = in.nextInt();
        in.nextLine();
        for (int i = 0; i < nbRoutes; i++) {
            String route[] = in.nextLine().split(" ");
            getStop(route[0]).addAccessibleStop(getStop(route[1]));
        }

        // computes shortest path, if it exists prints it, else prints IMPOSSIBLE
        Stack<Stop> path = shortestPath(getStop(startPoint), getStop(endPoint));
        if (path == null)
            System.out.println("IMPOSSIBLE");
        else
            while (!path.empty())
                System.out.println(path.pop().name());
    }
}
