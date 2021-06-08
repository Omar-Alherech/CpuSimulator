import java.util.Scanner;
import java.util.regex.*;

/**
 * The CpuSimulator program implements an application that
 * simulates round robin scheduling using queues. It is a type of process
 * scheduling algorithm that is preemptive, meaning that each process can
 * be stopped to process another potentially higher priority process. In this case,
 * each process is given a set amount of time to execute, defined as a quantum.
 * Once this process is executed for the quantum's time period, it is paused and
 * another process is given time to compute.
 *
 * @author  Omar (Porapat) Alherech
 * @version 1.0
 */
public class CpuSimulator {
    private CpuCore[] cores;
    private Queue<Process> processQueue;
    private boolean cores_occupied;
    private int time_keeper;
    private int process_counter;

    /**
     * This method sets up the cores, and the process queue with
     * user-input information from previously gathered, the cores are then
     * intialized with the processqueue, and the cutoff value, the amount of
     * steps it will complete before dropping the process.
     * @param numCores The number of cores
     * @param cutoff  The number of steps a process will take in sucession
     * @param pq  The built processqueue derived from user input.
     */
    public CpuSimulator(int numCores, int cutoff, Queue<Process> pq) {
        //Initializing core array
        cores = new CpuCore[numCores];
        //Setting process_queue as a instance variable
        processQueue = pq;
        //Creating an instance variable detailing initial length
        process_counter = pq.length();
        //Loop to initialize all the cores
        for (int i=0;i<numCores;i++){
            cores[i] = new CpuCore(cutoff, processQueue);
        }
        // set up the cores, and process queue
        // cutoff indicates maximum number of steps working on the same process
        // consecutively
    }
    /**
     * This method sets the high level decision tree for the round robin
     * simulation
     */
    public void run() {
        // loop as long as there are still processes to finish (either in the queue or
        // on a core)
        // and do one step for each core in the cpu
        // For the loop to continue, the processqueue must not be empty,
        // In addition, at least core must be currently processing,
        //this allows other cores to idle waiting on the last core to finish work
        while(processQueue.isEmpty()==false || cores_occupied==true ){
            //If cores are occupied, the logic begins
            // time keeper is incremented to print out the finish time of every process
            // cores occupied are initialized to zero, as a for loop checks and updates
            // the boolean in order to decide if the while loop continues,
            if(cores_occupied=true){
                cores_occupied = false;
                time_keeper++;
                for(int i=0;i<cores.length;i++){
                    // Each core will get to make one decision per step, whether its
                    // picking up a process, dropping it or working on it.
                    cores[i].step(time_keeper);
                    //Logic updated for the exterior while loop
                    if(cores[i].getCurrent_process()!=null){
                        cores_occupied=true;
                    }
                }
            }
            else{
                //Double check
                if (processQueue.isEmpty()){
                    break;
                }
            }
        }
    }
    /**
     * This method was written in order to check if any of the
     * cores are occupied. It ended up being unused as the logic
     * was integrated in the main while loop
     */
    public boolean cores_occupied(){
        boolean occupied = false;
        for(int i=0;i<cores.length;i++){
            if(cores[i].getCurrent_process()!=null){
                occupied=true;
            }
        }
        return occupied;
    }
    /**
     * This method returns a boolean regarding if the queue is empty or not.
     */
    public boolean queue_isEmpty(){
        return (processQueue.length()==0);
    }

    public static void main(String[] args) {

        // read the parameters from the command line using Scanner
        Scanner sc = new Scanner(System.in);
        // first line = number of processes
        System.out.print("Number of processes: ");
        int no_process = Integer.parseInt(sc.nextLine());
        // second line = number of cores
        System.out.print("Number of cores: ");
        int no_core = Integer.parseInt(sc.nextLine());
        // third line = cutoff
        System.out.print("Cutoff: ");
        int cutoff = Integer.parseInt(sc.nextLine());
        // then one line per process in this format
        // <process id>,<process size>
        // Create the process objects, set up the queue, create an instance of
        // CpuSimulator for this queue with the appropriate arguments
        Queue<Process> pass_queue = new Queue<>();
        for(int i=0;i<no_process;i++){
            System.out.print(String.format("Process %d: ", i));
            String process_input = sc.nextLine();
            pass_queue.enqueue(new Process(process_input));
        }
        CpuSimulator sim = new CpuSimulator(no_core, cutoff, pass_queue);
            // call run on the simulator
        sim.run();
        System.out.println(String.format("Average Turnaround Time %f: ", sim.avgTurnaroundTime()));
        System.out.println(String.format("Average Cpu Utilization Time %f: ", sim.getUtilization()));
    }
    /**
     * This method returns a value that signifies how productive the cores were
     * when it comes to the simulation.
     */
    public double getUtilization(){
        return((double)CpuCore.productive/(cores.length*time_keeper));
    }
    /**
     * This method returns a value that signifies the average amount of time
     * each process took to finish.
     */
    public double avgTurnaroundTime(){
        return ((double)CpuCore.avg_turnaround/process_counter);
    }

}
