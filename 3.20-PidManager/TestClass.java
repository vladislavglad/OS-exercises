public class TestClass {
    public static void main(String[] args) {

        //create and declare PidManager obejct.
        PidManager manager = new PidManager();

        //allocate a data structure.
        int allocationStatus = manager.allocate_map();

        System.out.println("Status of allocation: " + allocationStatus);

        //allocate pids.
        System.out.print("\nAllocating first 10 pids: ");
        printPids(manager, 10);

        /**
         * Jump to the following currently available index 
         * to simulate case where pids are approaching bounds.
         */
        manager.setCurrentIndex(4697);
        System.out.print("\n\nSimulating further allocation: ");
        printPids(manager, 10);
        System.out.println("\n");

        System.out.println("Releasing pids: ");
        for (int i = 0; i < 10; i+=2) {
            int pid = converToPid(i);
            System.out.println("\t\t" + pid + " released");
            manager.release_pid(pid);
        }

        System.out.print("\nTaking just released pids (and beyond): ");
        printPids(manager, 10);
    }

    /**
     * Utility method: prints out pids from PidManager.
     * @param manager an instance of PidManager.
     * @param amount how many pids to print.
     */
    public static void printPids(PidManager manager, int amount) {
        for (int i = 0; i < amount; i++) {
            int allocatedPid = manager.allocate_pid();
            System.out.print(allocatedPid + " ");
        }
    }

    /**
     * Utility method: converts a given index back to a pid.
     * @param index to be converted to pid
     * @return resulting pid.
     */
    public static int converToPid(int index) {
        return index+=300;
    }
}