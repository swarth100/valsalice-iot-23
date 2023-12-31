package se.sics.mspsim.core;

public class InterruptMultiplexer implements InterruptHandler {

    private final MSP430Core cpu;
    private final int vector;

    private int interruptBits;

    public InterruptMultiplexer(MSP430Core cpu, int vector) {
        this.cpu = cpu;
        this.vector = vector;
    }

    public void updateInterrupt(boolean value, int bit) {
        if (value) interruptBits |= 1 << bit;
        else interruptBits &= ~(1 << bit);
        cpu.flagInterrupt(vector, this, interruptBits > 0);
    }


    @Override
    public void interruptServiced(int vector) {
        /* do nothing??? */
    }

    @Override
    public String getName() {
        return "InterruptMultiplexer vector " + vector +  " bits: " + interruptBits;
    }

}
