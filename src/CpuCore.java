/**
 * The CpuCore class serves to be used by CpuSimulator in order
 * to simulate the work done on a process. Each core is allowed to
 * work on a process for a certain user defined number of times. Each
 * step defines a decision tree that decides what the process is to do,
 * whether it drops a process, works on a process, or picks up a process.
 *
 * @author  Omar (Porapat) Alherech
 * @version 1.0
 */

public class CpuCore {

    // instance variables...
    public static int core_counter;
    private static int time_counter;
    public static int avg_turnaround;
    public static int productive;
    private int step_counter;
    private int cutoff;
    private int core_id;
    private boolean put_back;
    private boolean out_of_processes;
    private Process current_process;
    Queue<Process> hold_pq;
    /**
     * This method sets up the core id, cutoff, a core counter to keep
     * track of the ids, a reference to the process queue, and boolean
     * variables that help perform the logic of a cpu working on a process for
     * round robin scheduling.
     * @param cut The cutoff, number of times a core can work on a process.
     * @param carry  Bring in a reference to the processqueue.
     */
    public CpuCore(int cut, Queue<Process> carry) {
        // set up this core
        core_id = core_counter;
        cutoff = cut;
        core_counter++;
        hold_pq = carry;
        put_back=false;
    }
    /**
     * This method defines the main decision tree for the cpu core,
     * deciding whether or not to work on a process, put down a process,
     * or pick a process up.
     * @param time The current time, counted by the CpuSimulator
     */
    public void step(int time) {
        // either work on the current process,
        // give the process back to the queue if we've worked on it,
        // or claim the next process to work on
        // If there are no processes left, the core will do nothing(idle).
        if(out_of_processes){
            return;
        }
        // If the boolean is set previously, that the process has reached
        // the cutoff, the process is then requeued for later, the boolean
        // is reset, and the current_process is set to null
        if (put_back){
            hold_pq.enqueue(current_process);
            current_process=null;
            put_back=false;
            return;
        }
        //Updates the instances variable that all cores share, in order
        // to print the finish time
        time_counter = time;
        //Increments the counter to see to check if the cutoff has been reached later
        step_counter++;
//      // If the core is not holding a process, the core grabs a new process,
        // due to how the logic was designed, the step counter must be reset.
        if (current_process==null){
            claimProcess();
            step_counter=0;
        }
        //Otherwise, progress is made on the core
        else {
            doWork();
        }


    }
    /**
     * This method checks the processqueue and picks up a process
     */
    private void claimProcess() {
        // get a new process from the queue if there is one
        //Redundant logic, checking if its null or not
        if (current_process==null){
            // Try to dequeue a process, if the process is empty, a boolean is
            //set so the core does not need to go through the decision tree, and
            // return(idle)
            try {
                current_process = hold_pq.dequeue();
            }
            catch (Exception InvalidOperationException){
                out_of_processes =true;
            }
        }
    }
    /**
     * This method simply returns an instance variable detailing the
     * current process
     */
    public Process getCurrent_process() {
        return current_process;
    }

    /**
     * This method actually calls upon the process and increments the progress,
     * if the process is done, the core process is set to null, metrics are taken for
     * avg_turnaround, the step counter is set to zero, and a string is printed detailing
     * the core id, process id, and finish time.
     */
    private void doWork() {
        // work on the current process
        current_process.doWork();
        //Productive step
        productive++;
        // if the process is done, print the string and collect metrics,
        //reset the process variables and counter
        if (current_process.isDone()){
            System.out.println(String.format("%d, %s, %d", core_id, current_process.getProcess_id(), time_counter));
            avg_turnaround += time_counter;
            step_counter=0;
            current_process = null;

        }
        else {
            // if the step counter has reached the cutoff, trigger
            // a boolean to complete the logic in the next loop
            if(step_counter==cutoff){
                step_counter=0;
                put_back = true;
            }
        }


        // if it finishes the process, then print a line in the following format
        //<core id>, <process id>, <finished time>

    }
    /**
     * This method simply returns an instance variable that returns metrics,
     * this is to calculate the avg_turnaround.
     */
    public int get_finished_times(){
        return (avg_turnaround/(core_counter+1));
    }
}