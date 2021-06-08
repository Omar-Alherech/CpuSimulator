import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Process {

    // instance variables...
    private char process_id;
    private int process_size;
    private int progress;

    /**
     * This method returns an instance variable that returns
     * the progress done.
     */
    public int getProgress() {
        return progress;
    }

    /**
     * This method returns an instance variable detailing the
     * process id
     */
    public char getProcess_id() {
        return process_id;
    }
    /**
     * This method returns an instance variable detailing the
     * process size
     */
    public int getProcess_size() {
        return process_size;
    }

    /**
     * This method initializes the process_id and process_size from the
     * user input string.
     * @param  text User defined input, used to set up the instance variables
     */
    public Process(String text) {
        // set up process object
        //Split the string and set up the respective instance variables
        String[] splitter = text.split(",");
        process_id = splitter[0].charAt(0);
        process_size = Integer.parseInt(splitter[1]);
    }

    /**
     * This method increments the progress, when this is used
     * is decided by the core.
     */
    public void doWork() {
        // increment progress for this job
        progress++;
    }
    /**
     * This method returns boolean that defines whether or not
     * the process has been completed.
     */
    public boolean isDone(){
        return (progress==process_size);
    }
}