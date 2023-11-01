package edu.coursera.parallel;

import static edu.rice.pcdp.PCDP.finish;
import static edu.rice.pcdp.PCDP.async;

/**
 * A simple class for testing compilation of an PCDP project.
 */
public final class Setup {

    /**
     * Default constructor.
     */
    private Setup() {
    }

    /**
     * A simple method for testing compilation of an PCDP project.
     * @param val Input value
     * @return Dummy value
     */
    public static int setup(final int val) {
        final int[] result = new int[1];
        finish(() -> {
            async(() -> {
                result[0] = val;
            });
        });
        return result[0];
    }
}

/*
speed <= work/span
T1 = work =
T∞ = span =
q <=  (T1 - T∞)/ T1
*/