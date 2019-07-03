import java.util.*;

/**
 * A class for checking the existence of the vertical line of symmetry for a set of integral points.
 */
public class SymmetryChecker {
    public static class Point {
        final long x;
        final long y;

        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void checkFromConsole() {
        Scanner scanner = new Scanner(System.in);
        int pointsNum = scanner.nextInt();
        Point[] points = new Point[pointsNum];
        for (int i = 0; i < pointsNum; i++) {
            long x = scanner.nextInt();
            long y = scanner.nextInt();
            points[i] = new Point(x, y);
        }
        System.out.println(symmetryExists(points));
    }

    public static boolean symmetryExists(Point[] points) {
        HashMap<Long, HashMap<Long,Integer>> layers = new HashMap<>();
        // for each existing y coord store the list of x coords
        for (Point p : points) {
            layers.putIfAbsent(p.y, new HashMap<>());
            HashMap<Long, Integer> curLayer = layers.get(p.y);
            // multiply by two being able not to use doubles
            curLayer.compute(p.x * 2, (coord, cnt) -> cnt == null ? 1 : cnt + 1);
        }
        long possibleMid = Long.MIN_VALUE;
        for (Map.Entry<Long, HashMap<Long, Integer>> entry : layers.entrySet()) {
            HashMap<Long, Integer> layerPoints = entry.getValue();
            if (possibleMid == Long.MIN_VALUE) {
                // compute the only possible x coordinate on the first visited level
                long minValue = Long.MAX_VALUE, maxValue = Long.MIN_VALUE;
                for (long xCoord : layerPoints.keySet()) {
                    minValue = Math.min(minValue, xCoord);
                    maxValue = Math.max(maxValue, xCoord);
                }
                possibleMid = (minValue + maxValue) / 2;
            }
            // check level to match the candidate
            for (Map.Entry<Long, Integer> point : layerPoints.entrySet()) {
                long oppositeX = 2 * possibleMid - point.getKey();
                if (!point.getValue().equals(layerPoints.get(oppositeX))) {
                    return false;
                }
            }
        }
        return true;
    }
}
