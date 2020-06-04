/**
 * This is a program that creates multiple threads 
 * to test (previously submitted) PidManager class.
 * @author Vladislav Gladyshev.
 */
public class ThreadTest extends Thread {

    //class vars.
    private PidManager manager;
    private int pid;

    /**
     * Constructor that accepts instance of PidManager 
     * to request allocation of pid.
     * @param manager an instance of PidManger class.
     */
    public ThreadTest(PidManager manager) {
        this.manager = manager;
        this.pid = manager.allocate_pid();
    }

    /**
     * Method which is called when thread starts. 
     * In this case thread requests pid, then sleeps for 
     * a random amount of time (0-10 seconds) and releases pid afterwards.
     */
    public void run() {
        try {
            System.out.println("Thread " + ThreadTest.currentThread().getId() + 
                " is running; pid " + pid + " is allocated. \n");

            //generates a random integer; 0-10,000 is possible.
            int rand = (int) (Math.random() * 1000 * 10);

            //puts this thread to sleep (possibly for 0-10 seconds).
            ThreadTest.sleep(rand);

            //releases pid and notifies of thread's return.
            manager.release_pid(pid);
            System.out.println("Thread " + ThreadTest.currentThread().getId() + 
                " has returned after " + (int) rand + " miliseconds of sleep and released pid " + pid + "\n");

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    /**
     * This is the main method to create multiple threads
     * and ask PidAllocation class for an available pid.
     * @param args - (optional command line arguments)
     */
    public static void main(String[] args) {
        
        //instanciate the PidManager class.
        PidManager manager = new PidManager();

        //allocate underlying data structure.
        manager.allocate_map();

        //create 15 threads and start them.
        //(Tested: works for 100 threads)
        for (int i = 0; i < 15; i++) {
            ThreadTest thread = new ThreadTest(manager);
            thread.start();
        }
    }
}
