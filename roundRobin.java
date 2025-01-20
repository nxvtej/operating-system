package os;

import java.util.ArrayList;
import java.util.Scanner;

class Solution {
    int process;
    int[] bTime;
    ArrayList<Integer> order;
    int totalTime = 0;

    public void schedule() {
        int[] rTime = bTime;
        order = new ArrayList<>();

        while (true) {
            boolean done = true;
            for (int i = 0; i < process; i++) {
                if (rTime[i] > 0) {
                    totalTime++;
                    order.add(i + 1);
                    rTime[i]--;
                    done = false;
                } else {
                    continue;
                }
            }

            if (done == true) {
                break;
            }
        }

        System.out.println("Total time taken is: " + totalTime);
        System.out.print("Below is the order of execution : ");
        for (int process : order) {
            System.out.print(process + " ");
        }
    }

    public void start() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of process : ");
        process = sc.nextInt();

        bTime = new int[process];
        System.out.print("Enter each process burst time : ");
        for (int i = 0; i < process; i++) {
            bTime[i] = sc.nextInt();
        }

        System.out.print("Bust time are : ");
        for (int time : bTime) {
            System.out.print(time + " ");
        }
        System.out.println();

        System.out.println("scheduling...");
        schedule();

        sc.close();
    }
}

public class roundRobin {

    public static void main(String[] args) {
        Solution sol = new Solution();

        sol.start();

    }
}