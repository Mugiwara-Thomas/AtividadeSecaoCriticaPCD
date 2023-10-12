public class TrafficController {
    private int carsOnBridge = 0;
    private boolean bridgeLocked = false;

    public synchronized void enterLeft() throws InterruptedException {
        while (bridgeLocked) {
            wait();
        }

        if (carsOnBridge != 0) {
            wait();
        }
        carsOnBridge++;
        bridgeLocked = true;
    }

    public synchronized void enterRight() throws InterruptedException {
        while (bridgeLocked) {
            wait();
        }

        if (carsOnBridge != 0) {
            wait();
        }
        carsOnBridge++;
        bridgeLocked = true;
    }

    public synchronized void leaveLeft() {
        carsOnBridge--;
        notifyAll();
        bridgeLocked = false;
    }

    public synchronized void leaveRight() {
        carsOnBridge--;
        notifyAll();
        bridgeLocked = false;
    }

}