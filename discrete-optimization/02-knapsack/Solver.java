import java.io.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;

class Item {
    int index;
    int value;
    int weight;
    int pick;

    public Item(int index, int value, int weight, int pick) {
        this.index = index;
        this.value = value;
        this.weight = weight;
        this.pick = pick;
    }

    public void updatePick(int newPick) {
        this.pick = newPick;
    }
}

/**
 * The class <code>Solver</code> is an implementation of a greedy algorithm to solve the knapsack problem.
 *
 */
public class Solver {

    /**
     * The main class
     */
    public static void main(String[] args) {
        try {
            solve(args);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Read the instance, solve it, and print the solution in the standard output
     */
    public static void solve(String[] args) throws IOException {
        String fileName = null;

        // get the temp file name
        for(String arg : args){
            if(arg.startsWith("-file=")){
                fileName = arg.substring(6);
            }
        }
        if(fileName == null)
            return;

        // read the lines out of the file
        List<String> lines = new ArrayList<String>();

        BufferedReader input =  new BufferedReader(new FileReader(fileName));
        try {
            String line = null;
            while (( line = input.readLine()) != null){
                lines.add(line);
            }
        }
        finally {
            input.close();
        }
        // parse the data in the file
        String[] firstLine = lines.get(0).split("\\s+");
        int items = Integer.parseInt(firstLine[0]);
        int capacity = Integer.parseInt(firstLine[1]);

        int[] values = new int[items];
        int[] weights = new int[items];

        for(int i=1; i < items+1; i++){
          String line = lines.get(i);
          String[] parts = line.split("\\s+");

          values[i-1] = Integer.parseInt(parts[0]);
          weights[i-1] = Integer.parseInt(parts[1]);
        }

        // a trivial greedy algorithm for filling the knapsack
        // it takes items in-order until the knapsack is full
        int value = 0;
        int weight = 0;
        int[] taken = new int[items];



        // for (int i = 1; i <= item_count; i++) {
        //     String line = lines[i];
        //     String[] parts = line.split(" ");
        //     items.add(new Item(i - 1, Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), 0));
        //     max_estimate += Integer.parseInt(parts[0]);
        // }

        // items.sort(Comparator.comparingDouble(item -> (double) item.value / item.weight).reversed());
        // for(int i=0; i < items; i++){
        //     if(weight + weights[i] <= capacity){
        //         taken[i] = 1;
        //         value += values[i];
        //         weight += weights[i];
        //     } else {
        //         taken[i] = 0;
        //     }
        // }

        // prepare the solution in the specified output format
        System.out.println(value+" 0");
        for(int i=0; i < items; i++){
            System.out.print(taken[i]+" ");
        }
        System.out.println("");
    }

    private static void go(List<Integer> path, int value, int room, int estimate, List<Item> items, int[] result) {
        int max_value = 0;
        List<Object[]> stack = new ArrayList<>();
        stack.add(new Object[]{path, value, room, estimate});

        while (!stack.isEmpty()) {
            Object[] current = stack.remove(stack.size() - 1);
            List<Integer> currentPath = (List<Integer>) current[0];
            int currentValue = (int) current[1];
            int currentRoom = (int) current[2];
            int currentEstimate = (int) current[3];

            if (currentPath.size() == items.size()) {
                if (currentValue > max_value) {
                    max_value = currentValue;
                    result[0] = currentValue;
                    result[1] = currentPath.get(currentPath.size() - 1);
                }
                continue;
            }

            Item item = items.get(currentPath.size());

            int estimateAll = estimate;

            if (currentRoom - item.weight >= 0) {
                List<Integer> newPath = new ArrayList<>(currentPath);
                newPath.add(1);
                stack.add(new Object[]{newPath, currentValue + item.value, currentRoom - item.weight, estimate});
            }

            if (item.pick == 1) {
                estimateAll -= item.value;
            }

            if (estimateAll >= result[0]) {
                List<Integer> newPath = new ArrayList<>(currentPath);
                newPath.add(0);
                stack.add(new Object[]{newPath, currentValue, currentRoom, estimateAll});
            }
        }
    }

    private static int[] sortPathByItemIndex(int[] path, List<Item> items) {
        int[] sortedPath = new int[path.length];
        int index = 0;
        for (int itemIndex : path) {
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).index == itemIndex) {
                    sortedPath[index++] = itemIndex;
                    break;
                }
            }
        }
        return sortedPath;
    }

}