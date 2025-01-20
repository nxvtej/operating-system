package os;

import java.util.ArrayList;
import java.util.Scanner;

class Simple {
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

// mine
class Advance {

    int process;
    int[] bTime;
    int slice;
    ArrayList<Integer> order;
    int totalTime = 0;
    int[] tTime;
    int[] wTime;
    int[] aTime;

    public void schedule() {
        int[] rTime = bTime;
        order = new ArrayList<>();
        tTime = new int[process];
        wTime = new int[process];
        aTime = new int[process];

        for (int i = 0; i < process; i++) {
            tTime[i] = -1;
            wTime[i] = -1;
            aTime[i] = 1;
        }

        while (true) {
            boolean done = true;
            for (int i = 0; i < process; i++) {
                if (aTime[i] == -1) {
                    aTime[i] = totalTime;
                }

                if (rTime[i] > 0) {
                    totalTime++;
                    order.add(i + 1);
                    if (rTime[i] > slice) {
                        rTime[i] = rTime[i] - slice;
                    } else {
                        tTime[i] = totalTime - aTime[i];
                        wTime[i] = tTime[i] - bTime[i];
                        rTime[i] = 0;
                    }

                    done = false;
                } else {
                    continue;
                }
            }

            if (done == true) {
                break;
            }
        }

        printResult();
    }

    public void printResult() {

        System.out.println("Total time consumed is : " + totalTime);
        System.out.println("Time Quantum used is : " + slice);

        System.out.print("Burst time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(bTime[i] + " ");
        }

        System.out.println();
        System.out.print("Arrival time is: ");

        for (int i = 0; i < process; i++) {
            System.out.print(aTime[i] + " ");
        }
        System.out.println();
        System.out.print("Turn Around time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(tTime[i] + " ");
        }
        System.out.println();
        System.out.print("Wait time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(wTime[i] + " ");
        }
        System.out.print("Order of execution is : ");
        for (int i = 0; i < order.size(); i++) {
            System.out.print(order.get(i));
        }
    }

    public void start() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of process : ");
        process = sc.nextInt();

        System.out.print("Enter time slice : ");
        slice = sc.nextInt();

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

// gpt
class GPT3Advance {
    int process;
    int[] bTime;
    int slice;
    ArrayList<Integer> order;
    int totalTime = 0;
    int[] tTime;
    int[] wTime;
    int[] aTime;

    public void schedule() {
        int[] rTime = bTime.clone();
        order = new ArrayList<>();
        tTime = new int[process];
        wTime = new int[process];
        aTime = new int[process];

        for (int i = 0; i < process; i++) {
            tTime[i] = 0;
            wTime[i] = 0;
        }

        while (true) {
            boolean done = true;
            for (int i = 0; i < process; i++) {
                if (rTime[i] > 0) {
                    done = false;
                    if (rTime[i] > slice) {
                        totalTime += slice;
                        rTime[i] -= slice;
                    } else {
                        totalTime += rTime[i];
                        tTime[i] = totalTime - aTime[i];
                        wTime[i] = tTime[i] - bTime[i];
                        rTime[i] = 0;
                    }
                    order.add(i + 1);
                }
            }
            if (done)

                break;
        }

        printResult();
    }

    public void printResult() {
        System.out.println("Total time consumed is: " + totalTime);
        System.out.println("Time Quantum used is: " + slice);

        System.out.print("Burst time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(bTime[i] + " ");
        }

        System.out.println();
        System.out.print("Arrival time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(aTime[i] + " ");
        }
        System.out.println();
        System.out.print("Turnaround time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(tTime[i] + " ");
        }
        System.out.println();
        System.out.print("Wait time is: ");
        for (int i = 0; i < process; i++) {
            System.out.print(wTime[i] + " ");
        }
        System.out.println();
        System.out.print("Order of execution is: ");
        for (int i = 0; i < order.size(); i++) {
            System.out.print(order.get(i) + " ");
        }
    }

    public void start() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        process = sc.nextInt();

        System.out.print("Enter time slice: ");
        slice = sc.nextInt();

        bTime = new int[process];
        aTime = new int[process];

        System.out.print("Enter each process burst time: ");
        for (int i = 0; i < process; i++) {
            bTime[i] = sc.nextInt();
        }

        System.out.print("Enter arrival times: ");
        for (int i = 0; i < process; i++) {
            aTime[i] = sc.nextInt();
        }

        System.out.println("Scheduling...");
        schedule();

        sc.close();
    }
}

public class roundRobin {

    public static void main(String[] args) {
        // Simple simple = new Simple();
        // simple.start();

        GPT3Advance adv = new GPT3Advance();
        adv.start();

    }
}