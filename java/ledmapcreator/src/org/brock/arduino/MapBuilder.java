package org.brock.arduino;

import java.awt.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Created by rbrock on 10/10/15.
 */
public class MapBuilder {

    public static final int FULL_BRIGHTNESS = 0xFF;
    public static final int BEAT_BLAST_LENGTH = 250;
    public static final int NUM_OF_PIXELS = 25;

    List<Operation> operations = new ArrayList<>();

    public MapBuilder() {

    }

    public MapBuilder beat(int startTick, int endTick, int freqInMs, int saddr, int eaddr, int brightness, Color color) {
        int tick = startTick;

        while(tick < endTick) {
            operations.add(new Operation(tick, saddr, eaddr, brightness, color.getRed(), color.getGreen(), color.getBlue()));
            operations.add(new Operation(tick + BEAT_BLAST_LENGTH, saddr, eaddr, 0, color.getRed(), color.getGreen(), color.getBlue()));
            tick += freqInMs;
        }

        return this;
    }


    public MapBuilder ramp(int startTick, int endTick, int saddr, int eaddr, int brightness, Color color) {
        int tick = startTick;
        int steps = 25;
        int brightnessStep = brightness / steps;
        int tickSteps = (endTick - startTick) / steps;
        int brightnessRamp = 0;

        while(tick < endTick) {
            operations.add(new Operation(tick, saddr, eaddr, brightnessRamp, color.getRed(), color.getGreen(), color.getBlue()));
            tick += tickSteps;
            brightnessRamp += brightnessStep;
        }

        return this;
    }

    public MapBuilder clear(int startTick) {
        operations.add(new Operation(startTick, 0, NUM_OF_PIXELS - 1, 0, 0, 0, 0));
        return this;
    }

    public void build() {
        Collections.sort(operations);

        for(Operation o : operations) {
            int redIntensity;
            int greenIntensity;
            int blueIntensity;


            if (o.brightness > 0) {
                redIntensity = o.r / (255 / o.brightness);
                greenIntensity = o.g / (255 / o.brightness);
                blueIntensity = o.b / (255 / o.brightness);
            } else {
                redIntensity = greenIntensity = blueIntensity = 0;
            }

            System.out.println(String.format("{%d, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X},", o.tick, o.saddr, o.eaddr, redIntensity, greenIntensity, blueIntensity));
        }
    }




    class Operation implements Comparable {
        public int tick;
        public int saddr;
        public int eaddr;
        public int brightness;
        public int r;
        public int g;
        public int b;

        public Operation(int tick, int saddr, int eaddr, int brightness, int r, int g, int b) {
            this.tick = tick;
            this.saddr = saddr;
            this.eaddr = eaddr;
            this.brightness = brightness;
            this.r = r;
            this.g = g;
            this.b = b;
        }

        @Override
        public int compareTo(Object o) {
            return new Integer(this.tick).compareTo(((Operation)o).tick);
        }
    }


    public static void main(String args[]) {
        MapBuilder m = new MapBuilder();

        m.beat(109, 29000, 937, 0, 0, FULL_BRIGHTNESS, Color.RED)
                .beat(576, 29000, 937, 1, 1, FULL_BRIGHTNESS, Color.BLUE)
                .ramp(15260, 17500, 2, 4, FULL_BRIGHTNESS, Color.GREEN)
                .ramp(17141, 19000, 5, 7, FULL_BRIGHTNESS, Color.MAGENTA)
                .ramp(18070, 20000, 8, 10, FULL_BRIGHTNESS, Color.RED)
                .ramp(18669, 21000, 11, 13, FULL_BRIGHTNESS, Color.BLUE)
                //.ramp(22807, 25000, 14, 15, FULL_BRIGHTNESS, Color.GREEN)
                .clear(22500)
                .ramp(22807, 25500, 2, 4, FULL_BRIGHTNESS, Color.GREEN)
                .ramp(24688, 27000, 5, 7, FULL_BRIGHTNESS, Color.MAGENTA)
                .ramp(25617, 28000, 8, 10, FULL_BRIGHTNESS, Color.RED)
                .ramp(26216, 29000, 11, 13, FULL_BRIGHTNESS, Color.BLUE)
                .build();
    }
}
