//Java's built-in library for Semaphores.
import java.util.concurrent.Semaphore;

/**
 * This is a program that creates multiple threads 
 * to test Mutex Lock in action when receiving pid 
 * from PidManager instance.
 * @author Vladislav Gladyshev.
 */
public class MutexThread extends Thread {

    //class vars.
    private char name;
    private Semaphore mutex;
    private PidManager manager;

    /**
     * Constructor for our custom MutexThread class.
     * @param name used to identify any given Thread.
     * @param mutex lock that needs to be aquired.
     * @param manager an instance of PidManger class.
     */
    public MutexThread(char name, Semaphore mutex, PidManager manager) {
        this.name = name;
        this.mutex = mutex;
        this.manager = manager;
    }

    /**
     * Method which is called when thread starts. 
     * In this case a Thread acquires Lock, requests pid, then sleeps for 
     * a random amount of time (0-10 seconds) and releases both Lock and pid afterwards.
     */
    public void run() {
        try {

            //ENTRY SECTION.
            mutex.acquire();

            //CRITICAL SECTION.
            int pid = manager.allocate_pid();
            System.out.println("'" + name + "'" + " has acquired lock and received pid #" + pid + ".\n");
            
            //EXIT SECTION.
            mutex.release();
            System.out.println("'" + name + "'" + " has released lock...\n");

            //REMAINDER SECTION.
            int rand = (int) (Math.random() * 1000 * 10);
            MutexThread.sleep(rand);

            manager.release_pid(pid);
            System.out.println("'" + name + "'" + " has released pid #" + pid 
                + " after " + rand + " ms.\n");

        } catch (Exception err) {err.printStackTrace();}  
    }

    /**
     * This is the main method to create multiple threads
     * that try to acquire Lock and ask 
     * PidAllocation class for an available pid.
     * @param args - (optional command line arguments)
     */
    public static void main(String[] args) {
        
        //Our mutex lock (binary Semaphore).
        Semaphore mutex = new Semaphore(1);

        //Instantiate the Pid Manager class.
        PidManager manager = new PidManager();

        //allocate underlying data structure.
        manager.allocate_map();
        manager.setCurrentIndex(3020);

        //create 15 threads and start them right away.
        for (int i = 0; i < 15; i++) {
            new MutexThread((char)(65 + i), mutex, manager).start();
        }
    }
}