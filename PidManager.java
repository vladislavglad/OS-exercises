/**
 * Class that allows you to allocate and release process IDs.
 * (within default bounds of 300 to 5000).
 * @author Vladislav Gladyshev
 * @version 2.0
 */
public class PidManager {

    //our instance vars.
    private final int MIN_PID = 300;
    private final int MAX_PID = 5000;
    
    //Size of an underlying data structure.
    private final int SIZE = 4701; 
    
    /**
     * an array to check availablility of a pid:
     * 0 means available for taking,
     * 1 means taken.
     */
    private int[] pids;

    //our iterator (used for an developer's testing).
    private int currentIndex; 

    /**
     * Utility method to convert a given pid to an index
     * that we use to check pid's availability.
     * @param pid value you would like to convert to index.
     * @return corresponding index (to the pid you passed)
     */
    private int convertToIndex(int pid) {
        return pid -= 300;
    }

    /**
     * Utility method to convert a given index back to a pid.
     * @param index index you would like to convert to a pid.
     * @return corresponding pid of the passed index.
     */
    private int convertToPid(int index) {
        return index += 300;
    }

    /**
     * Utility method to check if index is within defined bounds.
     * @param i index to check
     * @return true if inex is within bounds, false otherwise.
     */
    private boolean isIndexInRange(int i) {
        return i >= convertToIndex(MIN_PID) && i <= convertToIndex(MAX_PID);
    }
    
    /**
     * Setter for currentIndex - index available for taking.
     * @param index value to set.
     */
    public void setCurrentIndex(int index) {
        currentIndex = index;
    }

    /**
     * Creates a data structure to hold information about pid's availability.
     * @return 1 if succesfully created, -1 otherwise.
     */
    public int allocate_map() {
        try {
            /**
             * Java automatically initializes contents of each index with 0.
             * (indices 0 through 4700 corresponding to pids 300 to 5000).
             */
            pids = new int[SIZE];

            //for internal testing.
            currentIndex = 0;

            //created succesfuly.
            return 1;
        } catch(Exception e) {
            //failed to create an object.
            return -1;
        }
    }

    /**
     * Allocates first available pid.
     * @return allocated pid, otherwise -1 if unsuccesful.
     */
    public int allocate_pid() {

        //check if currentIndex is available for taking.
        if (isIndexInRange(currentIndex)) {

            //get the pid and occupy it.
            int allocatedPid = convertToPid(currentIndex);
            pids[currentIndex] = 1; 

            //set next available index and return allocated pid.
            currentIndex++;
            return allocatedPid;

            /**
             * if currentIndex is not available 
             * iterate from the start of "pids" array 
             * and find unocupied index: content is 0.
             */
        } else {
            for (int i = convertToIndex(MIN_PID); i <= convertToIndex(MAX_PID); i++) {
                if (pids[i] == 0) {
                    
                    //occupy this index.
                    pids[i] = 1; 
                   
                    //return allocated pid.
                    return convertToPid(i);
                }
            }

            //unsuccessful.
            return -1;
        }
    }

    /**
     * Releases a given pid and sets it as available for taking.
     * @param pid value you want to release.
     */
    public void release_pid(int pid) {

        //convert pid to index and check if within bounds.
        int index = convertToIndex(pid);
        if (isIndexInRange(index)) {

            //set it as available.
            pids[index] = 0; 

            //currentIndex = index;
        }
    }
}